#ifndef SBCVOICE_H_
#define SBCVOICE_H_

char far* load_voice_file(char* filename);
int init_sbv(void);
void output_voice(char far* buffer);

#endif
