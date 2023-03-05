#!/bin/sh

if [[ "$1" = "clean" ]]; then
  CLEAN="clean "
else
  CLEAN=""
fi

export INPUT_PROGRAMS=$(cat <<-END
$/turbo-asm/2.01:c:\tasm
$/turbo-c++/3.00:c:\tc
src:c:\src
build:c:\build
END
)

export INPUT_RUN=$(cat <<-END
c:
cd \src\digisnd
make ${CLEAN}> c:\build\build.txt
cd \src\utility
make ${CLEAN}>> c:\build\build.txt
cd \src\_g1
make ${CLEAN}>> c:\build\build.txt
cd \src\_g2
make ${CLEAN}>> c:\build\build.txt
cd \src\_g3
make ${CLEAN}>> c:\build\build.txt
END
)

export INPUT_CONF=$(cat <<-END
[dosbox]
memsize=256

[cpu]
cycles=max
turbo=true
END
)

node ../dos-build-action/src/index.js > /dev/null
cat ./build/BUILD.TXT
