import { writeFile } from 'fs/promises';
import Jimp from 'jimp';
import { join, parse } from 'path';
import { loadImage } from '../image';
import { fromTs } from '../palettes';

export async function toBinary(filename: string, src: string, dst: string) {
  const { palettes } = await fromTs(join(src, '..', 'palettes', 'palette.ts'));

  const colors = palettes.map(({ r, g, b }) => Jimp.rgbaToInt(r, g, b, 0xFF));

  const width = 320;
  const height = 48;
  const img = await loadImage(join(src, filename));
  const buffer = new Uint8Array(width * height * 4);

  for (let i = 0; i < width * height; i++) {
    const row = Math.floor(i / width);
    const col = i % width;
    const offset = (row * 12 * width) + (Math.floor(col / 4) * 4) + (col % 4);

    const pixel = img.getPixelColor(
      col,
      row,
      // x + (i * 4) + xOffset,
      // y + yOffset,
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
    buffer[offset] = paletteIndex;
  }

  const target = join(dst, parse(filename).name.toUpperCase());
  await writeFile(target, buffer);
  console.log('writing', target);
}
