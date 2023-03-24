import { readFile } from 'fs/promises';
import { join } from 'path';
import { makeDataView } from 'struct-buffer';
import { ActorData } from './ActorData';
import { toTs } from './toTs';
import { mkdirIfNotExists } from '../files';

export async function fromBinary(filename: string, src: string, dst: string) {
  const buffer = await readFile(
    join(src, filename),
  );
  const view = makeDataView(buffer);
  const resource = ActorData.decode(view);
  const actorDir = join(dst, 'actors');
  await mkdirIfNotExists(actorDir);
  await toTs(resource, filename.toLowerCase(), actorDir);
}
