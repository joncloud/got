CC=clang
LIBPATH=
INCLUDEPATH=src/utility
CFLAGS=-g -O0 -fno-signed-char
LINKFLAGS=-I $(INCLUDEPATH)

all: build/res

clean:
	rm -f build/*.o
	rm -f build/res

OBJ=build/res.o build/modern.o build/lzss.o build/res_abrt.o build/res_add.o build/res_crea.o\
	build/res_del.o build/res_enco.o build/res_find.o build/res_err.o build/res_extr.o\
	build/res_init.o build/res_int.o build/res_pack.o build/res_renm.o build/res_repl.o
build/res: $(OBJ)
	$(CC) $(LINKFLAGS) $(OBJ) -o build/res

build/%.o: src/utility/%.c
	$(CC) $(CFLAGS) -c $< -o build/$*.o
