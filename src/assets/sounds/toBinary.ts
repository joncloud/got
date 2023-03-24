import { readdir, stat, readFile, writeFile } from 'fs/promises';
import { join, parse } from 'path';
import { HeaderList } from './HeaderList';

export async function toBinary(filename: string, src: string, dst: string) {
  const files = [];
  for (const vocFilename of await readdir(src)) {
    if (!vocFilename.startsWith(filename)) {
      continue;
    }

    const res = /\d+/.exec(vocFilename);
    if (!res) {
      continue;
    }
    const index = parseInt(res[0], 10);
    const { size } = await stat(join(src, vocFilename));
    const buffer = await readFile(join(src, vocFilename));

    files.push([index, size, buffer] as const);
  }
  files.sort((x, y) => x[0] - y[0]);

  const headers = [];
  const sounds = [];
  for (const [, size, buffer] of files) {
    headers.push({
      offset: sounds.length,
      length: size,
    } as const)
    sounds.push(...buffer);
  }

  const view = HeaderList.encode(headers);
  const target = join(dst, parse(filename).name.toUpperCase());
  await writeFile(
    target,
    new Uint8Array([...Buffer.from(view.buffer), ...sounds]),
  );
  console.log('writing', target);
}
