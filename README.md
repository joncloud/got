# God of Thunder (MS-DOS)

This is a copy of the MS-DOS Game God of Thunder. The intention of this project is to build and compile the game in order to preserve compatibility with its original system requirements.

## Files

## _G1.EXE

This program is contains all of the code to play the first episode - Part I: Serpent Surprise.

## _G2.EXE

This program is contains all of the code to play the first episode - Part II: Non-Stick Nognir.

## _G3.EXE

This program is contains all of the code to play the first episode - Part II: Lookin' for Loki.

## GOTRES.DAT

This contains all of the game assets necessary to play the game episodes.

## LVLBUILD.EXE

This program is used to manipulate screen data within `GOTRES.DAT`. By default it loads `GOTRES.DAT` out of `C:\GOT\GOTRES.DAT` and edits Episode 1's data (`SDAT1`).

### Arguments

* `/AREA:num` - Overrides the Episode screen data to load, e.g., num=2 will load `SDAT2`
* `/FILE:name` - Overrides the path to the `GOTRES.DAT` file to load and save

### Keyboard Shortcuts

* F1 - Save
* F2 - Load
* F3 - BGTILE
* F4 - Fill
* F5 - Quit
* CTRL+F1 - Add Actor
* CTRL+F2 - Del Actor
* CTRL+F3 - Flip
* CTRL+F4 - Val
* ALT+F1 - Inc
* ALT+F2 - Dec
* ALT+Left Click - Place
* ALT+Right Click - Delete
* SHIFT+F1 - Music
* SHIFT+F2 - Redraw
* SHIFT+F3 - Edit Wrap
* SHIFT+F4 - Pack Wrap
* Left - Shift Tile Palette Left
* Right - Shift Tile Palette Right

## RES.EXE

This program provides an interface for managing the `GOTRES.DAT` archive.

### Arguments

RES.EXE is a command based program, which has dynamic arguments. All commands first argument is filename, e.g., `RES.EXE [filename]`. When no arguments are passed, a help dialog is displayed. The following are the various argument combinations to run the program.

* `C` - Creates a new archive at `[filename]`
* `A [src_filename] [res_name] [encode_flag]` Adds a file on disk (`[src_filename]`) to the archive with a name of `[res_name]`. When the `[encode_flag]` is non-zero, then the resource will be compressed using LZSS compression before adding to the archive.
* `U [src_filename] [res_name] [encode_flag]` - Updates an existing entry (`[res_name]`) within the archive from a file on disk (`[src_filename]`). When the `[encode_flag]` is non-zero, then the resource will be compressed using LZSS compression before adding to the archive.
* `E [res_name] [dest_filename]` - Extracts a resource (`[res_name]`) from the archive to disk at `[dest_filename]`.
* `D [res_name]` - Deletes a resource (`[res_name]`) from the archive.
* `P` - Does nothing.
* `R [res_oldname] [res_newname]` - Renames a resource (`[res_oldname]`) in the archive with a new name (`[res_newname]`).
* `B` - Extracts all resources with a .DAT file extension.
* `L` - Lists all entries in the archive.

## References

### Original Source Distribution

This is the source code for the 1994 DOS shareware game God of Thunder (Turbo
C/Assembler).

It is a good example of how not to code in C. I was once told it was impressive
that it actually worked, so that's something.

This is only the main source code here. I have released it to the public
domain. Do whatever you want with it. It will not compile as-is. There is at
least 1 3rd party compression file missing and the sound/music code was a
licensed library that is not open source. The opening/high score/game select
screens are also not included.

The game itself can be found for free on Steam. The graphics of the game are
not open source and may not be used in any commercial projects. The music and
sound effects are public domain but I would appreciate credit to "Roy Davis" if
you use any of the music. He was my father and he passed away in 2011. The
music and other stuff is in GOTstuff.zip.

Sorry, but I cannot offer any support.

#### Features

* Very questionable C code (to put it nicely)

Original source: https://sourceforge.net/projects/god-of-thunder-1994-dos-game/

Released on: 2020-03-27 (source only), 2020-07-19 (sound/music/utility)
