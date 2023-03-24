import { mkdir } from 'fs/promises';

export async function mkdirIfNotExists(p: string) {
  try {
    await mkdir(p, {
      recursive: true,
    });
  } catch (err) {
    // TODO handle specific error
  }
}
