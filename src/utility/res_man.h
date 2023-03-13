#ifndef RES_MAN_H_
#define RES_MAN_H_

#include <stdio.h>
#include "modern.h"

typedef struct{
  /**
   * The name of the resource in the archive. This is what
   * is used to find, extract and manipulate records.
   */
  char name[9];
  /**
   * The offset within the archive that this entry's data is at.
   */
  uint32_t offset;
  /**
   * The total length of the data within the archive.
   */
  uint32_t length;
  /**
   * The total length of the data after uncompressing.
   * This value is the same as @ref length when data is
   * not compressed.
   */
  uint32_t original_size;

  /**
   * This stores a boolean value of 0 when data is not
   * compressed, and 1 when data is compressed using
   * an LZSS algorithm.
   */
  uint16_t key;
} RES_HEADER;

#define RES_MAX_ENTRIES 256  //max # of elements

#define RES_NO_ERROR         0
#define RES_NOT_ACTIVE      -1
#define RES_CANT_OPEN       -2
#define RES_CANT_CLOSE      -3
#define RES_CANT_WRITE      -4
#define RES_CANT_READ       -5
#define RES_ENTRY_NOT_FOUND -6
#define RES_ALREADY_OPEN    -7
#define RES_FULL            -8
#define RES_CANT_SEEK       -9
#define RES_NOT_OPEN        -10
#define RES_CANT_CREATE     -11
#define RES_CANT_FIND       -12
#define RES_ALREADY_EXISTS  -13
#define RES_CANT_OPEN_SRC   -14
#define RES_CANT_OPEN_DST   -15
#define RES_SRC_TOO_LARGE   -16
#define RES_OUT_OF_MEMORY   -17

/**
 * The file pointer to the active resource archive.
 */
extern FILE*      res_fp;

/**
 * The array of resource entries for the active resource archive.
 */
extern RES_HEADER res_header[RES_MAX_ENTRIES];

/**
 * Stores whether or not there is an active resource archive.
 */
extern int        res_active;

/**
 * Stores whether or not the active resource archive has unsaved changes.
 */
extern int        res_changed;

/**
 * Stores a reference to a data buffer that can be used for LZSS
 * compression / decompression. This is not owned by the resource manager.
 */
extern char far*  res_lzss_buff;

/**
 * Initializes resource manager. This function should be
 * called before opening a resource archive.
 * @param buff A memory buffer used for extracting and
 * decompressing contents. Typically this buffer should
 * be at least 18,000 bytes long.
 */
void res_init(char far* buff);

/**
 * Opens a resource archive.
 * @param filename The path to the resource archive to open.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_open(const char* filename);

/**
 * Closes a resource archive. If any contents were changed within the
 * archive they will be flushed out to disk.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_close(void);

/**
 * Encodes the memory buffer with a simple XOR algorithm with @ref key.
 * The function is used to encode the header entries in the resource
 * archive. This is only ever called with a @ref key of 128.
 * @param buff The memory buffer to encode.
 * @param len The length of the memory buffer.
 * @param key The key for XORing the data.
 */
void res_encrypt(char far* buff, long len, unsigned char key);

/**
 * Decodes the memory buffer with a simple XOR algorithm with @ref key.
 * The function is used to decode the header entries in the resource
 * archive. This is only ever called with a @ref key of 128.
 * @param buff The memory buffer to decode.
 * @param len The length of the memory buffer.
 * @param key The key for XORing the data.
 */
void res_decrypt(char far* buff, long len, unsigned char key);

/**
 * This function should be called when a program needs to abort
 * in order to clean up any internal resources to the resource
 * manager.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_abort(void);

/**
 * Creates a new resource archive located at @ref filename. Upon
 * successful creation, the archive is then opened using @ref res_open.
 * @param filename The path to where the archive should be created.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_create(const char* filename);

/**
 * Compresses the data in @ref buff using LZSS.
 * @param buff A memory location with data to compress.
 * @param length How many bytes long @ref buff is.
 * @returns The total number of bytes the compressed size is.
 */
