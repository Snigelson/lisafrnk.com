## `LISAFRNK.COM`

Shows an ＡＥＳＴＨＥＴＩＣ image and plays a soothing tune.

Demo: https://www.youtube.com/watch?v=whH76m4ecGA

### Build requirements

Watcom. Only tested with verstion 1.9.

To generate bitmap data you will need a more modern computer with python.
Run `python cgaconvb.py floral_shoppe.png >bmpdata.c`.

Then, on your less modern computer (or under an emulator for all I care),
just run `wmake` in this directory.

### Running requirements

This program should run on anything. And by anything, I mean any PC or
PC Compatible with CGA graphics. Since the binary is under 8&nbsp;kB
in size, it should be able to run on the lowliest of these,
the 16&nbsp;kB IBM PC (if a CGA card is installed, of course).

When running in Dosbox, the music seems to run too fast. The music is
synchronized to the frame rate, so maybe my Dosbox just doesn't run at
60 Hz. Future me will test this.

### Modifying stuff

To change the graphics, you need to replace `floral_shoppe.png` with a
4 color indexed palette PNG file, 200x200 px in size. You can use a
different width by modifying some defines in `graphics.c`.

To change the music, well you're gonna have to figure out `music.c`.
