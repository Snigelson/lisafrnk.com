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
;

/* Like above but pushes DX */
extern void wait_vsync_safe(void);
#pragma aux wait_vsync_safe =	\
	"push dx"			\
"l0:"					\
	"mov dx,0x3da"		\
	"in al, dx"			\
	"test al, 0x08"		\
	"je l0"				\
"l1:"					\
	"in al, dx"			\
	"test al, 0x08"		\
	"jne l1"			\
	"pop dx"			\
;

void draw_bmp();


