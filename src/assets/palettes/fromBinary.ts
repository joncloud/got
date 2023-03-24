import { readFile } from 'fs/promises';
import { join } from 'path';
import { makeDataView } from 'struct-buffer';
import { PaletteList } from './Palette';
import { toTs } from './toTs';
import { mkdirIfNotExists } from '../files';

export async function fromBinary(filename: string, src: string, dst: string) {
  const buffer = await readFile(
    join(src, filename),
  );
  const view = makeDataView(buffer);
  const resource = PaletteList.decode(view);
  const paletteDir = join(dst, 'palettes');
  await mkdirIfNotExists(paletteDir);
  await toTs(resource, filename.toLowerCase(), paletteDir);
}
