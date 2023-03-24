import { readFile } from 'fs/promises';
import { join } from 'path';
import { mkdirIfNotExists } from '../files';
import { createImage } from '../image';
import { expectedBinaryLength, glyphCount, glyphHeight, glyphWidth } from './glyph';

function getColor(val: number) {
  return val ? 0xFFFFFFFF : 0x00000000;
}

export async function fromBinary(filename: string, src: string, dst: string) {
  const buffer = await readFile(
    join(src, filename),
  );
  if (buffer.length < expectedBinaryLength) {
    throw new Error(`${join(src, filename)} does not have enough data, expected ${expectedBinaryLength}`);
  }

  let index = 0;
  const img = await createImage(glyphWidth * glyphCount, glyphHeight);
  function writeGlyph(xOffset: number) {
    let x = 0, y = 0, remaining = glyphWidth * glyphHeight;
    while (remaining >= 2) {
      img.setPixelColor(getColor(buffer[index]), x + xOffset, y);
      img.setPixelColor(getColor(buffer[index + 1]), x + 4 + xOffset, y);

      y = (y + 1) % 9;
      if (y === 0) x += 1;
      index += 2;
      remaining -= 2;
    }
  }

  let glyphsWritten = 0;
  while (index < buffer.length) {
    const xOffset = glyphsWritten * 8;
    writeGlyph(xOffset);
    glyphsWritten += 1;
  }

  const fontsDir = join(dst, 'fonts');
  await mkdirIfNotExists(fontsDir);
  const target = join(fontsDir, `${filename.toLowerCase()}.png`);
  await img.writeAsync(target);
  console.log('writing', target);
}
