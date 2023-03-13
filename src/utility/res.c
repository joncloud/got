//Resource Manager
//Copyright 1993, Custom Software Engineering
//07-28-93
//==========================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "modern.h"

#ifdef modern

#else
#include <dos.h>
#include <conio.h>
#include <alloc.h>
#endif

#include "res_man.h"

void print_options(void) {
  printf("\r\n");
  printf("FORMAT: RES filename (C)reate\r\n");
  printf("                     (A)add src_filename res_name encode_flag\r\n");
  printf("                     (U)pdate src_filename res_name encode_flag\r\n");
  printf("                     (E)xtract res_name dest_filename\r\n");
  printf("                     (D)elete res_name\r\n");
  printf("                     (P)ack\r\n");
  printf("                     (R)ename res_oldname res_newname\r\n");
  printf("                     (B)reakout path\r\n");
  printf("                     (L)ist\r\n\r\n");

  printf("EXAMPLE: RES RESFILE.000 A GRAPHICS.DAT GRPDATA 1\r\n\r\n");
}

int main(int argc, char *argv[]) {
  int  ret, i;
  char filename[128];
  char name[1024];
  char fname[128];
  char path[256];
  FILE* fp;
  char ch;
  char fpath[21];

  char far* fb;

  printf("\r\n\r\nResource File Manager V1.2\r\n");
  printf("Copyright 1993, Custom Software Engineering\r\n");
  if (argc < 3) {
    print_options();
    exit(0);
  }
  fb = farmalloc(65000l);
  if (!fb) {
    printf("\r\n\r\nNot Enough Memory.\r\n\r\n");
    exit(0);
  }
  res_init(fb);

  strcpy(filename, argv[1]);

  if (!strcmpi(argv[2], "C")) {
    printf("\r\nCreating Resource File: %s...", filename);
    printf("%s\r\n\r\n", res_error(res_create(filename)));
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else if (!strcmpi(argv[2], "A")) {
    strcpy(fname, argv[3]);
    strncpy(name, argv[4], 8);
    name[8] = 0;
    i = atoi(argv[5]);
    printf("\r\nOpening Resource File: %s...", filename);
    printf("%s\r\n", res_error(res_open(filename)));
    printf("Adding: %s to Resource as: %s...", fname, name);
    ret = res_add_file(fname, name, i);
    printf("%s\r\n\r\n", res_error(ret));
    if (ret < 0) {
      res_abort();
    }
    else {
      res_close();
    }
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else if (!strcmpi(argv[2], "E")) {
    strcpy(fname, argv[4]);
    strncpy(name, argv[3], 8);
    name[8] = 0;
    printf("\r\nOpening Resource File: %s...", filename);
    printf("%s\r\n", res_error(res_open(filename)));
    printf("Extracting: %s from Resource as: %s...", name, fname);
    ret = res_extract_file(fname, name);
    printf("%s\r\n\r\n", res_error(ret));
    if (ret < 0) {
      res_abort();
    }
    else {
      res_close();
    }
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else if (!strcmpi(argv[2], "L")) {
    printf("\r\nOpening Resource File: %s...", filename);
    ret = res_open(filename);
    if (ret < 0) {
      printf("ERROR!\r\n\r\n");
      if (fb) {
        farfree(fb);
      }
      exit(0);
    }
    printf("%s\r\n", res_error(ret));
    printf("\r\n");
    printf("-----------------------------------------\r\n");
    printf("  NAME    OFFSET  LENGTH  ORIG LEN  KEY\r\n");
    printf("-----------------------------------------\r\n");
    for (i = 0; i < RES_MAX_ENTRIES; i++) {
      if (res_header[i].length) {
        strcpy(name, res_header[i].name);
        while (strlen(name) < 8) {
          strcat(name, " ");
        }
        printf("%s  %.6u  %.6u   %.6u   %.u\r\n", name,
          res_header[i].offset, res_header[i].length,
          res_header[i].original_size, res_header[i].key);
      }
    }
    res_abort();
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else if (!strcmpi(argv[2], "D")) {
    printf("\r\nOpening Resource File: %s...", filename);
    ret = res_open(filename);
    if (ret < 0) {
      printf("ERROR!\r\n\r\n");
      if (fb) {
        farfree(fb);
      }
      exit(0);
    }
    strncpy(name, argv[3], 8);
    name[8] = 0;
    printf("Deleteing Resource : %s...", name);
    printf("%s\r\n\r\n", res_error(res_delete_file(name)));
    res_close();
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else if (!strcmpi(argv[2], "P")) {
    printf("\r\nOpening Resource File: %s...", filename);
    ret = res_open(filename);
    if (ret < 0) {
      printf("\r\n\r\n");
      if (fb) {
        farfree(fb);
      }
      exit(0);
    }
    printf("%s\r\n\r\n", res_error(res_pack(filename)));
    res_abort();
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else if (!strcmpi(argv[2], "U")) {
    strcpy(fname, argv[3]);
    strncpy(name, argv[4], 8);
    name[8] = 0;
    i = atoi(argv[5]);
    printf("\r\nOpening Resource File: %s...", filename);
    printf("%s\r\n", res_error(res_open(filename)));
    printf("Updating: %s in Resource with: %s...", name, fname);
    ret = res_replace_file(fname, name, i);
    printf("%s\r\n\r\n", res_error(ret));
    if (ret < 0) {
      res_abort();
    }
    else {
      res_close();
    }
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else if (!strcmpi(argv[2], "R")) {
    printf("\r\nOpening Resource File: %s...", filename);
    ret = res_open(filename);
    if (ret < 0) {
      printf("ERROR!\r\n\r\n");
      if (fb) {
        farfree(fb);
      }
      exit(0);
    }
    strncpy(name, argv[3], 8);
    name[8] = 0;
    strncpy(fname, argv[4], 8);
    fname[8] = 0;
    printf("\r\nRenaming : %s to %s...", name, fname);
    printf("%s\r\n\r\n", res_error(res_rename_file(name,fname)));
    res_close();
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else if (!strcmpi(argv[2], "B")) {
    printf("\r\nOpening Resource File: %s...", filename);
    ret = res_open(filename);
    if (ret < 0) {
      printf("ERROR!\r\n\r\n");
      if (fb) {
        farfree(fb);
      }
      exit(0);
    }
    printf("\r\n");
    strcpy(fpath, argv[3]);
    ch = fpath[strlen(fpath) - 1];
    if (ch != '\\' && ch != ':') {
      strcat(fpath, "\\");
    }

    strcpy(path, fpath);
    strcat(path, "REPACK.BAT");
    fp = fopen(path, "wt");
    if (!fp) {
      printf("\r\nCannot Open REPACK.BAT\r\n\r\n");
      if (fb) {
        farfree(fb);
      }
      exit(0);
    }
    strcpy(path, "DEL ");
    strcat(path, fpath);
    strcat(path, filename);
    strcat(path, "\n");
    fputs(path, fp);
    strcpy(path, "RES ");
    strcat(path, fpath);
    strcat(path, filename);
    strcat(path, " C \n");
    fputs(path, fp);
    for (i = 0; i < RES_MAX_ENTRIES; i++) {
      if (res_header[i].length) {
        strcpy(name, res_header[i].name);
        strcpy(fname, res_header[i].name);
        while (strlen(name) < 8) {
          strcat(name, " ");
        }
        strcpy(path, fpath);
        strcat(path, fname);
        strcat(path, ".DAT");
        strupr(path);
        printf("Extracting: %s to %s...", name, path);
        ret = res_extract_file(path, fname);
        printf("%s\r\n", res_error(ret));
        strcpy(path, "RES ");
        strcat(path, filename);
        strcat(path, " A ");
        strcat(path, fpath);
        strcat(path, fname);
        strcat(path, ".DAT ");
        strcat(path, fname);
        if (res_header[i].key) {
          strcat(path, " 1\n");
        }
        else {
          strcat(path, " 0\n");
        }
        fputs(path, fp);
      }
    }
    printf("\r\n\r\nDone.\r\n\r\n");
    fclose(fp);
    res_close();
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  else {
    print_options();
    if (fb) {
      farfree(fb);
    }
    exit(0);
  }
  return 0;
}
