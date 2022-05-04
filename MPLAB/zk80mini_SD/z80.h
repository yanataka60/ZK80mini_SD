/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

/*	z80.h defines the environment (CPU) specific settings
	Currently, all parameters are set for MIPS32 M4K
*/

// Define either Z80 or I8080
//#define Z80
#define I8080


#define INT32 long
#define INT16 short
#define INT8  char
#define UINT32 unsigned long
#define UINT16 unsigned short
#define UINT8  unsigned char

static UINT16 z80PC;
static UINT16 z80SP;
static UINT16 z80AF;
static UINT16 z80BC;
static UINT16 z80DE;
static UINT16 z80HL;
#ifdef Z80
	static UINT16 z80IX;
	static UINT16 z80IY;
#endif
static UINT16 z80IR;
static UINT8  z80IM;
static UINT8 z80irq;
static UINT8 z80nrq;
static UINT8 z80intCode;
#ifdef Z80
	static UINT16 z80AFprime;
	static UINT16 z80BCprime;
	static UINT16 z80DEprime;
	static UINT16 z80HLprime;
#endif

/*	T cycle setting for each instruction sets for MIPS working at 40 MHz*/
#define HMIPSCLK 20
#define setT4() (g_timer1+=HMIPSCLK*4)
#define setT5() (g_timer1+=HMIPSCLK*5)
#define setT6() (g_timer1+=HMIPSCLK*6)
#define setT7() (g_timer1+=HMIPSCLK*7)
#define setT8() (g_timer1+=HMIPSCLK*8)
#define setT9() (g_timer1+=HMIPSCLK*9)
#define setT10() (g_timer1+=HMIPSCLK*10)
#define setT11() (g_timer1+=HMIPSCLK*11)
#define setT12() (g_timer1+=HMIPSCLK*12)
#define setT13() (g_timer1+=HMIPSCLK*13)
#define setT14() (g_timer1+=HMIPSCLK*14)
#define setT15() (g_timer1+=HMIPSCLK*15)
#define setT16() (g_timer1+=HMIPSCLK*16)
#define setT17() (g_timer1+=HMIPSCLK*17)
#define setT19() (g_timer1+=HMIPSCLK*19)
#define setT20() (g_timer1+=HMIPSCLK*20)
#define setT21() (g_timer1+=HMIPSCLK*21)
#define setT23() (g_timer1+=HMIPSCLK*23)

#ifdef Z80
	#define setT4_5() (g_timer1+=HMIPSCLK*4)
	#define setT4_7() (g_timer1+=HMIPSCLK*4)
	#define setT6_5() (g_timer1+=HMIPSCLK*6)
	#define setT10_11() (g_timer1+=HMIPSCLK*10)
	#define setT11_10() (g_timer1+=HMIPSCLK*11)
	#define setT19_18() (g_timer1+=HMIPSCLK*19)
#endif
#ifdef I8080
	#define setT4_5() (g_timer1+=HMIPSCLK*5)
	#define setT4_7() (g_timer1+=HMIPSCLK*7)
	#define setT6_5() (g_timer1+=HMIPSCLK*5)
	#define setT10_11() (g_timer1+=HMIPSCLK*11)
	#define setT11_10() (g_timer1+=HMIPSCLK*10)
	#define setT19_18() (g_timer1+=HMIPSCLK*18)
#endif

