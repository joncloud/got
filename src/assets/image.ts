import Jimp from 'jimp';

export async function createImage(width: number, height: number) {
  return new Promise<Jimp>((resolve, reject) => {
    new Jimp(width, height, (err, res) => {
      if (res) {
        resolve(res);
      } else {
        reject(err ?? new Error('unexpected error'));
      }
    });
  });
}

export async function loadImage(imgPath: string) {
  return new Promise<Jimp>((resolve, reject) => {
    Jimp.read(imgPath, (err, res) => {
      if (res) {
        resolve(res);
      } else {
        reject(err ?? new Error('unexpected error'));
      }
    })
  });
}
