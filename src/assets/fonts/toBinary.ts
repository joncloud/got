import { writeFile } from 'fs/promises';
import { join, parse } from 'path';
import { loadImage } from '../image';
import { expectedBinaryLength, glyphHeight, glyphWidth } from './glyph';

export async function toBinary(filename: string, src: string, dst: string) {
  const resource = await loadImage(
    join(src, filename),
  );
  const buffer: number[] = [];

  let index = 0;
  function writeGlyph(xOffset: number) {
    let x = 0, y = 0, remaining = glyphWidth * glyphHeight;

    while (remaining >= 2) {
      buffer.push(resource.getPixelColor(x + xOffset, y) ? 1 : 0);
      buffer.push(resource.getPixelColor(x + 4 + xOffset, y) ? 1 : 0);

      y = (y + 1) % 9;
      if (y === 0) x += 1;
      index += 2;
      remaining -= 2;
    }
  }

  let glyphsWritten = 0;
  while (index < expectedBinaryLength) {
    const xOffset = glyphsWritten * 8;
    writeGlyph(xOffset);
    glyphsWritten += 1;
  }

  const target = join(dst, parse(filename).name.toUpperCase());
  await writeFile(target, new Uint8Array(buffer));
  console.log('writing', target);
}
