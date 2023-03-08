#ifndef RES_MAN_H_
#define RES_MAN_H_

typedef struct{
  char name[9];
  long offset;
  long length;   //original len
  long original_size;
  int  key;
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

extern FILE *res_fp;
extern RES_HEADER res_header[RES_MAX_ENTRIES];
extern int res_active;
extern int res_changed;
extern char far* res_lzss_buff;

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
void res_encrypt(char far* buff, long len, char key);

/**
 * Decodes the memory buffer with a simple XOR algorithm with @ref key.
 * The function is used to decode the header entries in the resource
 * archive. This is only ever called with a @ref key of 128.
 * @param buff The memory buffer to decode.
 * @param len The length of the memory buffer.
 * @param key The key for XORing the data.
 */
void res_decrypt(char far* buff, long len, char key);

int  res_abort(void);
int  res_create(char *filename);
long res_encode(char far *buff,long length);
long res_decode(char far *buff, long len);
int  res_find_name(char *name);
int  res_find_empty(void);
int  res_write(char *name,char far *buff,long length,int encode_flag);
long res_read(char *name,char far *buff);
long res_read_element(char *name,char far *buff,long offset,long size);
void far *res_falloc_read(char *name);
int  res_add_file(char *fname,char *name,int encode_flag);
int  res_extract_file(char *fname,char *name);
int  res_delete_file(char *name);
int  res_pack(char *filename);
int  res_replace_file(char *fname,char *name,int encode_flag);
long res_length(char *name);
long res_original_size(char *name);
int  res_rename_file(char *oldname,char *newname);

/**
 * Gets a text description for the error number.
 * @param num The error number.
 * @returns A string with the text description.
 */
char* res_error(int num);

#endif
