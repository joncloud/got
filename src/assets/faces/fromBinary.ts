import { readFile, readdir } from 'fs/promises';
import { join } from 'path';
import { mkdirIfNotExists } from '../files';
import { createImage, fromRawTileset } from '../image';
import { fromTs } from '../palettes';

async function findFaceFilenames(prefix: string, src: string) {
  const filenames = await readdir(src);
  const faceFilenames = [];
  for (const filename of filenames) {
    if (!filename.startsWith(prefix)) {
      continue;
    }

    const suffix = +filename.slice(prefix.length);
    if (Number.isNaN(suffix)) {
      continue;
    }

    faceFilenames.push([suffix, filename] as const);
  }

  faceFilenames.sort((x, y) => x[0] - y[0]);

  return faceFilenames.map(x => x[1]);
}

export async function fromBinary(filename: string, src: string, dst: string) {
  const filenames = await findFaceFilenames(filename, src);

  // (0x04 * 0x04) w x 0x10 h - 4 frames
  const imageWidth = 16 * 4;
  const imageHeight = filenames.length * 16;
  const img = await createImage(imageWidth, imageHeight);

  const paletteList = await fromTs(join(dst, 'palettes', 'palette.ts'));
  let yOffset = 0;

  for (const faceFilename of filenames) {
    const buffer = new Uint8Array(await readFile(
      join(src, faceFilename),
    ));

    const face = await fromRawTileset(4 * 16, 1 * 16, buffer, paletteList);
    for (let x = 0; x < face.getWidth(); x += 1) {
      for (let y = 0; y < face.getHeight(); y += 1) {
        img.setPixelColor(
          face.getPixelColor(x, y),
          x,
          y + yOffset,
        );
      }
    }

    yOffset += 16;
  }

  await mkdirIfNotExists(join(dst, 'images'));
  const target = join(dst, 'images', `${filename.toLowerCase()}.png`);
  await img.writeAsync(target);
  console.log('writing', target);
}
