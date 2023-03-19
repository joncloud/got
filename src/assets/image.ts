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
