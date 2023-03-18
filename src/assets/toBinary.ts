import { copyFile, readdir } from 'fs/promises';
import { join, parse } from 'path';
import { toBinary as actorProcessor } from './actors';
import { toBinary as paletteProcessor } from './palettes';
import { toBinary as soundProcessor } from './sounds';
import { mkdirIfNotExists } from './files';

const toCopy = [
  ['sounds', /bossv/],
] as const;

export async function toBinary(src: string, dst: string) {
  const actors = join(src, 'actors');
  await mkdirIfNotExists(actors);
  for (const filename of await readdir(actors)) {
    if (!filename.endsWith('.ts')) {
      continue;
    }

    await actorProcessor(filename, actors, dst);
  }

  const palettes = join(src, 'palettes');
  await mkdirIfNotExists(palettes);
  for (const filename of await readdir(palettes)) {
    if (!filename.endsWith('.ts')) {
      continue;
    }

    await paletteProcessor(filename, palettes, dst);
  }

  const sounds = join(src, 'sounds');
  await mkdirIfNotExists(sounds);

  await soundProcessor('digsound', sounds, dst);

  for (const [dirName, pattern] of toCopy) {
    const dir = join(src, dirName);
    await mkdirIfNotExists(dir);

    for (const filename of await readdir(dir)) {
      if (!pattern.test(filename)) {
        continue;
      }

      const target = join(dst, `${parse(filename).name.toUpperCase()}`);
      await copyFile(
        join(dir, filename),
        target,
      );
      console.log('writing', target);
    }
  }
}
