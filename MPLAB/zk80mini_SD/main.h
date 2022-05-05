/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

#include <p32xxxx.h>
#include <plib.h>


/* Global variables follow */

static const unsigned char PROG[]={
0x01,0x00,0x49,0x21,0xf8,0x83,0xb5,0x6f,0x70,0x06,0x09,0xcd,0xef,0x02,0x05,0xc2,
0x0b,0x80,0x3c,0x71,0xc3,0x00,0x80
/*
(8000)
loop:
LD    BC,4900
LD    HL,83F8
OR    L
LD    L,A
LD    (HL),B
LD    B,09
wait:
CALL  02EF
DEC   B
JP    NZ,wait:
INC   A
LD    (HL),C
JP    loop:
*/
};

//#define TIMER1LEN 13
#define TIMER1LEN 13
#define TIMR1HSTEP (1<<TIMER1LEN)

#ifdef MAIN
	unsigned char RAM[0x7200] __attribute__((persistent)); // 28KB RAM
	volatile unsigned long g_timer1;
	volatile unsigned long g_TMR1h;
	volatile unsigned char g_keymatrix[3];
#else
	extern unsigned char RAM[0x7200];
	extern volatile unsigned long g_timer1;
	extern volatile unsigned long g_TMR1h;
	extern volatile unsigned char g_keymatrix[3];
#endif

/* Prototyping */

void main();

void init_led();
void timer1Int();

void triggerInt();

void execZ80infinite();
void execZ80code();
void resetZ80();
void intZ80(unsigned char i8);
void nmrZ80();

