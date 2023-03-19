import { readdir, copyFile } from 'fs/promises';
import { join } from 'path';
import { fromBinary as actorProcessor } from './actors';
import { mkdirIfNotExists } from './files';
import { fromBinary as paletteProcessor } from './palettes';
import { fromBinary as soundProcessor } from './sounds';
import { fromBinary as fontProcessor } from './fonts';
import { fromBinary as tilesetProcessor } from './tilesets';
import { fromBinary as faceProcessor } from './faces';

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

type FileProcessor = (filename: string, src: string, dst: string) => Promise<void>;

async function processFiles(pattern: RegExp, filenames: string[], src: string, dst: string, processor: FileProcessor) {
  for (const filename of filenames) {
    if (!pattern.test(filename)) {
      continue;
    }

    await processor(filename, src, dst);
  }
}

export async function fromBinary(src: string, dst: string) {
  const filenames = await readdir(src);

  await processFiles(/PALETTE|STORYPAL/, filenames, src, dst, paletteProcessor);
  await processFiles(/ACTOR\d+/, filenames, src, dst, actorProcessor);
  await processFiles(/DIGSOUND/, filenames, src, dst, soundProcessor);
  await processFiles(/BOSSV\d+/, filenames, src, dst, copy.bind(null, 'sounds', '.voc'));
  await processFiles(/TEXT/, filenames, src, dst, fontProcessor);
  await processFiles(/BPICS/, filenames, src, dst, tilesetProcessor);
  await faceProcessor('FACE', src, dst);
}
