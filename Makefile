all: main.com

main.com: main.obj graphics.obj bmpdata.obj music.obj
	wcl -s -zls -0 -q -mt -oi -bcl=com main.obj graphics.obj bmpdata.obj music.obj @map

music.obj:
	wcl -s -zls -0 -q -mt -oi -bcl=com -c music.c

graphics.obj:
	wcl -s -zls -0 -q -mt -oi -bcl=com -c graphics.c

bmpdata.obj:
	wcl -s -zls -0 -q -mt -oi -bcl=com -c bmpdata.c

main.obj:
	wcl -s -zls -0 -q -mt -oi -bcl=com -c main.c
