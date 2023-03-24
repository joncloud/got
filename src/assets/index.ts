import { fromBinary } from './fromBinary';
import { toBinary } from './toBinary';

async function main() {
  for (const arg of process.argv) {
    if (arg === '--from-binary') {
      await fromBinary('assets', 'assets');
    } else if (arg === '--to-binary') {
      await toBinary('assets', 'assets');
    }
  }
}

main().then(() => {
  process.exit(0);
}).catch((err) => {
  console.error(err);
  process.exit(1);
});
