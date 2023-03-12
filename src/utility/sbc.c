#include "sbc.h"

char ct_io_addx;
char ct_voice_status;

int sbc_check_card(void) {
  return 0;
}

int sbc_scan_int(void) {
  return 0;
}

int ctvm_init(void) {
  return 0;
}

void ctvm_speaker(int a) {
  (void)a;
}

void ctvm_stop(void) {

}

void ctvm_output(char far* buffer) {
  (void)buffer;
}

void ctvm_terminate(void) {

}

void sbfm_terminate(void) {

}

void start_music(void) {

}

int sbfm_read_status(void) {
  return 0;
}

void play_cmf_file(const char* filename) {
  (void)filename;
}

void sbfm_init(void) {

}
