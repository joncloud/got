#!/bin/bash

REPO_DIR=$(dirname $0 | realpath)

dosbox-x -conf shell.conf \
  -c "mount c ." \
  -c "c:" \
  -c "set PATH=%PATH%;C:\SRC\_G1;C:\SRC\_G2;C:\SRC\_G3;C:\SRC\UTILITY"\
  -nopromptfolder \
  -fastlaunch