/*
It's not required to modify following settings,
but it may affect the emulating speed to modify them.
*/
#define regA (((UINT8*)(&z80AF))[1])
#define regF (((UINT8*)(&z80AF))[0])
#define regB (((UINT8*)(&z80BC))[1])
#define regC (((UINT8*)(&z80BC))[0])
#define regD (((UINT8*)(&z80DE))[1])
#define regE (((UINT8*)(&z80DE))[0])
#define regH (((UINT8*)(&z80HL))[1])
#define regL (((UINT8*)(&z80HL))[0])
#define regI (((UINT8*)(&z80IR))[1])
#define regR (((UINT8*)(&z80IR))[0])
#define regIXh (((UINT8*)(&z80IX))[1])
#define regIXl (((UINT8*)(&z80IX))[0])
#define regIYh (((UINT8*)(&z80IY))[1])
#define regIYl (((UINT8*)(&z80IY))[0])
#define regSPh (((UINT8*)(&z80SP))[1])
#define regSPl (((UINT8*)(&z80SP))[0])
#define regAF (z80AF)
#define regHL (z80HL)
#define regBC (z80BC)
#define regDE (z80DE)
#define regIX (z80IX)
#define regIY (z80IY)
#define regPC (z80PC)
#define regSP (z80SP)
#define regAFprime (z80AFprime)
#define regBCprime (z80BCprime)
#define regDEprime (z80DEprime)
#define regHLprime (z80HLprime)
// Flag register: SZ-H-PNC
#define flagS (z80AF & 0x80)
#define flagZ (z80AF & 0x40)
#define flagH (z80AF & 0x10)
#define flagP (z80AF & 0x04)
#define flagN (z80AF & 0x02)
#define flagC (z80AF & 0x01)
// Interrupt flip flops
#define flagIFF1 (z80IM & 0x04)
#define flagIFF2 (z80IM & 0x08)
#define regIM (z80IM & 0x03)

#define loadA(x) (((UINT8*)(&z80AF))[1]=(UINT8)x)
#define loadF(x) (((UINT8*)(&z80AF))[0]=(UINT8)x)
#define loadB(x) (((UINT8*)(&z80BC))[1]=(UINT8)x)
#define loadC(x) (((UINT8*)(&z80BC))[0]=(UINT8)x)
#define loadD(x) (((UINT8*)(&z80DE))[1]=(UINT8)x)
#define loadE(x) (((UINT8*)(&z80DE))[0]=(UINT8)x)
#define loadH(x) (((UINT8*)(&z80HL))[1]=(UINT8)x)
#define loadL(x) (((UINT8*)(&z80HL))[0]=(UINT8)x)
#define loadI(x) (((UINT8*)(&z80IR))[1]=(UINT8)x)
#define loadR(x) (((UINT8*)(&z80IR))[0]=(UINT8)x)
#define loadIXh(x) (((UINT8*)(&z80IX))[1]=(UINT8)x)
#define loadIXl(x) (((UINT8*)(&z80IX))[0]=(UINT8)x)
#define loadIYh(x) (((UINT8*)(&z80IY))[1]=(UINT8)x)
#define loadIYl(x) (((UINT8*)(&z80IY))[0]=(UINT8)x)
#define loadSPh(x) (((UINT8*)(&z80SP))[1]=(UINT8)x)
#define loadSPl(x) (((UINT8*)(&z80SP))[0]=(UINT8)x)
#define loadIM(x) (z80IM=(z80IM&0xFC) | (x)&0x03)
#define loadIFF1(x) (z80IM=(z80IM&0xFB) | ((x)?0x04:0x00))
#define loadIFF2(x) (z80IM=(z80IM&0xF7) | ((x)?0x08:0x00))

#define loadAF(x) (z80AF=(UINT16)(x))
#define loadBC(x) (z80BC=(UINT16)(x))
#define loadDE(x) (z80DE=(UINT16)(x))
#define loadHL(x) (z80HL=(UINT16)(x))
#define loadPC(x) (z80PC=(UINT16)(x))
#define loadSP(x) (z80SP=(UINT16)(x))
#define loadIX(x) (z80IX=(UINT16)(x))
#define loadIY(x) (z80IY=(UINT16)(x))
#define loadAFprime(x) (z80AFprime=(UINT16)(x));
#define loadBCprime(x) (z80BCprime=(UINT16)(x));
#define loadDEprime(x) (z80DEprime=(UINT16)(x));
#define loadHLprime(x) (z80HLprime=(UINT16)(x));
