import { join } from 'path';
import { PaletteList } from './Palette';
import { writeFile } from 'fs/promises';

function toHex(num: number) {
  return num.toString(16)
    .padStart(2, '0')
    .toUpperCase();
}

export async function toTs({ palettes }: PaletteList, name: string, dst: string) {
  let ts = '';
  function appendLine(line: string) {
    ts += `${line}\n`;
  }

  appendLine('const palette = [');
  for (const { r, g, b } of palettes) {
    const rgb = [
      toHex(r),
      toHex(g),
      toHex(b),
    ].join('');
    appendLine(`  '${rgb}',`);
  }
  appendLine('] as const;');
  appendLine('');
  appendLine('export default palette;');
  appendLine('');

  const target = join(dst, `${name}.ts`);
  await writeFile(target, ts);
  console.log('writing', target);
}
