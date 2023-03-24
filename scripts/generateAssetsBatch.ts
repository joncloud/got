// This script analyzes a directory to find all assets
// to add to the GOTRES.DAT file, and generates a batch
// file to run in MSDOS to create the GOTRES.DAT file.

import { readdir, writeFile } from 'fs/promises';

async function main() {
  const [srcFolder, dstBatchFile] = process.argv.slice(2);

  if (!srcFolder || !dstBatchFile) {
    console.error('usage generateAssetsBatch.js [srcFolder] [dstBatchFile]');
    process.exit(1);
  }

  const results = await readdir(srcFolder, { withFileTypes: true });

  let batch = 'res.exe \\build\\gotres.dat c > build\\assets.txt\r\n';

  // TODO eventually allow encoding / lzss compression of files
  for (const result of results) {
    if (!result.isFile()) {
      continue;
    }
    const file = result.name;
    batch += `res.exe \\build\\gotres.dat a \\${srcFolder}\\${file} ${file} 0 >> build\\assets.txt\r\n`;
  }

  await writeFile(dstBatchFile, batch);
}

main().then(() => {
  process.exit(0);
}).catch((err) => {
  console.error(err);
  process.exit(1);
});
