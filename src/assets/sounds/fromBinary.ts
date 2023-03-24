import { readFile, writeFile } from 'fs/promises';
import { join } from 'path';
import { makeDataView } from 'struct-buffer';
import { mkdirIfNotExists } from '../files';
import { HeaderList } from './HeaderList';

export async function fromBinary(filename: string, src: string, dst: string) {
  const buffer = new Uint8Array(await readFile(
    join(src, filename),
  ));
  let soundBuffer = buffer.slice(HeaderList.byteLength);
  const view = makeDataView(buffer);
  const headers = HeaderList.decode(view);

  const soundDir = join(dst, 'sounds');
  await mkdirIfNotExists(soundDir);

  for (let index = 0; index < headers.length; index += 1) {
    const header = headers[index];
    const voc = soundBuffer.slice(0, header.length);
    const vocFile = join(soundDir, `${filename.toLowerCase()}${index}.voc`);
    await writeFile(
      vocFile,
      voc,
    );
    console.log('writing', vocFile);
    soundBuffer = soundBuffer.slice(header.length);
  }
}
