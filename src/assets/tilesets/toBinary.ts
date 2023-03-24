import { writeFile } from 'fs/promises';
import { join, parse } from 'path';
import { toRawTileset } from '../image';
import { fromTs } from '../palettes';

export async function toBinary(filename: string, src: string, dst: string) {
  const paletteList = await fromTs(join(src, '..', '..', 'palettes', 'palette.ts'));

  const buffer = await toRawTileset(
    join(src, filename),
    16, 16,
    0xFF,
    23,
    paletteList,
  );

  const target = join(dst, parse(filename).name.toUpperCase());
  await writeFile(target, new Uint8Array(buffer));
  console.log('writing', target);
}
