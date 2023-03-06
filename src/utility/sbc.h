#ifndef SBC_H_
#define SBC_H_

typedef struct VOCHDR {
  // char signature[19];    // "Creative Voice File"
  // char signature2;       // 0x1A
  // unsigned int size;     // Size of the main header. Usually 0x001A
  // unsigned int version;  // Version number. Usually 0x010A (0x0A 0x01) for the old format, or 0x0114 for the new format
  // unsigned int checksum; // This should equal ~version + 0x1234
  int voice_offset; // TODO
} VOCHDR;

extern char ct_io_addx;
extern char ct_voice_status;

int sbc_check_card(void);
int sbc_scan_int(void);
int ctvm_init(void);
void ctvm_speaker(int a);
void ctvm_stop(void);
void ctvm_output(char far* buffer);
void ctvm_terminate(void);
void sbfm_terminate(void);
void start_music(void);
int sbfm_read_status(void);
void play_cmf_file(const char* filename);
void sbfm_init(void);

#endif
