import { readFile } from 'fs/promises';
import Jimp from 'jimp';
import { join } from 'path';
import { mkdirIfNotExists } from '../files';
import { createImage } from '../image';
import { fromTs } from '../palettes';

export async function fromBinary(filename: string, src: string, dst: string) {
  const buffer = new Uint8Array(await readFile(
    join(src, filename),
  ));

  const { palettes } = await fromTs(join(dst, 'palettes', 'palette.ts'));

  const colors = palettes.map(({ r, g, b }) => Jimp.rgbaToInt(r, g, b, 0xFF));
  function getColor(idx: number) {
    if (idx === 0 || idx === 15) {
      return Jimp.rgbaToInt(idx, 0x00, 0x00, 0x00);
    } else {
      return colors[idx];
    }
  }

  const width = 320;
  const height = 48;
  const passes = 4;
  const planeSize = height / passes;
  const img = await createImage(width, height);

  for (let i = 0; i < width * height; i++) {
    const paletteIndex = buffer[Math.floor(i / 4) + (i % 4) * width * planeSize + 6];
    const color = getColor(paletteIndex);
    const x = i % width;
    const y = Math.floor(i / width);
    img.setPixelColor(color, x, y);
  }

  const target = join(dst, 'images', `${filename.toLowerCase()}.png`);
  await mkdirIfNotExists(join(dst, 'images'));
  await img.writeAsync(target);
  console.log('writing', target);
}
