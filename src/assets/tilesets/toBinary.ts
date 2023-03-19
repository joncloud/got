import { writeFile } from 'fs/promises';
import Jimp from 'jimp';
import { join, parse } from 'path';
import { loadImage } from '../image';
import { fromTs } from '../palettes';

export async function toBinary(filename: string, src: string, dst: string) {
  const img = await loadImage(
    join(src, filename),
  );

  const { palettes } = await fromTs(join(src, '..', '..', 'palettes', 'palette.ts'));

  const colors = palettes.map(({ r, g, b }) => Jimp.rgbaToInt(r, g, b, 0xFF));

  const buffer: number[] = [];
  let total = 23 * 16 * 10 * 16;
  let xOffset = 0, yOffset = 0;
  while (total) {
    const width = 16;
    const height = 16;
    buffer.push(width / 4);
    buffer.push(height);
    buffer.push(0xFF); // TODO should be same as old value

    let x = 0, y = 0, remaining = width * height;
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

      y = (y + 1) % height;
      if (y === 0) {
        x += 1;
      }
    }

    xOffset += width;
    if (xOffset >= 23 * 16) {
      xOffset = 0;
      yOffset += height;
    }
  }

  const target = join(dst, parse(filename).name.toUpperCase());
  await writeFile(target, new Uint8Array(buffer));
  console.log('writing', target);
}
