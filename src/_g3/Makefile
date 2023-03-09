CC=tcc.exe
INCLUDEPATH=..\utility;..\digisnd;C:\tc\include
LIBPATH=
CFLAGS=+_g3.cfg -I$(INCLUDEPATH) -L$(LIBPATH)
AS=tasm.exe
AFLAGS=/MX /ZI /O
LINK=tlink.exe
LINKFLAGS=/s/c/d
OBJ=\
	3_back.obj\
	3_boss.obj\
	3_file.obj\
	3_grp.obj\
	3_image.obj\
	3_init.obj\
	3_main.obj\
	3_move.obj\
	3_movpat.obj\
	3_music.obj\
	3_object.obj\
	3_panel.obj\
	3_sbfx.obj\
	3_script.obj\
	3_shtmov.obj\
	3_shtpat.obj\
	3_sound.obj\
	3_sptile.obj

all: _g3.exe

clean:
	@del *.obj
	@del *.exe
	@del *.map

# Write the obj file to a temporary list,
# because DOS cannot send in more than 127
# characters worth of arguments.

_g3.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
C:\tc\lib\c0m.obj+
3_back.obj+
3_boss.obj+
3_file.obj+
3_grp.obj+
3_image.obj+
3_init.obj+
3_main.obj+
3_move.obj+
3_movpat.obj+
3_music.obj+
3_object.obj+
3_panel.obj+
3_sbfx.obj+
3_script.obj+
3_shtmov.obj+
3_shtpat.obj+
3_sound.obj+
3_sptile.obj+
..\utility\g_asm.obj+
..\utility\adlib.obj+
..\utility\fx_man.obj+
..\utility\joy.obj+
..\utility\lzss.obj+
..\utility\mu_man.obj+
..\utility\res_enco.obj+
..\utility\res_fall.obj+
..\utility\res_find.obj+
..\utility\res_init.obj+
..\utility\res_read.obj+
..\digisnd\digisnd.obj
_g3,_g3
C:\tc\lib\cm.lib
|

.c.obj:
	$(CC) $(CFLAGS) -c $<

.asm.obj:
	$(AS) $(AFLAGS) $&.asm,$&.obj
