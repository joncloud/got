CC=tcc.exe
INCLUDEPATH=c:\tc\include
LIBPATH=
CFLAGS=+utility.cfg -I$(INCLUDEPATH) -L$(LIBPATH)
AS=tasm.exe
AFLAGS=/MX /ZI /O
LINK=tlink.exe
LINKFLAGS=/s/c/d
OBJ=\
	adlib.obj\
	eg.obj\
	fx_man.obj\
	g_asm.obj\
	g_lib.obj\
	lvlbuild.obj\
	lzss.obj\
	mapgen.obj\
	mu_man.obj\
	pcxres.obj\
	pcx.obj\
	pcx_imp.obj\
	qsprite.obj\
	res.obj\
	res_abrt.obj\
	res_add.obj\
	res_crea.obj\
	res_del.obj\
	res_err.obj\
	res_extr.obj\
	res_enco.obj\
	res_fall.obj\
	res_find.obj\
	res_init.obj\
	res_pack.obj\
	res_read.obj\
	res_renm.obj\
	res_repl.obj\
	res_writ.obj\
	sbc.obj\
	sbvd.obj\
	spriteed.obj\
	th.obj\
	ximp.obj\
	xp_imp.obj\
	xmouse.obj

EXE=\
	lvlbuild.exe\
	mapgen.exe\
	pcxres.exe\
	pcx_imp.exe\
	qsprite.exe\
	res.exe\
	spriteed.exe\
	th.exe\
	xp_imp.exe
#	mixtest.exe
#	xsprite.exe

all: $(OBJ) $(EXE)

clean:
	@del *.obj
	@del *.map

lvlbuild.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
g_lib.obj+
lvlbuild.obj+
lzss.obj+
res_add.obj+
res_del.obj+
res_enco.obj+
res_fall.obj+
res_find.obj+
res_init.obj+
res_read.obj+
res_writ.obj+
xmouse.obj
lvlbuild,lvlbuild
c:\tc\lib\cm.lib
|

mapgen.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
eg.obj+
mapgen.obj
mapgen,mapgen
c:\tc\lib\cm.lib
|

mixtest.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
mixtest.obj
mixtest,mixtest
c:\tc\lib\cm.lib
|

pcx_imp.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
eg.obj+
pcx.obj+
pcx_imp.obj
pcx_imp,pcx_imp
c:\tc\lib\cm.lib
|

pcxres.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
pcxres.obj
pcxres,pcxres
c:\tc\lib\cm.lib
|

qsprite.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
g_lib.obj+
lzss.obj+
qsprite.obj+
res_del.obj+
res_enco.obj+
res_find.obj+
res_init.obj+
res_read.obj+
res_writ.obj+
xmouse.obj
qsprite,qsprite
c:\tc\lib\cm.lib
|

res.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
lzss.obj+
res.obj+
res_abrt.obj+
res_add.obj+
res_crea.obj+
res_del.obj+
res_enco.obj+
res_find.obj+
res_err.obj+
res_extr.obj+
res_init.obj+
res_pack.obj+
res_renm.obj+
res_repl.obj
res,res
c:\tc\lib\cm.lib
|

spriteed.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
g_lib.obj+
spriteed.obj+
ximp.obj+
xmouse.obj
spriteed,spriteed
c:\tc\lib\cm.lib
|

th.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
g_lib.obj+
sbc.obj+
sbvd.obj+
th.obj
th,th
c:\tc\lib\cm.lib
|

xp_imp.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
eg.obj+
pcx.obj+
xp_imp.obj
xp_imp,xp_imp
c:\tc\lib\cm.lib
|

xsprite.exe: $(OBJ)
	$(LINK) $(LINKFLAGS) @&&|
c:\tc\lib\c0m.obj+
xsprite.obj
xsprite,xsprite
c:\tc\lib\cm.lib
|

.c.obj:
	$(CC) $(CFLAGS) -c $<

.asm.obj:
	$(AS) $(AFLAGS) $&.asm,$&.obj
