#include "bmpdata.h"
#include "graphics.h"
#include <conio.h>

#define CGA_EVEN_BASE (0xB8000000L)
#define CGA_ODD_BASE (0xB8002000L)
/* #include <dos.h> */

#define WIDTH (200/4)
#define MARGIN (((320/4)-WIDTH)/2)

void do_lines(const unsigned char* src, unsigned char far* dst)
{
	int y;
	int x;
	register unsigned char cc,nc;

	dst += MARGIN;

	cc=*src;
	nc=*(src+1);
	src+=2;

	y=100;
	do {
		x=WIDTH;
		do {
			*dst=cc;
			dst++;
			if(!(--nc)) {
				cc=*src;
				nc=*(src+1);
				src+=2;
			}
		} while (--x);
		dst += MARGIN*2;
		wait_vsync_safe();
	} while (--y);
}

void draw_bmp()
{
	do_lines(bmp_even, (unsigned char far*)CGA_EVEN_BASE);
	do_lines(bmp_odd, (unsigned char far*)CGA_ODD_BASE);
}
