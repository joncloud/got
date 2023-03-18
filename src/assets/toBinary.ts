import { readdir } from 'fs/promises';
import { join } from 'path';
import { toBinary as actorProcessor } from './actors';
import { toBinary as paletteProcessor } from './palettes';
import { toBinary as soundProcessor } from './sounds';
import { mkdirIfNotExists } from './files';

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

  // TODO copy boss sounds as-is
}
