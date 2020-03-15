all: lisafrnk.com

lisafrnk.com: main.obj graphics.obj bmpdata.obj music.obj
	wcl -s -zls -0 -q -mt -oi -bcl=com main.obj graphics.obj bmpdata.obj music.obj @map
	@ren main.com lisafrnk.com

music.obj:
	wcl -s -zls -0 -q -mt -oi -bcl=com -c music.c

graphics.obj:
	wcl -s -zls -0 -q -mt -oi -bcl=com -c graphics.c

bmpdata.obj:
	wcl -s -zls -0 -q -mt -oi -bcl=com -c bmpdata.c

main.obj:
	wcl -s -zls -0 -q -mt -oi -bcl=com -c main.c
