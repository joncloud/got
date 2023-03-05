CC=tcc.exe
INCLUDEPATH=..\utility;..\digisnd;C:\tc\include
LIBPATH=
CFLAGS=+_g2.cfg -I$(INCLUDEPATH) -L$(LIBPATH)
AS=tasm.exe
AFLAGS=/MX /ZI /O
LINK=tlink.exe
LINKFLAGS=/s/c/d
OBJ=\
	2_back.obj\
	2_boss.obj\
	2_file.obj\
	2_grp.obj\
	2_image.obj\
	2_init.obj\
	2_main.obj\
	2_move.obj\
	2_movpat.obj\
	2_music.obj\
	2_object.obj\
	2_panel.obj\
	2_sbfx.obj\
	2_script.obj\
	2_shtmov.obj\
	2_shtpat.obj\
	2_sound.obj\
	2_sptile.obj

all: _g2.exe

clean:
	@del *.obj
	@del *.exe
	@del *.map

# Write the obj file to a temporary list,
# because DOS cannot send in more than 127
# characters worth of arguments.

_g2.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
C:\tc\lib\c0m.obj+
2_back.obj+
2_boss.obj+
2_file.obj+
2_grp.obj+
2_image.obj+
2_init.obj+
2_main.obj+
2_move.obj+
2_movpat.obj+
2_music.obj+
2_object.obj+
2_panel.obj+
2_sbfx.obj+
2_script.obj+
2_shtmov.obj+
2_shtpat.obj+
2_sound.obj+
2_sptile.obj+
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
_g2,_g2
C:\tc\lib\cm.lib
|

.c.obj:
	$(CC) $(CFLAGS) -c $<

.asm.obj:
	$(AS) $(AFLAGS) $&.asm,$&.obj
