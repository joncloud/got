import { readdir } from 'fs/promises';
import { fromBinary as actors } from './actors';
import { fromBinary as palettes } from './palettes';
import { fromBinary as sounds } from './sounds';

export const fileMatchers = [
  [/ACTOR\d+/, actors],
  [/PALETTE|STORYPAL/, palettes],
  [/DIGSOUND/, sounds],
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
