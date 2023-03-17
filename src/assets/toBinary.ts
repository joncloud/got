import { readdir } from 'fs/promises';
import { join } from 'path';
import { toBinary as actorProcessor } from './actors';
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
}