long res_encode(char far* buff, long length);

/**
 * Decompresses the data in @ref buff with LZSS.
 * @param buff A memory location with data to decompress.
 * @param length How many bytes long @ref buff is.
 * @returns The total number of bytes the decompressed size is.
 */
long res_decode(char far *buff, long len);

/**
 * Finds the resource index by the name specified at @ref name.
 * @param name The name of the resource to find.
 * @returns If the return value is >= 0, then it is the index in the
 * @ref res_header array, otherwise returns an enumeration. Use the
 * `RES_*` constants, or @ref res_error to determine a text description.
 */
int res_find_name(const char* name);

/**
 * Finds the first resource index for an empty entry.
 * @returns If the return value is >= 0, then it is the index in the
 * @ref res_header array, otherwise returns an enumeration. Use the
 * `RES_*` constants, or @ref res_error to determine a text description.
 */
int res_find_empty(void);

/**
 * Writes a new resource to the archive.
 * @param name The name of the resource.
 * @param buff The memory location with the data for the resource.
 * @param length The total number of bytes of data to write.
 * @param encode_flag 1 when the data should be compressed with LZSS, otherwise 0.
 * @returns 1 if the entry was successfully written, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text description.
 */
int res_write(const char* name, char far* buff, long length, int encode_flag);

/**
 * Reads an existing resource from the archive into the buffer. If the resource is
 * compressed, it is uncompressed.
 * @param name The name of the resource.
 * @param buff The memory location to read the resource contents into.
 * @returns When the value is >= 0, then the total number of bytes that were read,
 * otherwise returns an enumeration. Use the `RES_*` constants, or @ref res_error
 * to determine a text description.
 */
long res_read(const char* name, char far* buff);

/**
 * Allocates a new block of memory the size of the given resource entry,
 * and reads it into the memory block.
 * @param name The name of the resource to read.
 * @returns The memory block if able to read, otherwise 0.
 */
void far* res_falloc_read(const char* name);

/**
 * Adds a file from disk to the resource archive.
 * @param fname The name of the file to read from on disk.
 * @param name The name of the resource entry to create in the archive.
 * @param encode_flag 1 when the data should be compressed with LZSS, otherwise 0.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_add_file(const char* fname, const char* name, int encode_flag);

/**
 * Extracts a file from the resource archive to disk.
 * @param fname The name of the file to create on disk.
 * @param name The name of the resource entry to extract from the archive.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_extract_file(const char* fname, const char* name);

/**
 * Deletes a file from the resource archive.
 * @param name The name of the resource entry to delete.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_delete_file(const char* name);

/**
 * Rearranges the entries in the opened resource archive, and aligns
 * them at the beginning of the file removing fragmentation. Upon
 * successful rearrangement, the new resource archive is opened.
 * @param filename The new resource archive to create.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_pack(const char* filename);

/**
 * Updates the existing file in the resource archive with the contents on disk.
 * @param fname The name of the file on disk to load from.
 * @param name The name of the resource entry to update.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_replace_file(const char* fname, const char* name, int encode_flag);

/**
 * Renames an entry in the resource archive to a new name.
 * @param oldname The current name of the resource entry.
 * @param newname The desired name of the resource entry.
 * @returns Returns 1 upon success, otherwise returns an enumeration.
 * Use the `RES_*` constants, or @ref res_error to determine a text
 * description.
 */
int res_rename_file(const char* oldname, const char* newname);

/**
 * Gets a text description for the error number.
 * @param num The error number.
 * @returns A string with the text description.
 */
char* res_error(int num);

// TODO these are not actively being used in the codebase.
// long res_read_element(const char* name, char far* buff, long offset, long size);
// long res_length(char *name);
// long res_original_size(char *name);

#endif
