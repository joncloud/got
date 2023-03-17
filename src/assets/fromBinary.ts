import { readdir } from 'fs/promises';
import { fromBinary as actors } from './actors';

export const fileMatchers = [
  [/ACTOR\d+/, actors],
] as const;

export async function fromBinary(src: string, dst: string) {
  const filenames = await readdir(src);
  for (const filename of filenames) {
    for (const [pattern, processor] of fileMatchers) {
      if (!pattern.test(filename)) {
        continue;
      }

      await processor(filename, src, dst);
      break;
    }
  }
}
