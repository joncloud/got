import { ActorData } from './ActorData';
import { join } from 'path';

export async function fromTs(src: string) {
  const tmp = await import(join(process.cwd(), src));
  // TODO probably better validation to prevent unexpected type differences
  return tmp.default as unknown as ActorData;
}
