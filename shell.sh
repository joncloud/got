#!/bin/bash

REPO_DIR=$(dirname $0 | realpath)

dosbox-x -conf shell.conf \
  -c "mount c ." \
  -c "c:" \
  -nopromptfolder \
  -fastlaunch
