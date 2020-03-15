#include "graphics.h"
#include "bmpdata.h"
#include "music.h"

/* Return last key in input buffer, return 0 if buffer empty */
extern int get_key(void);
#pragma aux get_key =	\
	"xor bx,bx"			\
	"mov ah,0x01"		\
	"int 0x16"			\
	"je donzo"			\
"more_key:"				\
	"xor ah,ah"			\
	"int 0x16"			\
	"mov bx,ax"			\
	"mov ah,0x01"		\
	"int 0x16"			\
	"jne more_key"		\
"donzo:"				\
	"mov ax,bx"			\
value [ ax ]			\
modify [ bx ];

/* Put one character on screen */
extern void eputc(char c);
#pragma aux eputc =		\
	"mov ah, 06h"		\
	"int 21h"			\
parm [ dl ]				\
modify [ ax ];

void eputs(const char* str)
{
	while(*str) {
		eputc(*str);
		str++;
	};
}

int main() {
	int key, frame;

	set_cga();
	draw_bmp();
	music_select(0);
	frame=0;

	get_key(); /* Make sure buffer is empty */

	while(1) {
		wait_vsync();

		if (frame>80)
			music_process();

		key = get_key();
		if (key == 0x011B)
			break;

		frame++;

	}

	music_pause();
	reset_display();

	eputs ("Snigelson March 2020");

	return 0;
}
