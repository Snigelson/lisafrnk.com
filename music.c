/* Replace most header files with own size-optimized implementations? */
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>

/* Use google to find out how to use intrinsic versions of inp, outp, interrupt, etc.
 * Maybe roll out own versions since the intrinsic versions handle low addresses inefficiently. */

/* TODO: Optimize setfreq */
#define speaker_setup() \
  outp( 0x43, 0xB6 )
#define speaker_mute() \
  outp( 0x61, inp( 0x61 ) & 0xFC )
#define speaker_unmute() \
  outp( 0x61, inp( 0x61 ) | 0x03 )
#define setfreq(_freq) do { \
    outp( 0x42, _freq&0xFF ); \
    outp( 0x42, (_freq>>8)&0xFF ); \
  } while(0)

static unsigned int notes[] = {
/* Provisoning for more notes */
/* 0 */
/* NONE */ 5, /* Silence */
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* 12 */
/* C  */ 9121,
/* C# */ 8609,
/* D  */ 8126,
/* D# */ 7670,
/* E  */ 7239,
/* F  */ 6833,
/* F# */ 6449,
/* G  */ 6087,
/* G# */ 5746,
/* A  */ 5423,
/* A# */ 5119,
/* B  */ 4831,
/* 24 */
/* C  */ 4560,
/* C# */ 4304,
/* D  */ 4063,
/* D# */ 3834,
/* E  */ 3619,
/* F  */ 3416,
/* F# */ 3224,
/* G  */ 3043,
/* G# */ 2873,
/* A  */ 2711, /* ~440 */
/* A# */ 2559,
/* B  */ 2415,
/* 36 */
/* C  */ 2280,
/* C# */ 2152,
/* D  */ 2031,
/* D# */ 1917,
/* E  */ 1809,
/* F  */ 1715,
/* F# */ 1612,
/* G  */ 1521,
/* G# */ 1436,
/* A  */ 1355,
/* A# */ 1292,
/* B  */ 1207,
/* 48 */
/* C  */ 1140,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 1000,
/* NONE */ 0 /* Do not use! */
/* 64 */
};

/* ==== TRACKS ==== */

/*
	ttnnnnnn	-	tt is type (see below), nnnnnn is note index from table above (except 111111 which is silence)
	dddddddd	-	Duration in frames
	xxxxxxxx	-	Effect data, optional for some events

| tt | description                            | Third byte
+----+----------------------------------------+---------------
| 00 | Note on (or pause if note = 111111)    | Omitted
| 01 | Arpeggio                               | ppppdddd - Pattern number and note duration
| 10 | Glissando                              | Glissando offset/tick (calculated at compile time)
| 11 | Maybe "other effects"                  | Depends on effect type

Each byte in arpeggio pattern defines an offset from the base note. Pattern ends with ARPPAT_END

Other effects (tt = 11):

| 11nnnnnn | description                            | Third byte
+----------+----------------------------------------+---------------
|   000000 | Noise - simply randomize note          |
|          | each frame                             |

*/

#define TRACK_END NULL
#define PATTERN_END 0xFF
#define ARPPAT_END 0xFF

#define TYPE_MASK 0xC0
#define NOTE_MASK 0x3F
#define SILENCE 0

#define NOTE 0x00
#define ARPEGGIO 0x40
#define GLISSANDO 0x80
#define OTHER 0xC0

#define ARP(_pat, _dur) ((_pat<<4)|_dur)

/* Start track 0 */

#define PAUSE SILENCE

/* QNL=40 sounds good in Dosbox, but is too slow on real CGA. I have a
 * PAL/NTSC type hunch, because 33 sounds pretty good on my PC... */
#define QNL 40
#define ENL (QNL/2)
#define HNL (QNL*2)

/* ARPEGGIO|BASE, LEN, ARP(PATTERN, NOTE DURATION) */

static const unsigned char pattern0[] = {
	NOTE|34, QNL+ENL-1,
/*	ARPEGGIO|(34-19), QNL, ARP(0, 1),
	NOTE|34, ENL-1,*/

	NOTE|PAUSE, 1,
	NOTE|41, ENL+QNL+ENL-1,
	NOTE|PAUSE, 1,

	NOTE|41, ENL-1,
	NOTE|PAUSE, 1,
	NOTE|39, ENL-1,
	NOTE|PAUSE, 1,
	NOTE|37, ENL-1,
	NOTE|PAUSE, 1,
	NOTE|36, ENL-1,
	NOTE|PAUSE, 1,
	NOTE|36, ENL+QNL-1,
	NOTE|PAUSE, 1,

	PATTERN_END
};

