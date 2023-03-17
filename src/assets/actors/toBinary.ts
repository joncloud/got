import { writeFile } from 'fs/promises';
import { join, parse } from 'path';
import { ActorData } from './ActorData';
import { fromTs } from './fromTs';

export async function toBinary(filename: string, src: string, dst: string) {
  const resource = await fromTs(
    join(src, filename),
  );
  const view = ActorData.encode(resource);
  const target = join(dst, parse(filename).name.toUpperCase());
  await writeFile(
    target,
    Buffer.from(view.buffer)
  );
  console.log('writing', target);
}
