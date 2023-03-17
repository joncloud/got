export function encodeBase64(array: number[]) {
  return `[...Buffer.from('${Buffer.from(array).toString('base64')}', 'base64')]`;
}

export function encodeString(array: number[]) {
  const firstZero = array.indexOf(0);
  let target: number[];
  if (firstZero > -1) {
    target = array.slice(0, firstZero);
  } else {
    target = array.slice();
  }
  return `'${Buffer.from(target).toString('utf8')}'`;
}

export function encodeArray(array: number[]) {
  return `[${array.join(', ')}]`;
}
