import Jimp from 'jimp';
import { uint16_t, StructBuffer } from 'struct-buffer';
import { PaletteList } from './palettes';

export async function createImage(width: number, height: number) {
  return new Promise<Jimp>((resolve, reject) => {
    new Jimp(width, height, (err, res) => {
      if (res) {
        resolve(res);
      } else {
        reject(err ?? new Error('unexpected error'));
      }
    });
  });
}

export async function loadImage(imgPath: string) {
  return new Promise<Jimp>((resolve, reject) => {
    Jimp.read(imgPath, (err, res) => {
      if (res) {
        resolve(res);
      } else {
        reject(err ?? new Error('unexpected error'));
      }
    })
  });
}

export type TileHeader = {
  width: number,
  height: number,
  flag: number,
};

export const TileHeader = new StructBuffer<TileHeader>(
  'TileHeader',
  {
    width: uint16_t,
    height: uint16_t,
    flag: uint16_t,
  },
  {
    littleEndian: true,
  }
);

export async function fromRawTileset(imageWidth: number, imageHeight: number, buffer: Uint8Array, { palettes }: PaletteList) {
  const colors = palettes.map(({ r, g, b }) => Jimp.rgbaToInt(r, g, b, 0xFF));
  function getColor(idx: number) {
    if (idx === 0 || idx === 15) {
      return Jimp.rgbaToInt(idx, 0x00, 0x00, 0x00);
    } else {
      return colors[idx];
    }
  }
  const img = await createImage(imageWidth, imageHeight);
  let remainingBuffer = buffer.slice();
  let xOffset = 0, yOffset = 0;
  while (remainingBuffer.length) {
    const { width: partialWidth, height } = TileHeader.decode(remainingBuffer);
    const width = partialWidth * 4;
    remainingBuffer = remainingBuffer.slice(TileHeader.byteLength);

    let x = 0, y = 0, remaining = width * height;
    const passes = 4;
    while (remaining > 0) {
      for (let i = 0; i < passes; i += 1) {
        img.setPixelColor(
          getColor(remainingBuffer[0]),
          x + (i * 4) + xOffset,
          y + yOffset
        );
        remainingBuffer = remainingBuffer.slice(1);
        remaining -= 1;
      }

      y = (y + 1) % height;
      if (y === 0) {
        x += 1;
      }
    }

    xOffset += width;
    if (xOffset >= imageWidth) {
      xOffset = 0;
      yOffset += height;
    }
  }
  return img;
}

export async function toRawTileset(filenameOrImg: string | Jimp, tileWidth: number, tileHeight: number, flag: number, columnCount: number, { palettes }: PaletteList) {
  const img = typeof filenameOrImg === 'string'
    ? await loadImage(filenameOrImg)
    : filenameOrImg;

  const colors = palettes.map(({ r, g, b }) => Jimp.rgbaToInt(r, g, b, 0xFF));

  const buffer: number[] = [];
  let total = img.getWidth() * img.getHeight();
  let xOffset = 0, yOffset = 0;
  while (total) {
    const header = TileHeader.encode({
      width: tileWidth / 4,
      height: tileHeight,
      flag,
    });
    buffer.push(...new Uint8Array(header.buffer));

    let x = 0, y = 0, remaining = tileWidth * tileHeight;
    const passes = 4;
    while (remaining > 0) {
      for (let i = 0; i < passes; i += 1) {
        const pixel = img.getPixelColor(
          x + (i * 4) + xOffset,
          y + yOffset,
        );
        const { r, a } = Jimp.intToRGBA(pixel);
        // hacky to keep as close to original format
        const paletteIndex = a === 0 && r > -1 && r < colors.length
          ? r

          // Some colors are duplicated in palettes,
          // so they move to a separate index.
          // 0x37 -> 0x20
          // 0x60 -> 0x5F
          // 0xE0 -> 0x00
          : colors.indexOf(pixel);
        if (paletteIndex === -1) {
          const hexPixel = '0x' + pixel.toString(16).padStart(8, '0');
          throw new Error(`${hexPixel} is not defined in palette.ts`);
        }
        buffer.push(paletteIndex);
        remaining -= 1;
        total -= 1;
      }

      y = (y + 1) % tileHeight;
      if (y === 0) {
        x += 1;
      }
    }

    xOffset += tileWidth;
    if (xOffset >= 23 * 16) {
      xOffset = 0;
      yOffset += tileHeight;
    }
  }

  return new Uint8Array(buffer);
}

export type Rectangle = {
  x: number,
  y: number,
  width: number,
  height: number,
};

export async function slice(src: Jimp, { x, y, width, height }: Rectangle) {
  const dst = await createImage(width, height);
  for (let dstX = 0; dstX < width; dstX += 1) {
    for (let dstY = 0; dstY < height; dstY += 1) {
      dst.setPixelColor(
        src.getPixelColor(dstX + x, dstY + y),
        dstX,
        dstY,
      );
    }
  }
  return dst;
}
