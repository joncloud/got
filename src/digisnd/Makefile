CC=tcc.exe
INCLUDEPATH=c:\tc\include
CFLAGS=+digisnd.cfg -I$(INCLUDEPATH)

all: digisnd.obj

clean:
	@del *.obj
	@del *.map

digisnd.obj: digisnd.c digisnd.h digisnd.cfg
	$(CC) $(CFLAGS) -c digisnd.c
