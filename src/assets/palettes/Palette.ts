import { BYTE, StructBuffer } from 'struct-buffer';

export type Palette = {
  r: number,
  g: number,
  b: number,
};

export const Palette = new StructBuffer<Palette>(
  'Palette',
  {
    r: BYTE,
    g: BYTE,
    b: BYTE,
  },
);

export type PaletteList = {
  palettes: Palette[],
};

export const PaletteList = new StructBuffer<PaletteList>(
  'PaletteList',
  {
    palettes: Palette[256],
  },
);
