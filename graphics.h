void set_cga(void);
#pragma aux set_cga =	\
	"mov ax,0x0004"		\
	"int 0x10"			\
modify [ ax ];

void reset_display(void);
#pragma aux reset_display =	\
	"mov ax,0x0002"		\
	"int 0x10"			\
modify [ ax ];

extern void wait_vsync(void);
#pragma aux wait_vsync =	\
"l0:"					\
	"mov dx,0x3da"		\
	"in al, dx"			\
	"test al, 0x08"		\
	"je l0"				\
"l1:"					\
	"in al, dx"			\
	"test al, 0x08"		\
	"jne l1"			\
modify [ al dx ];

void draw_bmp();


