import { join, parse } from 'path';
import { loadImage, slice, toRawTileset } from '../image';
import { fromTs } from '../palettes';

export async function toBinary(filename: string, src: string, dst: string) {
  const img = await loadImage(
    join(src, filename),
  );

  const paletteList = await fromTs(join(src, '..', 'palettes', 'palette.ts'));

  const rowCount = img.getHeight() / 16;
  for (let row = 0; row < rowCount; row += 1) {
    const face = await slice(img, { x: 0, y: row * 16, width: img.getWidth(), height: 16 });

    const target = join(dst, `${parse(filename).name.toUpperCase()}${row + 1}`);
    await toRawTileset(face, 16, 16, 0x00, 4, paletteList);
    console.log('writing', target);
  }
}
