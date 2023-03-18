import { uint32_t, StructBuffer } from 'struct-buffer';

export type Header = {
  offset: number,
  length: number,
};

export const Header = new StructBuffer<Header>(
  'Header',
  {
    offset: uint32_t,
    length: uint32_t,
  },
  {
    littleEndian: true,
  }
);
