import { readdir, copyFile } from 'fs/promises';
import { join } from 'path';
import { fromBinary as actors } from './actors';
import { mkdirIfNotExists } from './files';
import { fromBinary as palettes } from './palettes';
import { fromBinary as sounds } from './sounds';

async function copy(dstSuffix: string, extension: string, filename: string, src: string, dst: string) {
  const dstDir = join(dst, dstSuffix);
  await mkdirIfNotExists(dstDir);

  const target = join(dstDir, `${filename.toLowerCase()}${extension}`);
  await copyFile(
    join(src, filename),
    target,
  );
  console.log('writing', target);
}

export const fileMatchers = [
  [/ACTOR\d+/, actors],
  [/PALETTE|STORYPAL/, palettes],
  [/DIGSOUND/, sounds],
  [/BOSSV/, copy.bind(null, 'sounds', '.voc')],
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
