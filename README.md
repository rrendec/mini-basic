This is the CIP-01 factory ROM. CIP-01 is a Romanian clone of the ZX
Spectrum 48K, manufactured in 1988-1989. The ROM size is 4 KB, and it
contains the MINI-BASIC interpreter, which includes a minimalistic
version of BASIC and tape loader code. The original Spectrum 16 KB ROM
could be loaded from tape.

Originally, the ROM was stored in two MMN2616 chips. These are 2Kx8 PROM
chips manufactured by Microelectronica. They are pin compatible with the
M2716 EPROM but lack the UV erase window.

Because I didn't have an EPROM programmer/reader around, I recovered the
contents using an Arduino UNO board wired directly to the PROM chips.
Due to the limited number of pins on the Arduino UNO (and because I
wanted to keep the design simple), I could only wire 10 address lines,
therefore addressing 1 KB. The 11th address line was hard-wired on the
breadboard, so I had to extract separately each half of the 2 KB of
contents.

This repository includes the extracted images in Intel hex format - two
images for each half (bank) of each PROM chip - 4 images total. The PROM
chips are factory marked E0001 and E0002, likely to be able to tell them
apart during PCBA manufacturing (this also suggests they were factory
programmed). I preserved the original labels in the image file names.
The repository also includes the Arduino sketch I used for extraction.

The included Makefile can be used to convert the images to binary format
on a standard Linux system, as well as to create a .rom file that can be
used with the [Fuse](https://fuse-emulator.sourceforge.net/) emulator.
To run the ROM in Fuse, go to Options -> Select ROMs -> Machine ROMs ->
Spectrum 48K... and select mini-basic.rom. Then reset the machine to
boot the MINI-BASIC ROM.
