import { readFile } from 'fs/promises';
import { join } from 'path';
import { mkdirIfNotExists } from '../files';
import { fromRawTileset } from '../image';
import { fromTs } from '../palettes';

export async function fromBinary(filename: string, src: string, dst: string) {
  const buffer = new Uint8Array(await readFile(
    join(src, filename),
  ));

  const paletteList = await fromTs(join(dst, 'palettes', 'palette.ts'));

  const img = await fromRawTileset(8 * 16, 4 * 16, buffer, paletteList);

  const target = join(dst, 'images', `${filename.toLowerCase()}.png`);
  await mkdirIfNotExists(join(dst, 'images'));
  await img.writeAsync(target);
  console.log('writing', target);
}
