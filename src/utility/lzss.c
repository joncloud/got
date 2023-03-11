#include "lzss.h"

int lzss_read_uint16le(const char far* src, long* size, unsigned int* value);

int lzss_read_uint16le(const char far* src, long* size, unsigned int* value) {
  if (*size < 2) {
    return 0;
  }

  *value = src[0] | (src[1] << 8);

  return 1;
}

long lzss_decompress(char far* src, char far* dst, long size) {
  char data, x;
  unsigned int decompressed_size, ignored, written, control
  , upper_four_bits, count, offset;
  long remaining, i, b, j;

  remaining = size;
  written = 0;
  i = 0;

  // Each file's data begins with a UINT16LE value holding the
  // decompressed size, in bytes,
  if (!lzss_read_uint16le(src, &remaining, &decompressed_size)) {
    return 0;
  }
  src += 2;

  // followed by another UINT16LE value of unknown purpose
  // which should be ignored (the value is always 0x0001.)
  if (!lzss_read_uint16le(src, &remaining, &ignored)) {
    return 0;
  }
  src += 2;

  // The rest of the data decompresses as follows:

  // If the amount of data decompressed matches the target size, finish. Otherwise:
  while (written < decompressed_size) {
    if (remaining <= 0) {
      break;
    }

    // Read a byte from the input data
    data = *src;
    src += 1;
    remaining -= 1;


    // For each bit in the previous byte, from the least significant to the most:
    for (b = 0; b < 8; b += 1) {
      if (written >= decompressed_size) {
        break;
      }

      // If the bit is 1, copy a byte unchanged from the input data to the output
      if (((data >> b) & 0x1)) {
        dst[written++] = *src;
        src += 1;
        remaining -= 1;
      }
      // Otherwise the bit is zero:
      else {
        // Read a UINT16LE
        if (!lzss_read_uint16le(src, &remaining, &control)) {
          return 0;
        }
        src += 2;

        i += 2;

        // Add two to the upper (most significant) four bits, and
        // treat this value as the LZSS "count"
        upper_four_bits = control >> 12;
        count = upper_four_bits + 2;

        // Take the lower 12 bits and treat the value as the LZSS "offset"
        offset = control & 0xFFF;

        // Look back "offset" bytes into the newly decompressed data

        /**
         * Copy "count" bytes from here to the end of the newly decompressed data.
         * Take note that as each byte is copied to its destination, that new byte
         * may later become a source byte in this same copy operation. For example,
         * if "offset" is 1 (i.e. look back one byte) and the counter is 15, then
         * the last byte will be copied 17 times (15 + 2 = 17). This is because as
         * each byte is copied, it becomes the source byte for the next copy cycle.
         */
        for (j = 0; j < count; j += 1) {
          x = dst[written - offset];
          dst[written++] = x;
        }
      }
    }
  }

  return (long)decompressed_size;
}

long lzss_compress(long origsize, char far* src, char far* dst) {
  (void)origsize;
  (void)src;
  (void)dst;
  // TODO https://github.com/joncloud/got/issues/3
  return 0;
}