static const unsigned char pattern1[] = {
	NOTE|37, ENL-1,
	NOTE|PAUSE, 1,
	NOTE|34, ENL+HNL+QNL-1,
	NOTE|PAUSE, 1,

	NOTE|46, ENL-1,
	NOTE|PAUSE, 1,
	NOTE|44, ENL+HNL+QNL-1,
	NOTE|PAUSE, 1,

	NOTE|34, ENL-1,
	NOTE|PAUSE, 1,
	NOTE|37, ENL-1,
	NOTE|PAUSE, 1,

	PATTERN_END
};

static const char pattern2[] = {
	NOTE|34, ENL-1,
	NOTE|PAUSE, 1,
	NOTE|41, ENL+HNL-1,
	NOTE|PAUSE, 1,

	NOTE|PAUSE, ENL,
	ARPEGGIO|34-12, ENL-1, ARP(1,1),
	NOTE|PAUSE, 1,
	ARPEGGIO|34-12, ENL, ARP(1,1),

	NOTE|PAUSE, ENL,
	ARPEGGIO|34-12, ENL-1, ARP(2,1),
	NOTE|PAUSE, 1,
	ARPEGGIO|34-12, ENL, ARP(2,1),

	NOTE|PAUSE, QNL,

	PATTERN_END
};

static const char* track0[] = {
	pattern0,
	pattern1,
	pattern0,
	pattern2,
	TRACK_END
};

/* End track 0 */

/* ==== List of tracks ==== */
static const unsigned char** tracks[] = {
	track0
};

/* ==== Arpeggio patterns ==== */
static unsigned char arp00[] = {
	0, 19, ARPPAT_END
};

static unsigned char arp01[] = {
	0, 3, 7, 10, ARPPAT_END
};

static unsigned char arp02[] = {
	0, 5, 9, 12, ARPPAT_END
};

static unsigned char* arppats[] = {
	arp00, arp01, arp02
};






/* Pointer to start of current track */
static unsigned char** curtrk;
/* Pointer to current position in track */
static unsigned char** trkptr;
/* Pointer to current position in pattern */
static unsigned char* patptr;

/* Countdown of ticks until next event */
static char tickctr;

/* Current arpeggio pattern */
static char arppat;
/* Pointer to current location in arpeggio pattern */
static char arpptr;
/* Arpeggio base note */
static char arpbase;
/* Arpeggio tick counter */
static char arpctr;
/* Arpeggio speed */
static char arpspd;

/* Current note frequency */
static unsigned int curfreq;
/* Glissando offset/tick */
static signed char glissoffs;

/* Current active effect */
static char effect;

void music_select(int track)
{
	register unsigned char** d;
	speaker_setup();
	speaker_unmute();
	d = trkptr = curtrk = tracks[track];
	patptr = (*d)-1;
	tickctr = 1;
	effect = NOTE;
}

void music_pause(void)
{
	speaker_mute();
}

void music_play(void)
{
	speaker_unmute();
}

/* Call every tick or frame or whatever */
void music_process(void)
{
	register unsigned char d;
	register unsigned int i;

	if (--tickctr) {
		/* Handle effects and then return */
		switch (effect) {
/*		case NOTE:
			break; */
		case ARPEGGIO:
			if (!--arpctr) {
				/* Next note in arpeggio sequence */
			arppat_restart:
				d = arppats[arppat][++arpptr];
				if (d==ARPPAT_END) {
					arpptr=-1;
					goto arppat_restart;
				}
				i = curfreq = notes[arpbase+d];
				setfreq(i);
				arpctr = arpspd;
			}
			break;
		case GLISSANDO:
			i = curfreq += glissoffs;
			setfreq(i);
			break;
		case OTHER:
			break;
		}
		return;
	}

	/* tickctr is 0, get next sound event */
get_sound_event:
	d = *++patptr;
	if (d == PATTERN_END) {
		/* Sound event is PATTERN_END, go to next pattern */
		if (*(++trkptr) == TRACK_END) {
			/* Track is over, go to beginning of track */
			trkptr = curtrk;
		}
		patptr = (*trkptr)-1;
		goto get_sound_event;
	}

	switch (d & TYPE_MASK) {
	case NOTE:
		effect = NOTE;
		i = curfreq = notes[d];
		setfreq(i);
		tickctr = *++patptr;
		break;

	case ARPEGGIO:
		effect = ARPEGGIO;
		arpbase = d&NOTE_MASK; /* Arpeggio note base */
		tickctr = *(++patptr); /* Duration */
		d = *(++patptr); /* Pattern and speed */
		arpctr = arpspd = d&0x0F;
		arppat = (d>>=4);
		arpptr = -1;

		i = curfreq = notes[arppats[arppat][0]];
		setfreq(i);
		break;

	case GLISSANDO:
		effect = GLISSANDO;
		i = curfreq = notes[d&=NOTE_MASK];
		setfreq(i);
		tickctr = *(++patptr);
		glissoffs = *(++patptr);
		break;
	case OTHER:
		effect = OTHER;
		tickctr = *(++patptr);
		break;
	}

}

