'use strict';

// This script analyzes a directory to find all assets
// to add to the GOTRES.DAT file, and generates a batch
// file to run in MSDOS to create the GOTRES.DAT file.

import { readdir, writeFile } from 'fs/promises';

const [srcFolder, dstBatchFile] = process.argv.slice(2);

if (!srcFolder || !dstBatchFile) {
  console.error('usage generateAssetsBatch.js [srcFolder] [dstBatchFile]');
  process.exit(1);
}

const files = await readdir(srcFolder);

let batch = 'res.exe build\\gotres.dat c\r\n';

// TODO eventually allow encoding / lzss compression of files
for (const file of files) {
  batch += `res.exe build\\gotres.dat a ${srcFolder}\\${file} ${file} 0\r\n`;
}

await writeFile(dstBatchFile, batch);
