#!/bin/bash

REPO_DIR=$(dirname $0 | realpath)

if [[ "$1" != "" ]]; then
  dosbox-x -conf shell.conf \
    -c "mount c ." \
    -c "c:" \
    -c "set PATH=%PATH%;C:\SRC\_G1;C:\SRC\_G2;C:\SRC\_G3;C:\SRC\UTILITY"\
    -c "$1"\
    -nopromptfolder \
    -fastlaunch
else
  dosbox-x -conf shell.conf \
    -c "mount c ." \
    -c "c:" \
    -c "set PATH=%PATH%;C:\SRC\_G1;C:\SRC\_G2;C:\SRC\_G3;C:\SRC\UTILITY"\
    -nopromptfolder \
    -fastlaunch
fi
