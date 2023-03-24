import { join } from 'path';

function fromHex(s: string) {
  return parseInt(s, 16);
}

export async function fromTs(src: string) {
  const resource = (await import(join(process.cwd(), src))).default as unknown;
  if (!Array.isArray(resource)) {
    throw new Error(`${src} does not export an array`);
  } else if (resource.length !== 256) {
    throw new Error(`${src} does not export an array with 256 elements`);
  }

  const palettes = [];
  for (let index = 0; index < resource.length; index += 1) {
    const item = resource[index];
    if (typeof item !== 'string') {
      throw new Error(`${src} element ${index} is not a string`);
    } else if (item.length !== 6) {
      throw new Error(`${src} element ${index} is not a hex string`);
    }

    const r = fromHex(item.slice(0, 2));
    const g = fromHex(item.slice(2, 4));
    const b = fromHex(item.slice(4, 6));
    palettes.push({
      r, g, b,
    });
  }
  return { palettes } as const;
}
