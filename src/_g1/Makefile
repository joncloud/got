CC=tcc.exe
INCLUDEPATH=..\utility;..\digisnd;C:\tc\include
LIBPATH=
CFLAGS=+_g1.cfg -I$(INCLUDEPATH) -L$(LIBPATH)
AS=tasm.exe
AFLAGS=/MX /ZI /O
LINK=tlink.exe
LINKFLAGS=/s/c/d
OBJ=\
	1_back.obj\
	1_boss1.obj\
	1_file.obj\
	1_grp.obj\
	1_image.obj\
	1_init.obj\
	1_main.obj\
	1_move.obj\
	1_movpat.obj\
	1_music.obj\
	1_object.obj\
	1_panel.obj\
	1_sbfx.obj\
	1_script.obj\
	1_shtmov.obj\
	1_shtpat.obj\
	1_sound.obj\
	1_sptile.obj

all: _g1.exe

clean:
	@del *.obj
	@del *.exe
	@del *.map

# Write the obj file to a temporary list,
# because DOS cannot send in more than 127
# characters worth of arguments.

_g1.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
C:\tc\lib\c0m.obj+
1_back.obj+
1_boss1.obj+
1_file.obj+
1_grp.obj+
1_image.obj+
1_init.obj+
1_main.obj+
1_move.obj+
1_movpat.obj+
1_music.obj+
1_object.obj+
1_panel.obj+
1_sbfx.obj+
1_script.obj+
1_shtmov.obj+
1_shtpat.obj+
1_sound.obj+
1_sptile.obj+
..\utility\g_asm.obj+
..\utility\adlib.obj+
..\utility\fx_man.obj+
..\utility\lzss.obj+
..\utility\mu_man.obj+
..\utility\res_enco.obj+
..\utility\res_fall.obj+
..\utility\res_find.obj+
..\utility\res_init.obj+
..\utility\res_read.obj+
..\digisnd\digisnd.obj
_g1,_g1
C:\tc\lib\cm.lib
|

.c.obj:
	$(CC) $(CFLAGS) -c $<

.asm.obj:
	$(AS) $(AFLAGS) $&.asm,$&.obj
