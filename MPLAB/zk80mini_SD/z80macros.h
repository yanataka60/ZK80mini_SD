/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

/* General bit macros */

#define bToggle(x,y) x^=1<<y
#define bSet(x,y) x|=1<<y
#define bClear(x,y) x&=(~(1<<y))&0xFFFF

/*	Flag-setting routines follow
	Flag register: SZ-H-PNC
*/
#define setSflag()   bSet(regAF,7)
#define clearSflag() bClear(regAF,7)
#define setZflag()   bSet(regAF,6)
#define clearZflag() bClear(regAF,6)
#define setHflag()   bSet(regAF,4)
#define clearHflag() bClear(regAF,4)
#define setPflag()   bSet(regAF,2)
#define clearPflag() bClear(regAF,2)
#define setNflag()   bSet(regAF,1)
#define clearNflag() bClear(regAF,1)
#define setCflag()   bSet(regAF,0)
#define clearCflag() bClear(regAF,0)

/*	Flag-setting macro for 8 bit increment.
	Flag register: SZ-H-PNC
	S is set if result is negative; reset otherwise
	Z is set if result is zero; reset otherwise
	H is set if carry from bit 3; reset otherwise
	P/V is set if r was 7FH before operation; reset otherwise
	N is reset
	C is not affected
*/
#define flag8inc(x) loadF(\
		(((x)&0x80) ? 0x80 : 0x00) |\
		(((x)&0xff) ? 0x00 : 0x40) |\
		((((x)&0x0F)==0x00) ? 0x10 : 0x00) |\
		(((x)==0x80) ? 0x04 : 0x00) |\
		(flagC ? 0x01 : 0x00)\
	)\
	
/*	Flag-setting macro for 8 bit decrement
	Flag register: SZ-H-PNC
	S is set if result is negative; reset otherwise
	Z is set if result is zero; reset otherwise
	H is set if borrow from bit 4, reset otherwise
	P/V is set if m was 80H before operation; reset otherwise
	N is set
	C is not affected
*/
#define flag8dec(x) loadF(\
		(((x)&0x80) ? 0x80 : 0x00) |\
		(((x)&0xff) ? 0x00 : 0x40) |\
		((((x)&0x0F)==0x0F) ? 0x10 : 0x00) |\
		(((x)==0x7F) ? 0x04 : 0x00) |\
		0x02 |\
		(flagC ? 0x01 : 0x00)\
	)
		
/*	Jump Relative macro uses a UINT8 temporaly register
*/
#define z80JR(x8) loadPC(regPC + getCodeIndex(x8));

/*	getCodeIndex(x8) macro uses a UINT8 temporary register
*/
#define getCodeIndex(x8) ( ((x8=getCode())&0x80) ? (0xff00|x8) : x8 )

/*	Set parity flag macro uses a temporaly 8 bit register.
	This macro takes 21 cycles.
*/
#define setZ80Parity(x,y8) \
	y8=x;\
	y8=y8^(y8>>4);\
	y8=y8^(y8>>2);\
	y8=y8^(y8>>1);\
	if (y8&0x01) clearPflag();\
	else setPflag()

/*	Table for DAA
	xHyyNC, where 
	x=0 or 1, corresponding to AL<0xA or 0x9<AL,
	yy=0, 1, or 2, corresponding to AH<0x9, AH==0x9, or 0x9<AH, and
	H, N, and C are Z80 flags.

	This table is not used, because the code using it is slower.

static const unsigned char z80DaaTable[]={

//	|      AH<0x9      |      AH==0x9      |       0x9<AH      |
//	|   N=0  |    N=1  |    N=0  |    N=1  |    N=0  |    N=1  | 
//	 C=0  C=1  C=0  C=1  C=0  C=1  C=0  C=1  C=0  C=1  C=0  C=1
 
	0x00,0x61,0x00,0xa1,0x00,0x61,0x00,0xa1,0x61,0x61,0xa1,0xa1,0x00,0x00,0x00,0x00, // H=0, AL<0xA
	0x06,0x67,0xfa,0x9b,0x06,0x67,0xfa,0x9b,0x67,0x67,0x9b,0x9b,0x00,0x00,0x00,0x00, // H=1, AL<0xA
	0x06,0x67,0xfa,0x9b,0x67,0x67,0x9b,0x9b,0x67,0x67,0x9b,0x9b,0x00,0x00,0x00,0x00, // H=0, 0x9<AL
	0x06,0x67,0xfa,0x9b,0x67,0x67,0x9b,0x9b,0x67,0x67,0x9b,0x9b,0x00,0x00,0x00,0x00  // H=1, 0x9<AL

};
//*/
