/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

/*	Z-80 emulator for microcontrollers.
	Written by Katsumi.
	This code is provided under the license of LGPL v2.
	To emulate Z80 function, call execZ80codes() periodically.
	You will also know the next timing of call through setTx() callback 
	functions (see z80.h).
*/

#include "main.h"
#include "rom.h"
#include "z80.h"
#include "z80macros.h"
#include "z80functions.h"
#include "peripheral.h"

/* Local prototypings */
void execZ80(UINT8 code);
void codeFF();

/* Reset */
void resetZ80(){
	// SP
	loadSP(0x10f0);
	// PC
	//loadPC(0x1200);
	loadPC(0x0000);
	// I and R
	loadI(0x00);
	loadR(0x00);
	// Disable interrupt and set interrupt mode to 0
	loadIM(0);
	loadIFF1(0);
	loadIFF2(0);
	z80irq=0;
	z80nrq=0;
}

/* Interrupts */
void intZ80(UINT8 i8){
	if (!flagIFF1) return;
	loadIFF1(0);
	loadIFF2(0);
	z80irq=1;
	z80intCode=i8;
}
void nmrZ80(){
	loadIFF1(0);
	z80irq=1;
	z80nrq=1;
}
void doZ80Int(){
	UINT16 addr;
	z80irq=0;
	if (z80nrq) {
		// NMR
		z80nrq=0;
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC(0x0066);
	} else {
		// Mascable interrupt
		switch (regIM) {
			case 0:
				execZ80(z80intCode);
				return;
			case 2:
				addr=(regI<<8)|z80intCode;
				loadSP(regSP-2);
				writeMemory(regSP,regPC&0xFF);
				writeMemory(regSP+1,regPC>>8);
				loadPC(readMemory(addr)|(readMemory(addr+1)<<8));
				return;
			case 1:
			default:
				codeFF();
				return;
		}
	}	
}

/*	Code emulation routines follow */
void codeVOID(){
	//NOP with longest T cycles
	setT23();
}
void code00(){
	//NOP
	#ifdef PRECODE00
		PRECODE00
	#endif
	setT4();
	#ifdef POSTCODE00
		POSTCODE00
	#endif
}
void code01(){
	//LD BC,nn
	#ifdef PRECODE01
		PRECODE01
	#endif
	setT10();
	loadC(getCode());
	loadB(getCode());
	#ifdef POSTCODE01
		POSTCODE01
	#endif
}
void code02(){
	//LD (BC),A
	#ifdef PRECODE02
		PRECODE02
	#endif
	setT7();
	writeMemory(regBC,regA);
	#ifdef POSTCODE02
		POSTCODE02
	#endif
}
void code03(){
	//INC BC
	#ifdef PRECODE03
		PRECODE03
	#endif
	//Note that 16-bit increment routine does not change flags.
	setT6_5();
	loadBC(regBC+1);
	#ifdef POSTCODE03
		POSTCODE03
	#endif
}
void code04(){
	UINT8 i8;
	//INC B
	#ifdef PRECODE04
		PRECODE04
	#endif
	setT4_5();
	i8=regB+1;
	loadB(i8);
	flag8inc(i8);
	#ifdef POSTCODE04
		POSTCODE04
	#endif
}
void code05(){
	UINT8 i8;
	//DEC B
	#ifdef PRECODE05
		PRECODE05
	#endif
	setT4_5();
	i8=regB-1;
	loadB(i8);
	flag8dec(i8);
	#ifdef POSTCODE05
		POSTCODE05
	#endif
}
void code06(){
	//LD B,n
	#ifdef PRECODE06
		PRECODE06
	#endif
	setT7();
	loadB(getCode());
	#ifdef POSTCODE06
		POSTCODE06
	#endif
}
void code07(){
	//RLCA  C <- A7<-A0 <- A7
	#ifdef PRECODE07
		PRECODE07
	#endif
	setT4();
	if (regA&0x80) {
		setCflag();
		loadA((regA<<1) | 0x01);
	} else {
		clearCflag();
		loadA(regA<<1);
	}
	clearHflag();
	clearNflag();	
	#ifdef POSTCODE07
		POSTCODE07
	#endif
}
#ifdef Z80
void code08(){
	UINT16 i16;
	//EX AF,AFf
	#ifdef PRECODE08
		PRECODE08
	#endif
	setT4();
	i16=regAF;
	loadAF(regAFprime);
	loadAFprime(i16);
	#ifdef POSTCODE08
		POSTCODE08
	#endif
}
#endif
void code09(){
	//ADD HL,BC
	#ifdef PRECODE09
		PRECODE09
	#endif
	setT11_10();
	z80ADD16(regBC);
	#ifdef POSTCODE09
		POSTCODE09
	#endif
}
void code0A(){
	//LD A,(BC)
	#ifdef PRECODE0A
		PRECODE0A
	#endif
	setT7();
	loadA(readMemory(regBC));
	#ifdef POSTCODE0A
		POSTCODE0A
	#endif
}
void code0B(){
	//DEC BC
	#ifdef PRECODE0B
		PRECODE0B
	#endif
	setT6_5();
	loadBC(regBC-1);
	#ifdef POSTCODE0B
		POSTCODE0B
	#endif
}
void code0C(){
	UINT8 i8;
	//INC C
	#ifdef PRECODE0C
		PRECODE0C
	#endif
	setT4_5();
	i8=regC+1;
	loadC(i8);
	flag8inc(i8);
	#ifdef POSTCODE0C
		POSTCODE0C
	#endif
}
void code0D(){
	UINT8 i8;
	//DEC C
	#ifdef PRECODE0D
		PRECODE0D
	#endif
	setT4_5();
	i8=regC-1;
	loadC(i8);
	flag8dec(i8);
	#ifdef POSTCODE0D
		POSTCODE0D
	#endif
}
void code0E(){
	//LD C,n
	#ifdef PRECODE0E
		PRECODE0E
	#endif
	setT7();
	loadC(getCode());
	#ifdef POSTCODE0E
		POSTCODE0E
	#endif
}
void code0F(){
	//RRCA A0 -> A7->A0 ->C
	#ifdef PRECODE0F
		PRECODE0F
	#endif
	setT4();
	if (regA&0x01) {
		setCflag();
		loadA((regA>>1) | 0x80);
	} else {
		clearCflag();
		loadA(regA>>1);
	}
	clearHflag();
	clearNflag();	
	#ifdef POSTCODE0F
		POSTCODE0F
	#endif
}
#ifdef Z80
void code10(){
	UINT8 i8;
	//DJNZ (PC+e)
	#ifdef PRECODE10
		PRECODE10
	#endif
	i8=regB-1;
	if (i8) {
		setT13();
		loadB(i8);
		z80JR(i8);
	} else {
		setT8();
		loadB(i8);
		getCode();
	}
	#ifdef POSTCODE10
		POSTCODE10
	#endif
}
#endif
void code11(){
	//LD DE,nn
	#ifdef PRECODE11
		PRECODE11
	#endif
	setT10();
	loadE(getCode());
	loadD(getCode());
	#ifdef POSTCODE11
		POSTCODE11
	#endif
}
void code12(){
	//LD (DE),A
	#ifdef PRECODE12
		PRECODE12
	#endif
	setT7();
	writeMemory(regDE,regA);
	#ifdef POSTCODE12
		POSTCODE12
	#endif
}
void code13(){
	//INC DE
	#ifdef PRECODE13
		PRECODE13
	#endif
	setT6_5();
	loadDE(regDE+1);
	#ifdef POSTCODE13
		POSTCODE13
	#endif
}
void code14(){
	UINT8 i8;
	//INC D
	#ifdef PRECODE14
		PRECODE14
	#endif
	setT4_5();
	i8=regD+1;
	loadD(i8);
	flag8inc(i8);
	#ifdef POSTCODE14
		POSTCODE14
	#endif
}
void code15(){
	UINT8 i8;
	//DEC D
	#ifdef PRECODE15
		PRECODE15
	#endif
	setT4_5();
	i8=regD-1;
	loadD(i8);
	flag8dec(i8);
	#ifdef POSTCODE15
		POSTCODE15
	#endif
}
void code16(){
	//LD D,n
	#ifdef PRECODE16
		PRECODE16
	#endif
	setT7();
	loadD(getCode());
	#ifdef POSTCODE16
		POSTCODE16
	#endif
}
void code17(){
	UINT8 i8;
	//RLA C<- A7<-A0 <-C
	#ifdef PRECODE17
		PRECODE17
	#endif
	setT4();
	i8=flagC;
	if (regA&0x80) setCflag();
	else clearCflag();		
	if (i8) loadA((regA<<1) | 0x01);
	else loadA(regA<<1);
	clearHflag();
	clearNflag();	
	#ifdef POSTCODE17
		POSTCODE17
	#endif
}
#ifdef Z80
void code18(){
	UINT8 i8;
	//JR (PC+e)
	#ifdef PRECODE18
		PRECODE18
	#endif
	setT12();
	z80JR(i8);
	#ifdef POSTCODE18
		POSTCODE18
	#endif
}
#endif
void code19(){
	//ADD HL,DE
	#ifdef PRECODE19
		PRECODE19
	#endif
	setT11_10();
	z80ADD16(regDE);
	#ifdef POSTCODE19
		POSTCODE19
	#endif
}
void code1A(){
	//LD A,(DE)
	#ifdef PRECODE1A
		PRECODE1A
	#endif
	setT7();
	loadA(readMemory(regDE));
	#ifdef POSTCODE1A
		POSTCODE1A
	#endif
}
void code1B(){
	//DEC DE
	#ifdef PRECODE1B
		PRECODE1B
	#endif
	setT6_5();
	loadDE(regDE-1);
	#ifdef POSTCODE1B
		POSTCODE1B
	#endif
}
void code1C(){
	UINT8 i8;
	//INC E
	#ifdef PRECODE1C
		PRECODE1C
	#endif
	setT4_5();
	i8=regE+1;
	loadE(i8);
	flag8inc(i8);
	#ifdef POSTCODE1C
		POSTCODE1C
	#endif
}
void code1D(){
	UINT8 i8;
	//DEC E
	#ifdef PRECODE1D
		PRECODE1D
	#endif
	setT4_5();
	i8=regE-1;
	loadE(i8);
	flag8dec(i8);
	#ifdef POSTCODE1D
		POSTCODE1D
	#endif
}
void code1E(){
	//LD E,n
	#ifdef PRECODE1E
		PRECODE1E
	#endif
	setT7();
	loadE(getCode());
	#ifdef POSTCODE1E
		POSTCODE1E
	#endif
}
void code1F(){
	UINT8 i8;
	//RRA C-> A7->A0 ->C
	#ifdef PRECODE1F
		PRECODE1F
	#endif
	setT4();
	i8=flagC;
	if (regA&0x01) setCflag();
	else clearCflag();		
	if (i8) loadA((regA>>1) | 0x80);
	else loadA(regA>>1);
	clearHflag();
	clearNflag();	
	#ifdef POSTCODE1F
		POSTCODE1F
	#endif
}
#ifdef Z80
void code20(){
	UINT8 i8;
	//JR NZ,(PC+e)
	#ifdef PRECODE20
		PRECODE20
	#endif
	if (flagZ) {
		setT7();
		getCode();
	} else {
		setT12();
		z80JR(i8);
	}
	#ifdef POSTCODE20
		POSTCODE20
	#endif
}
#endif
void code21(){
	//LD HL,nn
	#ifdef PRECODE21
		PRECODE21
	#endif
	setT10();
	loadL(getCode());
	loadH(getCode());
	#ifdef POSTCODE21
		POSTCODE21
	#endif
}
void code22(){
	UINT8 i8;
	UINT16 i16;
	//LD (nn),HL
	#ifdef PRECODE22
		PRECODE22
	#endif
	setT16();
	i8=getCode();
	i16=getCode()<<8;
	i16=i16 | i8;
	writeMemory(i16,regL);
	writeMemory(i16+1,regH);
	#ifdef POSTCODE22
		POSTCODE22
	#endif
}
void code23(){
	//INC HL
	#ifdef PRECODE23
		PRECODE23
	#endif
	setT6_5();
	loadHL(regHL+1);
	#ifdef POSTCODE23
		POSTCODE23
	#endif
}
void code24(){
	UINT8 i8;
	//INC H
	#ifdef PRECODE24
		PRECODE24
	#endif
	setT4_5();
	i8=regH+1;
	loadH(i8);
	flag8inc(i8);
	#ifdef POSTCODE24
		POSTCODE24
	#endif
}
void code25(){
	UINT8 i8;
	//DEC H
	#ifdef PRECODE25
		PRECODE25
	#endif
	setT4_5();
	i8=regH-1;
	loadH(i8);
	flag8dec(i8);
	#ifdef POSTCODE25
		POSTCODE25
	#endif
}
void code26(){
	//LD H,n
	#ifdef PRECODE26
		PRECODE26
	#endif
	setT7();
	loadH(getCode());
	#ifdef POSTCODE26
		POSTCODE26
	#endif
}
void code27(){
	UINT8 i8;
	UINT8 h;
	//DAA
	#ifdef PRECODE27
		PRECODE27
	#endif
	//This code is faster than one using DAA table.
	h=regA;
	setT4();
	if (!flagN) {
		if (!flagC) {
			if (!flagH) {
				if ((regA&0xF0)<0x90) {
					if ((regA&0x0F)<0x0A) {
						//loadA(regA+0x00);
						//clearCflag();
					} else {
						loadA(regA+0x06);
						//clearCflag();
					}
				} else if ((regA&0xF0)==0x90) {
					if ((regA&0x0F)<0x0A) {
						//loadA(regA+0x00);
						//clearCflag();
					} else {
						loadA(regA+0x66);
						setCflag();
					}
				} else {
					if ((regA&0x0F)<0x0A) {
						loadA(regA+0x60);
						setCflag();
					} else {
						loadA(regA+0x66);
						setCflag();
					}
				}
			} else {
				if ((regA&0xF0)<0x90) {
						loadA(regA+0x06);
						//clearCflag();
				} else if ((regA&0xF0)==0x90) {
					if ((regA&0x0F)<0x0A) {
						loadA(regA+0x06);
						//clearCflag();
					} else {
						loadA(regA+0x66);
						setCflag();
					}
				} else {
						loadA(regA+0x66);
						setCflag();
				}
			}
		} else {
			if (!flagH) {
					if ((regA&0x0F)<0x0A) {
						loadA(regA+0x60);
						//setCflag();
					} else {
						loadA(regA+0x66);
						//setCflag();
					}
			} else {
						loadA(regA+0x66);
						//setCflag();
			}
		}
	} else {
		if (!flagC) {
			if (!flagH) {
				if ((regA&0xF0)<0x90) {
					if ((regA&0x0F)<0x0A) {
						//loadA(regA+0x00);
						//clearCflag();
					} else {
						loadA(regA+0xFA);
						//clearCflag();
					}
				} else if ((regA&0xF0)==0x90) {
					if ((regA&0x0F)<0x0A) {
						//loadA(regA+0x00);
						//clearCflag();
					} else {
						loadA(regA+0x9A);
						setCflag();
					}
				} else {
					if ((regA&0x0F)<0x0A) {
						loadA(regA+0xA0);
						setCflag();
					} else {
						loadA(regA+0x9A);
						setCflag();
					}
				}
			} else {
				if ((regA&0xF0)<0x90) {
						loadA(regA+0xFA);
						//clearCflag();
				} else if ((regA&0xF0)==0x90) {
					if ((regA&0x0F)<0x0A) {
						loadA(regA+0xFA);
						//clearCflag();
					} else {
						loadA(regA+0x9A);
						setCflag();
					}
				} else {
						loadA(regA+0x9A);
						setCflag();
				}
			}
		} else {
			if (!flagH) {
					if ((regA&0x0F)<0x0A) {
						loadA(regA+0xA0);
						//setCflag();
					} else {
						loadA(regA+0x9A);
						//setCflag();
					}
			} else {
						loadA(regA+0x9A);
						//setCflag();
			}
		}
	}
	if (regA&0x80) setSflag();
	else clearSflag();
	if (regA) clearZflag();
	else setZflag();
	setZ80Parity(regA,i8);
	if ((h^regA)&0x10) setHflag();
	else clearHflag();
	#ifdef POSTCODE27
		POSTCODE27
	#endif
}
#ifdef Z80
void code28(){
	UINT8 i8;
	//JR Z,(PC+e)
	#ifdef PRECODE28
		PRECODE28
	#endif
	if (flagZ) {
		setT12();
		z80JR(i8);
	} else {
		setT7();
		getCode();
	}
	#ifdef POSTCODE28
		POSTCODE28
	#endif
}
#endif
void code29(){
	//ADD HL,HL
	#ifdef PRECODE29
		PRECODE29
	#endif
	setT11_10();
	z80ADD16(regHL);
	#ifdef POSTCODE29
		POSTCODE29
	#endif
}
void code2A(){
	UINT8 i8;
	UINT16 i16;
	//LD HL,(nn)
	#ifdef PRECODE2A
		PRECODE2A
	#endif
	setT16();
	i8=getCode();
	i16=getCode()<<8;
	i16|=i8;
	loadL(readMemory(i16));
	loadH(readMemory(i16+1));
	#ifdef POSTCODE2A
		POSTCODE2A
	#endif
}
void code2B(){
	//DEC HL
	#ifdef PRECODE2B
		PRECODE2B
	#endif
	setT6_5();
	loadHL(regHL-1);
	#ifdef POSTCODE2B
		POSTCODE2B
	#endif
}
void code2C(){
	UINT8 i8;
	//INC L
	#ifdef PRECODE2C
		PRECODE2C
	#endif
	setT4_5();
	i8=regL+1;
	loadL(i8);
	flag8inc(i8);
	#ifdef POSTCODE2C
		POSTCODE2C
	#endif
}
void code2D(){
	UINT8 i8;
	//DEC L
	#ifdef PRECODE2D
		PRECODE2D
	#endif
	setT4_5();
	i8=regL-1;
	loadL(i8);
	flag8dec(i8);
	#ifdef POSTCODE2D
		POSTCODE2D
	#endif
}
void code2E(){
	//LD L,n
	#ifdef PRECODE2E
		PRECODE2E
	#endif
	setT7();
	loadL(getCode());
	#ifdef POSTCODE2E
		POSTCODE2E
	#endif
}
void code2F(){
	//CPL
	#ifdef PRECODE2F
		PRECODE2F
	#endif
	setT4();
	loadA(~regA);
	setHflag();
	setNflag();
	#ifdef POSTCODE2F
		POSTCODE2F
	#endif
}
#ifdef Z80
void code30(){
	UINT8 i8;
	//JR NC,(PC+e)
	#ifdef PRECODE30
		PRECODE30
	#endif
	if (flagC) {
		setT7();
		getCode();
	} else {
		setT12();
		z80JR(i8);
	}
	#ifdef POSTCODE30
		POSTCODE30
	#endif
}
#endif
void code31(){
	UINT8 i8;
	UINT16 i16;
	//LD SP,nn
	#ifdef PRECODE31
		PRECODE31
	#endif
	setT10();
	i8=getCode();
	i16=getCode()<<8;
	i16=i16 | i8;
	loadSP(i16);
	#ifdef POSTCODE31
		POSTCODE31
	#endif
}
void code32(){
	UINT8 i8;
	UINT16 i16;
	//LD (nn),A
	#ifdef PRECODE32
		PRECODE32
	#endif
	setT13();
	i8=getCode();
	i16=getCode()<<8;
	i16=i16 | i8;
	writeMemory(i16,regA);
	#ifdef POSTCODE32
		POSTCODE32
	#endif
}
void code33(){
	//INC SP
	#ifdef PRECODE33
		PRECODE33
	#endif
	setT6_5();
	loadSP(regSP+1);
	#ifdef POSTCODE33
		POSTCODE33
	#endif
}
void code34(){
	UINT8 i8;
	//INC (HL)
	#ifdef PRECODE34
		PRECODE34
	#endif
	setT11_10();
	i8=readMemory(regHL)+1;
	writeMemory(regHL,i8);
	flag8inc(i8);
	#ifdef POSTCODE34
		POSTCODE34
	#endif
}
void code35(){
	UINT8 i8;
	//DEC (HL)
	#ifdef PRECODE35
		PRECODE35
	#endif
	setT11_10();
	i8=readMemory(regHL)-1;
	writeMemory(regHL,i8);
	flag8dec(i8);
	#ifdef POSTCODE35
		POSTCODE35
	#endif
}
void code36(){
	//LD (HL),n
	#ifdef PRECODE36
		PRECODE36
	#endif
	setT10();
	writeMemory(regHL,getCode());
	#ifdef POSTCODE36
		POSTCODE36
	#endif
}
void code37(){
	//SCF
	#ifdef PRECODE37
		PRECODE37
	#endif
	setT4();
	clearHflag();
	clearNflag();
	setCflag();
	#ifdef POSTCODE37
		POSTCODE37
	#endif
}
#ifdef Z80
void code38(){
	UINT8 i8;
	//JR C,(PC+e)
	#ifdef PRECODE38
		PRECODE38
	#endif
	if (flagC) {
		setT12();
		z80JR(i8);
	} else {
		setT7();
		getCode();
	}
	#ifdef POSTCODE38
		POSTCODE38
	#endif
}
#endif
void code39(){
	//ADD HL,SP
	#ifdef PRECODE39
		PRECODE39
	#endif
	setT11_10();
	z80ADD16(regSP);
	#ifdef POSTCODE39
		POSTCODE39
	#endif
}
void code3A(){
	UINT8 i8;
	UINT16 i16;
	//LD A,(nn)
	#ifdef PRECODE3A
		PRECODE3A
	#endif
	setT13();
	i8=getCode();
	i16=getCode()<<8;
	i16|=i8;
	loadA(readMemory(i16));
	#ifdef POSTCODE3A
		POSTCODE3A
	#endif
}
void code3B(){
	//DEC SP
	#ifdef PRECODE3B
		PRECODE3B
	#endif
	setT6_5();
	loadSP(regSP-1);
	#ifdef POSTCODE3B
		POSTCODE3B
	#endif
}
void code3C(){
	UINT8 i8;
	//INC A
	#ifdef PRECODE3C
		PRECODE3C
	#endif
	setT4_5();
	i8=regA+1;
	loadA(i8);
	flag8inc(i8);
	#ifdef POSTCODE3C
		POSTCODE3C
	#endif
}
void code3D(){
	UINT8 i8;
	//DEC A
	#ifdef PRECODE3D
		PRECODE3D
	#endif
	setT4_5();
	i8=regA-1;
	loadA(i8);
	flag8dec(i8);
	#ifdef POSTCODE3D
		POSTCODE3D
	#endif
}
void code3E(){
	//LD A,n
	#ifdef PRECODE3E
		PRECODE3E
	#endif
	setT7();
	loadA(getCode());
	#ifdef POSTCODE3E
		POSTCODE3E
	#endif
}
void code3F(){
	//CCF
	#ifdef PRECODE3F
		PRECODE3F
	#endif
	setT4();
	if (flagC) {
		setHflag();
		clearCflag();
	} else {
		clearHflag();
		setCflag();
	}
	clearNflag();
	#ifdef POSTCODE3F
		POSTCODE3F
	#endif
}
void code40(){
	//LD B,B
	#ifdef PRECODE40
		PRECODE40
	#endif
	setT4_5();
	loadB(regB);
	#ifdef POSTCODE40
		POSTCODE40
	#endif
}
void code41(){
	//LD B,C
	#ifdef PRECODE41
		PRECODE41
	#endif
	setT4_5();
	loadB(regC);
	#ifdef POSTCODE41
		POSTCODE41
	#endif
}
void code42(){
	//LD B,D
	#ifdef PRECODE42
		PRECODE42
	#endif
	setT4_5();
	loadB(regD);
	#ifdef POSTCODE42
		POSTCODE42
	#endif
}
void code43(){
	//LD B,E
	#ifdef PRECODE43
		PRECODE43
	#endif
	setT4_5();
	loadB(regE);
	#ifdef POSTCODE43
		POSTCODE43
	#endif
}
void code44(){
	//LD B,H
	#ifdef PRECODE44
		PRECODE44
	#endif
	setT4_5();
	loadB(regH);
	#ifdef POSTCODE44
		POSTCODE44
	#endif
}
void code45(){
	//LD B,L
	#ifdef PRECODE45
		PRECODE45
	#endif
	setT4_5();
	loadB(regL);
	#ifdef POSTCODE45
		POSTCODE45
	#endif
}
void code46(){
	//LD B,(HL)
	#ifdef PRECODE46
		PRECODE46
	#endif
	setT7();
	loadB(readMemory(regHL));
	#ifdef POSTCODE46
		POSTCODE46
	#endif
}
void code47(){
	//LD B,A
	#ifdef PRECODE47
		PRECODE47
	#endif
	setT4_5();
	loadB(regA);
	#ifdef POSTCODE47
		POSTCODE47
	#endif
}
void code48(){
	//LD C,B
	#ifdef PRECODE48
		PRECODE48
	#endif
	setT4_5();
	loadC(regB);
	#ifdef POSTCODE48
		POSTCODE48
	#endif
}
void code49(){
	//LD C,C
	#ifdef PRECODE49
		PRECODE49
	#endif
	setT4_5();
	loadC(regC);
	#ifdef POSTCODE49
		POSTCODE49
	#endif
}
void code4A(){
	//LD C,D
	#ifdef PRECODE4A
		PRECODE4A
	#endif
	setT4_5();
	loadC(regD);
	#ifdef POSTCODE4A
		POSTCODE4A
	#endif
}
void code4B(){
	//LD C,E
	#ifdef PRECODE4B
		PRECODE4B
	#endif
	setT4_5();
	loadC(regE);
	#ifdef POSTCODE4B
		POSTCODE4B
	#endif
}
void code4C(){
	//LD C,H
	#ifdef PRECODE4C
		PRECODE4C
	#endif
	setT4_5();
	loadC(regH);
	#ifdef POSTCODE4C
		POSTCODE4C
	#endif
}
void code4D(){
	//LD C,L
	#ifdef PRECODE4D
		PRECODE4D
	#endif
	setT4_5();
	loadC(regL);
	#ifdef POSTCODE4D
		POSTCODE4D
	#endif
}
void code4E(){
	//LD C,(HL)
	#ifdef PRECODE4E
		PRECODE4E
	#endif
	setT7();
	loadC(readMemory(regHL));
	#ifdef POSTCODE4E
		POSTCODE4E
	#endif
}
void code4F(){
	//LD C,A
	#ifdef PRECODE4F
		PRECODE4F
	#endif
	setT4_5();
	loadC(regA);
	#ifdef POSTCODE4F
		POSTCODE4F
	#endif
}
void code50(){
	//LD D,B
	#ifdef PRECODE50
		PRECODE50
	#endif
	setT4_5();
	loadD(regB);
	#ifdef POSTCODE50
		POSTCODE50
	#endif
}
void code51(){
	//LD D,C
	#ifdef PRECODE51
		PRECODE51
	#endif
	setT4_5();
	loadD(regC);
	#ifdef POSTCODE51
		POSTCODE51
	#endif
}
void code52(){
	//LD D,D
	#ifdef PRECODE52
		PRECODE52
	#endif
	setT4_5();
	loadD(regD);
	#ifdef POSTCODE52
		POSTCODE52
	#endif
}
void code53(){
	//LD D,E
	#ifdef PRECODE53
		PRECODE53
	#endif
	setT4_5();
	loadD(regE);
	#ifdef POSTCODE53
		POSTCODE53
	#endif
}
void code54(){
	//LD D,H
	#ifdef PRECODE54
		PRECODE54
	#endif
	setT4_5();
	loadD(regH);
	#ifdef POSTCODE54
		POSTCODE54
	#endif
}
void code55(){
	//LD D,L
	#ifdef PRECODE55
		PRECODE55
	#endif
	setT4_5();
	loadD(regL);
	#ifdef POSTCODE55
		POSTCODE55
	#endif
}
void code56(){
	//LD D,(HL)
	#ifdef PRECODE56
		PRECODE56
	#endif
	setT7();
	loadD(readMemory(regHL));
	#ifdef POSTCODE56
		POSTCODE56
	#endif
}
void code57(){
	//LD D,A
	#ifdef PRECODE57
		PRECODE57
	#endif
	setT4_5();
	loadD(regA);
	#ifdef POSTCODE57
		POSTCODE57
	#endif
}
void code58(){
	//LD E,B
	#ifdef PRECODE58
		PRECODE58
	#endif
	setT4_5();
	loadE(regB);
	#ifdef POSTCODE58
		POSTCODE58
	#endif
}
void code59(){
	//LD E,C
	#ifdef PRECODE59
		PRECODE59
	#endif
	setT4_5();
	loadE(regC);
	#ifdef POSTCODE59
		POSTCODE59
	#endif
}
void code5A(){
	//LD E,D
	#ifdef PRECODE5A
		PRECODE5A
	#endif
	setT4_5();
	loadE(regD);
	#ifdef POSTCODE5A
		POSTCODE5A
	#endif
}
void code5B(){
	//LD E,E
	#ifdef PRECODE5B
		PRECODE5B
	#endif
	setT4_5();
	loadE(regE);
	#ifdef POSTCODE5B
		POSTCODE5B
	#endif
}
void code5C(){
	//LD E,H
	#ifdef PRECODE5C
		PRECODE5C
	#endif
	setT4_5();
	loadE(regH);
	#ifdef POSTCODE5C
		POSTCODE5C
	#endif
}
void code5D(){
	//LD E,L
	#ifdef PRECODE5D
		PRECODE5D
	#endif
	setT4_5();
	loadE(regL);
	#ifdef POSTCODE5D
		POSTCODE5D
	#endif
}
void code5E(){
	//LD E,(HL)
	#ifdef PRECODE5E
		PRECODE5E
	#endif
	setT7();
	loadE(readMemory(regHL));
	#ifdef POSTCODE5E
		POSTCODE5E
	#endif
}
void code5F(){
	//LD E,A
	#ifdef PRECODE5F
		PRECODE5F
	#endif
	setT4_5();
	loadE(regA);
	#ifdef POSTCODE5F
		POSTCODE5F
	#endif
}
void code60(){
	//LD H,B
	#ifdef PRECODE60
		PRECODE60
	#endif
	setT4_5();
	loadH(regB);
	#ifdef POSTCODE60
		POSTCODE60
	#endif
}
void code61(){
	//LD H,C
	#ifdef PRECODE61
		PRECODE61
	#endif
	setT4_5();
	loadH(regC);
	#ifdef POSTCODE61
		POSTCODE61
	#endif
}
void code62(){
	//LD H,D
	#ifdef PRECODE62
		PRECODE62
	#endif
	setT4_5();
	loadH(regD);
	#ifdef POSTCODE62
		POSTCODE62
	#endif
}
void code63(){
	//LD H,E
	#ifdef PRECODE63
		PRECODE63
	#endif
	setT4_5();
	loadH(regE);
	#ifdef POSTCODE63
		POSTCODE63
	#endif
}
void code64(){
	//LD H,H
	#ifdef PRECODE64
		PRECODE64
	#endif
	setT4_5();
	loadH(regH);
	#ifdef POSTCODE64
		POSTCODE64
	#endif
}
void code65(){
	//LD H,L
	#ifdef PRECODE65
		PRECODE65
	#endif
	setT4_5();
	loadH(regL);
	#ifdef POSTCODE65
		POSTCODE65
	#endif
}
void code66(){
	//LD H,(HL)
	#ifdef PRECODE66
		PRECODE66
	#endif
	setT7();
	loadH(readMemory(regHL));
	#ifdef POSTCODE66
		POSTCODE66
	#endif
}
void code67(){
	//LD H,A
	#ifdef PRECODE67
		PRECODE67
	#endif
	setT4_5();
	loadH(regA);
	#ifdef POSTCODE67
		POSTCODE67
	#endif
}
void code68(){
	//LD L,B
	#ifdef PRECODE68
		PRECODE68
	#endif
	setT4_5();
	loadL(regB);
	#ifdef POSTCODE68
		POSTCODE68
	#endif
}
void code69(){
	//LD L,C
	#ifdef PRECODE69
		PRECODE69
	#endif
	setT4_5();
	loadL(regC);
	#ifdef POSTCODE69
		POSTCODE69
	#endif
}
void code6A(){
	//LD L,D
	#ifdef PRECODE6A
		PRECODE6A
	#endif
	setT4_5();
	loadL(regD);
	#ifdef POSTCODE6A
		POSTCODE6A
	#endif
}
void code6B(){
	//LD L,E
	#ifdef PRECODE6B
		PRECODE6B
	#endif
	setT4_5();
	loadL(regE);
	#ifdef POSTCODE6B
		POSTCODE6B
	#endif
}
void code6C(){
	//LD L,H
	#ifdef PRECODE6C
		PRECODE6C
	#endif
	setT4_5();
	loadL(regH);
	#ifdef POSTCODE6C
		POSTCODE6C
	#endif
}
void code6D(){
	//LD L,L
	#ifdef PRECODE6D
		PRECODE6D
	#endif
	setT4_5();
	loadL(regL);
	#ifdef POSTCODE6D
		POSTCODE6D
	#endif
}
void code6E(){
	//LD L,(HL)
	#ifdef PRECODE6E
		PRECODE6E
	#endif
	setT7();
	loadL(readMemory(regHL));
	#ifdef POSTCODE6E
		POSTCODE6E
	#endif
}
void code6F(){
	//LD L,A
	#ifdef PRECODE6F
		PRECODE6F
	#endif
	setT4_5();
	loadL(regA);
	#ifdef POSTCODE6F
		POSTCODE6F
	#endif
}
void code70(){
	//LD (HL),B
	#ifdef PRECODE70
		PRECODE70
	#endif
	setT7();
	writeMemory(regHL,regB);
	#ifdef POSTCODE70
		POSTCODE70
	#endif
}
void code71(){
	//LD (HL),C
	#ifdef PRECODE71
		PRECODE71
	#endif
	setT7();
	writeMemory(regHL,regC);
	#ifdef POSTCODE71
		POSTCODE71
	#endif
}
void code72(){
	//LD (HL),D
	#ifdef PRECODE72
		PRECODE72
	#endif
	setT7();
	writeMemory(regHL,regD);
	#ifdef POSTCODE72
		POSTCODE72
	#endif
}
void code73(){
	//LD (HL),E
	#ifdef PRECODE73
		PRECODE73
	#endif
	setT7();
	writeMemory(regHL,regE);
	#ifdef POSTCODE73
		POSTCODE73
	#endif
}
void code74(){
	//LD (HL),H
	#ifdef PRECODE74
		PRECODE74
	#endif
	setT7();
	writeMemory(regHL,regH);
	#ifdef POSTCODE74
		POSTCODE74
	#endif
}
void code75(){
	//LD (HL),L
	#ifdef PRECODE75
		PRECODE75
	#endif
	setT7();
	writeMemory(regHL,regL);
	#ifdef POSTCODE75
		POSTCODE75
	#endif
}
void code76(){
	//HALT
	#ifdef PRECODE76
		PRECODE76
	#endif
	setT4_7();
	loadPC(regPC-1);
	#ifdef POSTCODE76
		POSTCODE76
	#endif
}
void code77(){
	//LD (HL),A
	#ifdef PRECODE77
		PRECODE77
	#endif
	setT7();
	writeMemory(regHL,regA);
	#ifdef POSTCODE77
		POSTCODE77
	#endif
}
void code78(){
	//LD A,B
	#ifdef PRECODE78
		PRECODE78
	#endif
	setT4_5();
	loadA(regB);
	#ifdef POSTCODE78
		POSTCODE78
	#endif
}
void code79(){
	//LD A,C
	#ifdef PRECODE79
		PRECODE79
	#endif
	setT4_5();
	loadA(regC);
	#ifdef POSTCODE79
		POSTCODE79
	#endif
}
void code7A(){
	//LD A,D
	#ifdef PRECODE7A
		PRECODE7A
	#endif
	setT4_5();
	loadA(regD);
	#ifdef POSTCODE7A
		POSTCODE7A
	#endif
}
void code7B(){
	//LD A,E
	#ifdef PRECODE7B
		PRECODE7B
	#endif
	setT4_5();
	loadA(regE);
	#ifdef POSTCODE7B
		POSTCODE7B
	#endif
}
void code7C(){
	//LD A,H
	#ifdef PRECODE7C
		PRECODE7C
	#endif
	setT4_5();
	loadA(regH);
	#ifdef POSTCODE7C
		POSTCODE7C
	#endif
}
void code7D(){
	//LD A,L
	#ifdef PRECODE7D
		PRECODE7D
	#endif
	setT4_5();
	loadA(regL);
	#ifdef POSTCODE7D
		POSTCODE7D
	#endif
}
void code7E(){
	//LD A,(HL)
	#ifdef PRECODE7E
		PRECODE7E
	#endif
	setT7();
	loadA(readMemory(regHL));
	#ifdef POSTCODE7E
		POSTCODE7E
	#endif
}
void code7F(){
	//LD A,A
	#ifdef PRECODE7F
		PRECODE7F
	#endif
	setT4_5();
	loadA(regA);
	#ifdef POSTCODE7F
		POSTCODE7F
	#endif
}
void code80(){
	//ADD A,B
	#ifdef PRECODE80
		PRECODE80
	#endif
	setT4();
	z80ADD(regB);
	#ifdef POSTCODE80
		POSTCODE80
	#endif
}
void code81(){
	//ADD A,C
	#ifdef PRECODE81
		PRECODE81
	#endif
	setT4();
	z80ADD(regC);
	#ifdef POSTCODE81
		POSTCODE81
	#endif
}
void code82(){
	//ADD A,D
	#ifdef PRECODE82
		PRECODE82
	#endif
	setT4();
	z80ADD(regD);
	#ifdef POSTCODE82
		POSTCODE82
	#endif
}
void code83(){
	//ADD A,E
	#ifdef PRECODE83
		PRECODE83
	#endif
	setT4();
	z80ADD(regE);
	#ifdef POSTCODE83
		POSTCODE83
	#endif
}
void code84(){
	//ADD A,H
	#ifdef PRECODE84
		PRECODE84
	#endif
	setT4();
	z80ADD(regH);
	#ifdef POSTCODE84
		POSTCODE84
	#endif
}
void code85(){
	//ADD A,L
	#ifdef PRECODE85
		PRECODE85
	#endif
	setT4();
	z80ADD(regL);
	#ifdef POSTCODE85
		POSTCODE85
	#endif
}
void code86(){
	//ADD A,(HL)
	#ifdef PRECODE86
		PRECODE86
	#endif
	setT7();
	z80ADD(readMemory(regHL));
	#ifdef POSTCODE86
		POSTCODE86
	#endif
}
void code87(){
	//ADD A,A
	#ifdef PRECODE87
		PRECODE87
	#endif
	setT4();
	z80ADD(regA);
	#ifdef POSTCODE87
		POSTCODE87
	#endif
}
void code88(){
	//ADC A,B
	#ifdef PRECODE88
		PRECODE88
	#endif
	setT4();
	z80ADC(regB);
	#ifdef POSTCODE88
		POSTCODE88
	#endif
}
void code89(){
	//ADC A,C
	#ifdef PRECODE89
		PRECODE89
	#endif
	setT4();
	z80ADC(regC);
	#ifdef POSTCODE89
		POSTCODE89
	#endif
}
void code8A(){
	//ADC A,D
	#ifdef PRECODE8A
		PRECODE8A
	#endif
	setT4();
	z80ADC(regD);
	#ifdef POSTCODE8A
		POSTCODE8A
	#endif
}
void code8B(){
	//ADC A,E
	#ifdef PRECODE8B
		PRECODE8B
	#endif
	setT4();
	z80ADC(regE);
	#ifdef POSTCODE8B
		POSTCODE8B
	#endif
}
void code8C(){
	//ADC A,H
	#ifdef PRECODE8C
		PRECODE8C
	#endif
	setT4();
	z80ADC(regH);
	#ifdef POSTCODE8C
		POSTCODE8C
	#endif
}
void code8D(){
	//ADC A,L
	#ifdef PRECODE8D
		PRECODE8D
	#endif
	setT4();
	z80ADC(regL);
	#ifdef POSTCODE8D
		POSTCODE8D
	#endif
}
void code8E(){
	//ADC A,(HL)
	#ifdef PRECODE8E
		PRECODE8E
	#endif
	setT7();
	z80ADC(readMemory(regHL));
	#ifdef POSTCODE8E
		POSTCODE8E
	#endif
}
void code8F(){
	//ADC A,A
	#ifdef PRECODE8F
		PRECODE8F
	#endif
	setT4();
	z80ADC(regA);
	#ifdef POSTCODE8F
		POSTCODE8F
	#endif
}
void code90(){
	//SUB B
	#ifdef PRECODE90
		PRECODE90
	#endif
	setT4();
	z80SUB(regB);
	#ifdef POSTCODE90
		POSTCODE90
	#endif
}
void code91(){
	//SUB C
	#ifdef PRECODE91
		PRECODE91
	#endif
	setT4();
	z80SUB(regC);
	#ifdef POSTCODE91
		POSTCODE91
	#endif
}
void code92(){
	//SUB D
	#ifdef PRECODE92
		PRECODE92
	#endif
	setT4();
	z80SUB(regD);
	#ifdef POSTCODE92
		POSTCODE92
	#endif
}
void code93(){
	//SUB E
	#ifdef PRECODE93
		PRECODE93
	#endif
	setT4();
	z80SUB(regE);
	#ifdef POSTCODE93
		POSTCODE93
	#endif
}
void code94(){
	//SUB H
	#ifdef PRECODE94
		PRECODE94
	#endif
	setT4();
	z80SUB(regH);
	#ifdef POSTCODE94
		POSTCODE94
	#endif
}
void code95(){
	//SUB L
	#ifdef PRECODE95
		PRECODE95
	#endif
	setT4();
	z80SUB(regL);
	#ifdef POSTCODE95
		POSTCODE95
	#endif
}
void code96(){
	//SUB (HL)
	#ifdef PRECODE96
		PRECODE96
	#endif
	setT7();
	z80SUB(readMemory(regHL));
	#ifdef POSTCODE96
		POSTCODE96
	#endif
}
void code97(){
	//SUB A
	#ifdef PRECODE97
		PRECODE97
	#endif
	setT4();
	z80SUB(regA);
	#ifdef POSTCODE97
		POSTCODE97
	#endif
}
void code98(){
	//SBC A,B
	#ifdef PRECODE98
		PRECODE98
	#endif
	setT4();
	z80SBC(regB);
	#ifdef POSTCODE98
		POSTCODE98
	#endif
}
void code99(){
	//SBC A,C
	#ifdef PRECODE99
		PRECODE99
	#endif
	setT4();
	z80SBC(regC);
	#ifdef POSTCODE99
		POSTCODE99
	#endif
}
void code9A(){
	//SBC A,D
	#ifdef PRECODE9A
		PRECODE9A
	#endif
	setT4();
	z80SBC(regD);
	#ifdef POSTCODE9A
		POSTCODE9A
	#endif
}
void code9B(){
	//SBC A,E
	#ifdef PRECODE9B
		PRECODE9B
	#endif
	setT4();
	z80SBC(regE);
	#ifdef POSTCODE9B
		POSTCODE9B
	#endif
}
void code9C(){
	//SBC A,H
	#ifdef PRECODE9C
		PRECODE9C
	#endif
	setT4();
	z80SBC(regH);
	#ifdef POSTCODE9C
		POSTCODE9C
	#endif
}
void code9D(){
	//SBC A,L
	#ifdef PRECODE9D
		PRECODE9D
	#endif
	setT4();
	z80SBC(regL);
	#ifdef POSTCODE9D
		POSTCODE9D
	#endif
}
void code9E(){
	//SBC A,(HL)
	#ifdef PRECODE9E
		PRECODE9E
	#endif
	setT7();
	z80SBC(readMemory(regHL));
	#ifdef POSTCODE9E
		POSTCODE9E
	#endif
}
void code9F(){
	//SBC A,A
	#ifdef PRECODE9F
		PRECODE9F
	#endif
	setT4();
	z80SBC(regA);
	#ifdef POSTCODE9F
		POSTCODE9F
	#endif
}
void codeA0(){
	//AND B
	#ifdef PRECODEA0
		PRECODEA0
	#endif
	setT4();
	z80AND(regB);
	#ifdef POSTCODEA0
		POSTCODEA0
	#endif
}
void codeA1(){
	//AND C
	#ifdef PRECODEA1
		PRECODEA1
	#endif
	setT4();
	z80AND(regC);
	#ifdef POSTCODEA1
		POSTCODEA1
	#endif
}
void codeA2(){
	//AND D
	#ifdef PRECODEA2
		PRECODEA2
	#endif
	setT4();
	z80AND(regD);
	#ifdef POSTCODEA2
		POSTCODEA2
	#endif
}
void codeA3(){
	//AND E
	#ifdef PRECODEA3
		PRECODEA3
	#endif
	setT4();
	z80AND(regE);
	#ifdef POSTCODEA3
		POSTCODEA3
	#endif
}
void codeA4(){
	//AND H
	#ifdef PRECODEA4
		PRECODEA4
	#endif
	setT4();
	z80AND(regH);
	#ifdef POSTCODEA4
		POSTCODEA4
	#endif
}
void codeA5(){
	//AND L
	#ifdef PRECODEA5
		PRECODEA5
	#endif
	setT4();
	z80AND(regL);
	#ifdef POSTCODEA5
		POSTCODEA5
	#endif
}
void codeA6(){
	//AND (HL)
	#ifdef PRECODEA6
		PRECODEA6
	#endif
	setT7();
	z80AND(readMemory(regHL));
	#ifdef POSTCODEA6
		POSTCODEA6
	#endif
}
void codeA7(){
	//AND A
	#ifdef PRECODEA7
		PRECODEA7
	#endif
	setT4();
	z80AND(regA);
	#ifdef POSTCODEA7
		POSTCODEA7
	#endif
}
void codeA8(){
	//XOR B
	#ifdef PRECODEA8
		PRECODEA8
	#endif
	setT4();
	z80XOR(regB);
	#ifdef POSTCODEA8
		POSTCODEA8
	#endif
}
void codeA9(){
	//XOR C
	#ifdef PRECODEA9
		PRECODEA9
	#endif
	setT4();
	z80XOR(regC);
	#ifdef POSTCODEA9
		POSTCODEA9
	#endif
}
void codeAA(){
	//XOR D
	#ifdef PRECODEAA
		PRECODEAA
	#endif
	setT4();
	z80XOR(regD);
	#ifdef POSTCODEAA
		POSTCODEAA
	#endif
}
void codeAB(){
	//XOR E
	#ifdef PRECODEAB
		PRECODEAB
	#endif
	setT4();
	z80XOR(regE);
	#ifdef POSTCODEAB
		POSTCODEAB
	#endif
}
void codeAC(){
	//XOR H
	#ifdef PRECODEAC
		PRECODEAC
	#endif
	setT4();
	z80XOR(regH);
	#ifdef POSTCODEAC
		POSTCODEAC
	#endif
}
void codeAD(){
	//XOR L
	#ifdef PRECODEAD
		PRECODEAD
	#endif
	setT4();
	z80XOR(regL);
	#ifdef POSTCODEAD
		POSTCODEAD
	#endif
}
void codeAE(){
	//XOR (HL)
	#ifdef PRECODEAE
		PRECODEAE
	#endif
	setT7();
	z80XOR(readMemory(regHL));
	#ifdef POSTCODEAE
		POSTCODEAE
	#endif
}
void codeAF(){
	//XOR A
	#ifdef PRECODEAF
		PRECODEAF
	#endif
	setT4();
	z80XOR(regA);
	#ifdef POSTCODEAF
		POSTCODEAF
	#endif
}
void codeB0(){
	//OR B
	#ifdef PRECODEB0
		PRECODEB0
	#endif
	setT4();
	z80OR(regB);
	#ifdef POSTCODEB0
		POSTCODEB0
	#endif
}
void codeB1(){
	//OR C
	#ifdef PRECODEB1
		PRECODEB1
	#endif
	setT4();
	z80OR(regC);
	#ifdef POSTCODEB1
		POSTCODEB1
	#endif
}
void codeB2(){
	//OR D
	#ifdef PRECODEB2
		PRECODEB2
	#endif
	setT4();
	z80OR(regD);
	#ifdef POSTCODEB2
		POSTCODEB2
	#endif
}
void codeB3(){
	//OR E
	#ifdef PRECODEB3
		PRECODEB3
	#endif
	setT4();
	z80OR(regE);
	#ifdef POSTCODEB3
		POSTCODEB3
	#endif
}
void codeB4(){
	//OR H
	#ifdef PRECODEB4
		PRECODEB4
	#endif
	setT4();
	z80OR(regH);
	#ifdef POSTCODEB4
		POSTCODEB4
	#endif
}
void codeB5(){
	//OR L
	#ifdef PRECODEB5
		PRECODEB5
	#endif
	setT4();
	z80OR(regL);
	#ifdef POSTCODEB5
		POSTCODEB5
	#endif
}
void codeB6(){
	//OR (HL)
	#ifdef PRECODEB6
		PRECODEB6
	#endif
	setT7();
	z80OR(readMemory(regHL));
	#ifdef POSTCODEB6
		POSTCODEB6
	#endif
}
void codeB7(){
	//OR A
	#ifdef PRECODEB7
		PRECODEB7
	#endif
	setT4();
	z80OR(regA);
	#ifdef POSTCODEB7
		POSTCODEB7
	#endif
}
void codeB8(){
	//CP B
	#ifdef PRECODEB8
		PRECODEB8
	#endif
	setT4();
	z80CP(regB);
	#ifdef POSTCODEB8
		POSTCODEB8
	#endif
}
void codeB9(){
	//CP C
	#ifdef PRECODEB9
		PRECODEB9
	#endif
	setT4();
	z80CP(regC);
	#ifdef POSTCODEB9
		POSTCODEB9
	#endif
}
void codeBA(){
	//CP D
	#ifdef PRECODEBA
		PRECODEBA
	#endif
	setT4();
	z80CP(regD);
	#ifdef POSTCODEBA
		POSTCODEBA
	#endif
}
void codeBB(){
	//CP E
	#ifdef PRECODEBB
		PRECODEBB
	#endif
	setT4();
	z80CP(regE);
	#ifdef POSTCODEBB
		POSTCODEBB
	#endif
}
void codeBC(){
	//CP H
	#ifdef PRECODEBC
		PRECODEBC
	#endif
	setT4();
	z80CP(regH);
	#ifdef POSTCODEBC
		POSTCODEBC
	#endif
}
void codeBD(){
	//CP L
	#ifdef PRECODEBD
		PRECODEBD
	#endif
	setT4();
	z80CP(regL);
	#ifdef POSTCODEBD
		POSTCODEBD
	#endif
}
void codeBE(){
	//CP (HL)
	#ifdef PRECODEBE
		PRECODEBE
	#endif
	setT7();
	z80CP(readMemory(regHL));
	#ifdef POSTCODEBE
		POSTCODEBE
	#endif
}
void codeBF(){
	//CP A
	#ifdef PRECODEBF
		PRECODEBF
	#endif
	setT4();
	z80CP(regA);
	#ifdef POSTCODEBF
		POSTCODEBF
	#endif
}
void codeC0(){
	UINT8 i8;
	UINT16 i16;
	//RET NZ
	#ifdef PRECODEC0
		PRECODEC0
	#endif
	if (flagZ) {
		setT5();
	} else {
		setT11();
		i8=readMemory(regSP);
		i16=readMemory(regSP+1)<<8;
		i16|=i8;
		loadPC(i16);
		loadSP(regSP+2);
	}
	#ifdef POSTCODEC0
		POSTCODEC0
	#endif
}
void codeC1(){
	//POP BC
	#ifdef PRECODEC1
		PRECODEC1
	#endif
	setT10();
	loadC(readMemory(regSP));
	loadB(readMemory(regSP+1));
	loadSP(regSP+2);
	#ifdef POSTCODEC1
		POSTCODEC1
	#endif
}
void codeC2(){
	UINT8 i8;
	UINT16 i16;
	//JP NZ,nn
	#ifdef PRECODEC2
		PRECODEC2
	#endif
	setT10();
	i8=getCode();
	i16=getCode();
	if (!flagZ) loadPC( (i16<<8) | i8);
	#ifdef POSTCODEC2
		POSTCODEC2
	#endif
}
void codeC3(){
	UINT8 i8;
	UINT16 i16;
	//JP nn
	#ifdef PRECODEC3
		PRECODEC3
	#endif
	setT10();
	i8=getCode();
	i16=getCode();
	loadPC( (i16<<8) | i8);
	#ifdef POSTCODEC3
		POSTCODEC3
	#endif
}
void codeC4(){
	UINT8 i8;
	UINT16 i16;
	//CALL NZ,nn
	#ifdef PRECODEC4
		PRECODEC4
	#endif
	i8=getCode();
	i16=getCode();
	if (flagZ){
		setT10_11();
	} else {
		setT17();
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC((i16<<8)|i8);
	}
	#ifdef POSTCODEC4
		POSTCODEC4
	#endif
}
void codeC5(){
	//PUSH BC
	#ifdef PRECODEC5
		PRECODEC5
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regC);
	writeMemory(regSP+1,regB);
	#ifdef POSTCODEC5
		POSTCODEC5
	#endif
}
void codeC6(){
	//ADD A,n
	#ifdef PRECODEC6
		PRECODEC6
	#endif
	setT7();
	z80ADD(getCode());
	#ifdef POSTCODEC6
		POSTCODEC6
	#endif
}
void codeC7(){
	//RST 0H
	#ifdef PRECODEC7
		PRECODEC7
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC(0x00);
	#ifdef POSTCODEC7
		POSTCODEC7
	#endif
}
void codeC8(){
	UINT8 i8;
	UINT16 i16;
	//RET Z
	#ifdef PRECODEC8
		PRECODEC8
	#endif
	if (flagZ) {
		setT11();
		i8=readMemory(regSP);
		i16=readMemory(regSP+1)<<8;
		i16|=i8;
		loadPC(i16);
		loadSP(regSP+2);
	} else {
		setT5();
	}
	#ifdef POSTCODEC8
		POSTCODEC8
	#endif
}
void codeC9(){
	UINT8 i8;
	UINT16 i16;
	//RET
	#ifdef PRECODEC9
		PRECODEC9
	#endif
	setT10();
	i8=readMemory(regSP);
	i16=readMemory(regSP+1)<<8;
	i16|=i8;
	loadPC(i16);
	loadSP(regSP+2);
	#ifdef POSTCODEC9
		POSTCODEC9
	#endif
}
void codeCA(){
	UINT8 i8;
	UINT16 i16;
	//JP Z,nn
	#ifdef PRECODECA
		PRECODECA
	#endif
	setT10();
	i8=getCode();
	i16=getCode();
	if (flagZ) loadPC( (i16<<8) | i8);
	#ifdef POSTCODECA
		POSTCODECA
	#endif
}
void codeCC(){
	UINT8 i8;
	UINT16 i16;
	//CALL Z,nn
	#ifdef PRECODECC
		PRECODECC
	#endif
	i8=getCode();
	i16=getCode();
	if (flagZ){
		setT17();
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC((i16<<8)|i8);
	} else {
		setT10_11();
	}
	#ifdef POSTCODECC
		POSTCODECC
	#endif
}
void codeCD(){
	UINT8 i8;
	UINT16 i16;
	//CALL nn
	#ifdef PRECODECD
		PRECODECD
	#endif
	setT17();
	i8=getCode();
	i16=getCode();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC((i16<<8)|i8);
	#ifdef POSTCODECD
		POSTCODECD
	#endif
}
void codeCE(){
	//ADC A,n
	#ifdef PRECODECE
		PRECODECE
	#endif
	setT7();
	z80ADC(getCode());
	#ifdef POSTCODECE
		POSTCODECE
	#endif
}
void codeCF(){
	//RST 8H
	#ifdef PRECODECF
		PRECODECF
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC(0x08);
	#ifdef POSTCODECF
		POSTCODECF
	#endif
}
void codeD0(){
	UINT8 i8;
	UINT16 i16;
	//RET NC
	#ifdef PRECODED0
		PRECODED0
	#endif
	if (flagC) {
		setT5();
	} else {
		setT11();
		i8=readMemory(regSP);
		i16=readMemory(regSP+1)<<8;
		i16|=i8;
		loadPC(i16);
		loadSP(regSP+2);
	}
	#ifdef POSTCODED0
		POSTCODED0
	#endif
}
void codeD1(){
	//POP DE
	#ifdef PRECODED1
		PRECODED1
	#endif
	setT10();
	loadE(readMemory(regSP));
	loadD(readMemory(regSP+1));
	loadSP(regSP+2);
	#ifdef POSTCODED1
		POSTCODED1
	#endif
}
void codeD2(){
	UINT8 i8;
	UINT16 i16;
	//JP NC,nn
	#ifdef PRECODED2
		PRECODED2
	#endif
	setT10();
	i8=getCode();
	i16=getCode();
	if (!flagC) loadPC( (i16<<8) | i8);
	#ifdef POSTCODED2
		POSTCODED2
	#endif
}
void codeD3(){
	//OUT (n),A
	#ifdef PRECODED3
		PRECODED3
	#endif
	setT11_10();
	writeIO(getCode(),regA,regA);
	#ifdef POSTCODED3
		POSTCODED3
	#endif
}
void codeD4(){
	UINT8 i8;
	UINT16 i16;
	//CALL NC,nn
	#ifdef PRECODED4
		PRECODED4
	#endif
	i8=getCode();
	i16=getCode();
	if (flagC){
		setT10_11();
	} else {
		setT17();
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC((i16<<8)|i8);
	}
	#ifdef POSTCODED4
		POSTCODED4
	#endif
}
void codeD5(){
	//PUSH DE
	#ifdef PRECODED5
		PRECODED5
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regE);
	writeMemory(regSP+1,regD);
	#ifdef POSTCODED5
		POSTCODED5
	#endif
}
void codeD6(){
	//SUB n
	#ifdef PRECODED6
		PRECODED6
	#endif
	setT7();
	z80SUB(getCode());
	#ifdef POSTCODED6
		POSTCODED6
	#endif
}
void codeD7(){
	//RST 10H
	#ifdef PRECODED7
		PRECODED7
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC(0x10);
	#ifdef POSTCODED7
		POSTCODED7
	#endif
}
void codeD8(){
	UINT8 i8;
	UINT16 i16;
	//RET C
	#ifdef PRECODED8
		PRECODED8
	#endif
	if (flagC) {
		setT11();
		i8=readMemory(regSP);
		i16=readMemory(regSP+1)<<8;
		i16|=i8;
		loadPC(i16);
		loadSP(regSP+2);
	} else {
		setT5();
	}
	#ifdef POSTCODED8
		POSTCODED8
	#endif
}
#ifdef Z80
void codeD9(){
	UINT16 i16;
	//EXX
	#ifdef PRECODED9
		PRECODED9
	#endif
	setT4();
	i16=regBC;
	loadBC(regBCprime);
	loadBCprime(i16);
	i16=regDE;
	loadDE(regDEprime);
	loadDEprime(i16);
	i16=regHL;
	loadHL(regHLprime);
	loadHLprime(i16);
	#ifdef POSTCODED9
		POSTCODED9
	#endif
}
#endif
void codeDA(){
	UINT8 i8;
	UINT16 i16;
	//JP C,nn
	#ifdef PRECODEDA
		PRECODEDA
	#endif
	setT10();
	i8=getCode();
	i16=getCode();
	if (flagC) loadPC( (i16<<8) | i8);
	#ifdef POSTCODEDA
		POSTCODEDA
	#endif
}
void codeDB(){
	//IN A,n
	#ifdef PRECODEDB
		PRECODEDB
	#endif
	setT11_10();
	loadA(readIO(getCode(), regA));
	#ifdef POSTCODEDB
		POSTCODEDB
	#endif
}
void codeDC(){
	UINT8 i8;
	UINT16 i16;
	//CALL C,nn
	#ifdef PRECODEDC
		PRECODEDC
	#endif
	i8=getCode();
	i16=getCode();
	if (flagC){
		setT17();
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC((i16<<8)|i8);
	} else {
		setT10_11();
	}
	#ifdef POSTCODEDC
		POSTCODEDC
	#endif
}
void codeDE(){
	//SBC   A,n
	#ifdef PRECODEDE
		PRECODEDE
	#endif
	setT7();
	z80SBC(getCode());
	#ifdef POSTCODEDE
		POSTCODEDE
	#endif
}
void codeDF(){
	//RST   18H
	#ifdef PRECODEDF
		PRECODEDF
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC(0x18);
	#ifdef POSTCODEDF
		POSTCODEDF
	#endif
}
void codeE0(){
	UINT8 i8;
	UINT16 i16;
	//RET   PO
	#ifdef PRECODEE0
		PRECODEE0
	#endif
	if (flagP) {
		setT5();
	} else {
		setT11();
		i8=readMemory(regSP);
		i16=readMemory(regSP+1)<<8;
		i16|=i8;
		loadPC(i16);
		loadSP(regSP+2);
	}
	#ifdef POSTCODEE0
		POSTCODEE0
	#endif
}
void codeE1(){
	//POP   HL
	#ifdef PRECODEE1
		PRECODEE1
	#endif
	setT10();
	loadL(readMemory(regSP));
	loadH(readMemory(regSP+1));
	loadSP(regSP+2);
	#ifdef POSTCODEE1
		POSTCODEE1
	#endif
}
void codeE2(){
	UINT8 i8;
	UINT16 i16;
	//E2   JP    PO,nn
	#ifdef PRECODEE2
		PRECODEE2
	#endif
	setT10();
	i8=getCode();
	i16=getCode();
	if (!flagP) loadPC( (i16<<8) | i8);
	#ifdef POSTCODEE2
		POSTCODEE2
	#endif
}
void codeE3(){
	UINT16 i16;
	//EX    (SP),HL
	#ifdef PRECODEE3
		PRECODEE3
	#endif
	setT19_18();
	i16=readMemory(regSP+1)<<8;
	i16|=readMemory(regSP);
	writeMemory(regSP,regL);
	writeMemory(regSP+1,regH);
	loadHL(i16);
	#ifdef POSTCODEE3
		POSTCODEE3
	#endif
}
void codeE4(){
	UINT8 i8;
	UINT16 i16;
	//CALL  PO,nn
	#ifdef PRECODEE4
		PRECODEE4
	#endif
	i8=getCode();
	i16=getCode();
	if (flagP){
		setT10_11();
	} else {
		setT17();
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC((i16<<8)|i8);
	}
	#ifdef POSTCODEE4
		POSTCODEE4
	#endif
}
void codeE5(){
	//PUSH  HL
	#ifdef PRECODEE5
		PRECODEE5
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regL);
	writeMemory(regSP+1,regH);
	#ifdef POSTCODEE5
		POSTCODEE5
	#endif
}
void codeE6(){
	//AND   n
	#ifdef PRECODEE6
		PRECODEE6
	#endif
	setT7();
	z80AND(getCode());
	#ifdef POSTCODEE6
		POSTCODEE6
	#endif
}
void codeE7(){
	//RST   20H
	#ifdef PRECODEE7
		PRECODEE7
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC(0x20);
	#ifdef POSTCODEE7
		POSTCODEE7
	#endif
}
void codeE8(){
	UINT8 i8;
	UINT16 i16;
	//RET   PE
	#ifdef PRECODEE8
		PRECODEE8
	#endif
	if (flagP) {
		setT11();
		i8=readMemory(regSP);
		i16=readMemory(regSP+1)<<8;
		i16|=i8;
		loadPC(i16);
		loadSP(regSP+2);
	} else {
		setT5();
	}
	#ifdef POSTCODEE8
		POSTCODEE8
	#endif
}
void codeE9(){
	//JP    (HL)
	#ifdef PRECODEE9
		PRECODEE9
	#endif
	setT4_5();
	loadPC(regHL);
	#ifdef POSTCODEE9
		POSTCODEE9
	#endif
}
void codeEA(){
	UINT8 i8;
	UINT16 i16;
	//JP    PE,nn
	#ifdef PRECODEEA
		PRECODEEA
	#endif
	setT10();
	i8=getCode();
	i16=getCode();
	if (flagP) loadPC( (i16<<8) | i8);
	#ifdef POSTCODEEA
		POSTCODEEA
	#endif
}
void codeEB(){
	UINT16 i16;
	//EX    DE,HL
	#ifdef PRECODEEB
		PRECODEEB
	#endif
	setT4();
	i16=regHL;
	loadHL(regDE);
	loadDE(i16);
	#ifdef POSTCODEEB
		POSTCODEEB
	#endif
}
void codeEC(){
	UINT8 i8;
	UINT16 i16;
	//CALL  PE,NN
	#ifdef PRECODEEC
		PRECODEEC
	#endif
	i8=getCode();
	i16=getCode();
	if (flagP){
		setT17();
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC((i16<<8)|i8);
	} else {
		setT10_11();
	}
	#ifdef POSTCODEEC
		POSTCODEEC
	#endif
}
void codeEE(){
	//XOR   n
	#ifdef PRECODEEE
		PRECODEEE
	#endif
	setT7();
	z80XOR(getCode());
	#ifdef POSTCODEEE
		POSTCODEEE
	#endif
}
void codeEF(){
	//RST   28H
	#ifdef PRECODEEF
		PRECODEEF
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC(0x28);
	#ifdef POSTCODEEF
		POSTCODEEF
	#endif
}
void codeF0(){
	UINT8 i8;
	UINT16 i16;
	//RET   P
	#ifdef PRECODEF0
		PRECODEF0
	#endif
	if (flagS) {
		setT5();
	} else {
		setT11();
		i8=readMemory(regSP);
		i16=readMemory(regSP+1)<<8;
		i16|=i8;
		loadPC(i16);
		loadSP(regSP+2);
	}
	#ifdef POSTCODEF0
		POSTCODEF0
	#endif
}
void codeF1(){
	//POP   AF
	#ifdef PRECODEF1
		PRECODEF1
	#endif
	setT10();
	loadF(readMemory(regSP));
	loadA(readMemory(regSP+1));
	loadSP(regSP+2);
	#ifdef POSTCODEF1
		POSTCODEF1
	#endif
}
void codeF2(){
	UINT8 i8;
	UINT16 i16;
	//F2   JP    P,nn
	#ifdef PRECODEF2
		PRECODEF2
	#endif
	setT10();
	setT10();
	i8=getCode();
	i16=getCode();
	if (!flagS) loadPC( (i16<<8) | i8);
	#ifdef POSTCODEF2
		POSTCODEF2
	#endif
}
void codeF3(){
	//DI
	#ifdef PRECODEF3
		PRECODEF3
	#endif
	setT4();
	loadIFF1(0);
	loadIFF2(0);
	#ifdef POSTCODEF3
		POSTCODEF3
	#endif
}
void codeF4(){
	UINT8 i8;
	UINT16 i16;
	//CALL  P,nn
	#ifdef PRECODEF4
		PRECODEF4
	#endif
	i8=getCode();
	i16=getCode();
	if (flagS){
		setT10_11();
	} else {
		setT17();
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC((i16<<8)|i8);
	}
	#ifdef POSTCODEF4
		POSTCODEF4
	#endif
}
void codeF5(){
	//PUSH  AF
	#ifdef PRECODEF5
		PRECODEF5
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regF);
	writeMemory(regSP+1,regA);
	#ifdef POSTCODEF5
		POSTCODEF5
	#endif
}
void codeF6(){
	//F6   OR    n
	#ifdef PRECODEF6
		PRECODEF6
	#endif
	setT7();
	z80OR(getCode());
	#ifdef POSTCODEF6
		POSTCODEF6
	#endif
}
void codeF7(){
	//RST   30H
	#ifdef PRECODEF7
		PRECODEF7
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC(0x30);
	#ifdef POSTCODEF7
		POSTCODEF7
	#endif
}
void codeF8(){
	UINT8 i8;
	UINT16 i16;
	//RET   M
	#ifdef PRECODEF8
		PRECODEF8
	#endif
	if (flagS) {
		setT11();
		i8=readMemory(regSP);
		i16=readMemory(regSP+1)<<8;
		i16|=i8;
		loadPC(i16);
		loadSP(regSP+2);
	} else {
		setT5();
	}
	#ifdef POSTCODEF8
		POSTCODEF8
	#endif
}
void codeF9(){
	//LD    SP,HL
	#ifdef PRECODEF9
		PRECODEF9
	#endif
	setT6_5();
	loadSP(regHL);
	#ifdef POSTCODEF9
		POSTCODEF9
	#endif
}
void codeFA(){
	UINT8 i8;
	UINT16 i16;
	//FA   JP    M,nn
	#ifdef PRECODEFA
		PRECODEFA
	#endif
	setT10();
	i8=getCode();
	i16=getCode();
	if (flagS) loadPC( (i16<<8) | i8);
	#ifdef POSTCODEFA
		POSTCODEFA
	#endif
}
void codeFB(){
	//EI
	#ifdef PRECODEFB
		PRECODEFB
	#endif
	setT4();
	loadIFF1(1);
	loadIFF2(1);
	#ifdef POSTCODEFB
		POSTCODEFB
	#endif
}
void codeFC(){
	UINT8 i8;
	UINT16 i16;
	//CALL  M,nn
	#ifdef PRECODEFC
		PRECODEFC
	#endif
	i8=getCode();
	i16=getCode();
	if (flagS){
		setT17();
		loadSP(regSP-2);
		writeMemory(regSP,regPC&0xFF);
		writeMemory(regSP+1,regPC>>8);
		loadPC((i16<<8)|i8);
	} else {
		setT10_11();
	}
	#ifdef POSTCODEFC
		POSTCODEFC
	#endif
}
void codeFE(){
	//FE   CP    n
	#ifdef PRECODEFE
		PRECODEFE
	#endif
	setT7();
	z80CP(getCode());
	#ifdef POSTCODEFE
		POSTCODEFE
	#endif
}
void codeFF(){
	//RST   38H
	#ifdef PRECODEFF
		PRECODEFF
	#endif
	setT11();
	loadSP(regSP-2);
	writeMemory(regSP,regPC&0xFF);
	writeMemory(regSP+1,regPC>>8);
	loadPC(0x38);
	#ifdef POSTCODEFF
		POSTCODEFF
	#endif
}
#ifdef Z80
void codeCB00(){
	//RLC   B
	#ifdef PRECODECB00
		PRECODECB00
	#endif
	setT8();
	loadB(z80RLC(regB));
	#ifdef POSTCODECB00
		POSTCODECB00
	#endif
}
void codeCB01(){
	//RLC   C
	#ifdef PRECODECB01
		PRECODECB01
	#endif
	setT8();
	loadC(z80RLC(regC));
	#ifdef POSTCODECB01
		POSTCODECB01
	#endif
}
void codeCB02(){
	//RLC   D
	#ifdef PRECODECB02
		PRECODECB02
	#endif
	setT8();
	loadD(z80RLC(regD));
	#ifdef POSTCODECB02
		POSTCODECB02
	#endif
}
void codeCB03(){
	//RLC   E
	#ifdef PRECODECB03
		PRECODECB03
	#endif
	setT8();
	loadE(z80RLC(regE));
	#ifdef POSTCODECB03
		POSTCODECB03
	#endif
}
void codeCB04(){
	//RLC   H
	#ifdef PRECODECB04
		PRECODECB04
	#endif
	setT8();
	loadH(z80RLC(regH));
	#ifdef POSTCODECB04
		POSTCODECB04
	#endif
}
void codeCB05(){
	//RLC   L
	#ifdef PRECODECB05
		PRECODECB05
	#endif
	setT8();
	loadL(z80RLC(regL));
	#ifdef POSTCODECB05
		POSTCODECB05
	#endif
}
void codeCB06(){
	//RLC   (HL)
	#ifdef PRECODECB06
		PRECODECB06
	#endif
	setT15();
	writeMemory(regHL,z80RLC(readMemory(regHL)));
	#ifdef POSTCODECB06
		POSTCODECB06
	#endif
}
void codeCB07(){
	//RLC   A
	#ifdef PRECODECB07
		PRECODECB07
	#endif
	setT8();
	loadA(z80RLC(regA));
	#ifdef POSTCODECB07
		POSTCODECB07
	#endif
}
void codeCB08(){
	//RRC   B
	#ifdef PRECODECB08
		PRECODECB08
	#endif
	setT8();
	loadB(z80RRC(regB));
	#ifdef POSTCODECB08
		POSTCODECB08
	#endif
}
void codeCB09(){
	//RRC   C
	#ifdef PRECODECB09
		PRECODECB09
	#endif
	setT8();
	loadC(z80RRC(regC));
	#ifdef POSTCODECB09
		POSTCODECB09
	#endif
}
void codeCB0A(){
	//CRRC   D
	#ifdef PRECODECB0A
		PRECODECB0A
	#endif
	setT8();
	loadD(z80RRC(regD));
	#ifdef POSTCODECB0A
		POSTCODECB0A
	#endif
}
void codeCB0B(){
	//RRC   E
	#ifdef PRECODECB0B
		PRECODECB0B
	#endif
	setT8();
	loadE(z80RRC(regE));
	#ifdef POSTCODECB0B
		POSTCODECB0B
	#endif
}
void codeCB0C(){
	//RRC   H
	#ifdef PRECODECB0C
		PRECODECB0C
	#endif
	setT8();
	loadH(z80RRC(regH));
	#ifdef POSTCODECB0C
		POSTCODECB0C
	#endif
}
void codeCB0D(){
	//RRC   L
	#ifdef PRECODECB0D
		PRECODECB0D
	#endif
	setT8();
	loadL(z80RRC(regL));
	#ifdef POSTCODECB0D
		POSTCODECB0D
	#endif
}
void codeCB0E(){
	//RRC   (HL)
	#ifdef PRECODECB0E
		PRECODECB0E
	#endif
	setT15();
	writeMemory(regHL,z80RRC(readMemory(regHL)));
	#ifdef POSTCODECB0E
		POSTCODECB0E
	#endif
}
void codeCB0F(){
	//RRC   A
	#ifdef PRECODECB0F
		PRECODECB0F
	#endif
	setT8();
	loadA(z80RRC(regA));
	#ifdef POSTCODECB0F
		POSTCODECB0F
	#endif
}
void codeCB10(){
	//RL    B
	#ifdef PRECODECB10
		PRECODECB10
	#endif
	setT8();
	loadB(z80RL(regB));
	#ifdef POSTCODECB10
		POSTCODECB10
	#endif
}
void codeCB11(){
	//RL    C
	#ifdef PRECODECB11
		PRECODECB11
	#endif
	setT8();
	loadC(z80RL(regC));
	#ifdef POSTCODECB11
		POSTCODECB11
	#endif
}
void codeCB12(){
	//RL    D
	#ifdef PRECODECB12
		PRECODECB12
	#endif
	setT8();
	loadD(z80RL(regD));
	#ifdef POSTCODECB12
		POSTCODECB12
	#endif
}
void codeCB13(){
	//RL    E
	#ifdef PRECODECB13
		PRECODECB13
	#endif
	setT8();
	loadE(z80RL(regE));
	#ifdef POSTCODECB13
		POSTCODECB13
	#endif
}
void codeCB14(){
	//RL    H
	#ifdef PRECODECB14
		PRECODECB14
	#endif
	setT8();
	loadH(z80RL(regH));
	#ifdef POSTCODECB14
		POSTCODECB14
	#endif
}
void codeCB15(){
	//RL    L
	#ifdef PRECODECB15
		PRECODECB15
	#endif
	setT8();
	loadL(z80RL(regL));
	#ifdef POSTCODECB15
		POSTCODECB15
	#endif
}
void codeCB16(){
	//RL    (HL)
	#ifdef PRECODECB16
		PRECODECB16
	#endif
	setT15();
	writeMemory(regHL,z80RL(readMemory(regHL)));
	#ifdef POSTCODECB16
		POSTCODECB16
	#endif
}
void codeCB17(){
	//RL    A
	#ifdef PRECODECB17
		PRECODECB17
	#endif
	setT8();
	loadA(z80RL(regA));
	#ifdef POSTCODECB17
		POSTCODECB17
	#endif
}
void codeCB18(){
	//CB 18   RR    B
	#ifdef PRECODECB18
		PRECODECB18
	#endif
	setT8();
	loadB(z80RR(regB));
	#ifdef POSTCODECB18
		POSTCODECB18
	#endif
}
void codeCB19(){
	//CB 19   RR    C
	#ifdef PRECODECB19
		PRECODECB19
	#endif
	setT8();
	loadC(z80RR(regC));
	#ifdef POSTCODECB19
		POSTCODECB19
	#endif
}
void codeCB1A(){
	//CB 1A   RR    D
	#ifdef PRECODECB1A
		PRECODECB1A
	#endif
	setT8();
	loadD(z80RR(regD));
	#ifdef POSTCODECB1A
		POSTCODECB1A
	#endif
}
void codeCB1B(){
	//CB 1B   RR    E
	#ifdef PRECODECB1B
		PRECODECB1B
	#endif
	setT8();
	loadE(z80RR(regE));
	#ifdef POSTCODECB1B
		POSTCODECB1B
	#endif
}
void codeCB1C(){
	//CB 1C   RR    H
	#ifdef PRECODECB1C
		PRECODECB1C
	#endif
	setT8();
	loadH(z80RR(regH));
	#ifdef POSTCODECB1C
		POSTCODECB1C
	#endif
}
void codeCB1D(){
	//CB 1D   RR    L
	#ifdef PRECODECB1D
		PRECODECB1D
	#endif
	setT8();
	loadL(z80RR(regL));
	#ifdef POSTCODECB1D
		POSTCODECB1D
	#endif
}
void codeCB1E(){
	//CB 1E   RR    (HL)
	#ifdef PRECODECB1E
		PRECODECB1E
	#endif
	setT15();
	writeMemory(regHL,z80RR(readMemory(regHL)));
	#ifdef POSTCODECB1E
		POSTCODECB1E
	#endif
}
void codeCB1F(){
	//CB 1F   RR    A
	#ifdef PRECODECB1F
		PRECODECB1F
	#endif
	setT8();
	loadA(z80RR(regA));
	#ifdef POSTCODECB1F
		POSTCODECB1F
	#endif
}
void codeCB20(){
	//SLA   B
	#ifdef PRECODECB20
		PRECODECB20
	#endif
	setT8();
	loadB(z80SLA(regB));
	#ifdef POSTCODECB20
		POSTCODECB20
	#endif
}
void codeCB21(){
	//SLA   C
	#ifdef PRECODECB21
		PRECODECB21
	#endif
	setT8();
	loadC(z80SLA(regC));
	#ifdef POSTCODECB21
		POSTCODECB21
	#endif
}
void codeCB22(){
	//SLA   D
	#ifdef PRECODECB22
		PRECODECB22
	#endif
	setT8();
	loadD(z80SLA(regD));
	#ifdef POSTCODECB22
		POSTCODECB22
	#endif
}
void codeCB23(){
	//SLA   E
	#ifdef PRECODECB23
		PRECODECB23
	#endif
	setT8();
	loadE(z80SLA(regE));
	#ifdef POSTCODECB23
		POSTCODECB23
	#endif
}
void codeCB24(){
	//SLA   H
	#ifdef PRECODECB24
		PRECODECB24
	#endif
	setT8();
	loadH(z80SLA(regH));
	#ifdef POSTCODECB24
		POSTCODECB24
	#endif
}
void codeCB25(){
	//SLA   L
	#ifdef PRECODECB25
		PRECODECB25
	#endif
	setT8();
	loadL(z80SLA(regL));
	#ifdef POSTCODECB25
		POSTCODECB25
	#endif
}
void codeCB26(){
	//SLA   (HL)
	#ifdef PRECODECB26
		PRECODECB26
	#endif
	setT15();
	writeMemory(regHL,z80SLA(readMemory(regHL)));
	#ifdef POSTCODECB26
		POSTCODECB26
	#endif
}
void codeCB27(){
	//SLA   A
	#ifdef PRECODECB27
		PRECODECB27
	#endif
	setT8();
	loadA(z80SLA(regA));
	#ifdef POSTCODECB27
		POSTCODECB27
	#endif
}
void codeCB28(){
	//SRA   B
	#ifdef PRECODECB28
		PRECODECB28
	#endif
	setT8();
	loadB(z80SRA(regB));
	#ifdef POSTCODECB28
		POSTCODECB28
	#endif
}
void codeCB29(){
	//SRA   C
	#ifdef PRECODECB29
		PRECODECB29
	#endif
	setT8();
	loadC(z80SRA(regC));
	#ifdef POSTCODECB29
		POSTCODECB29
	#endif
}
void codeCB2A(){
	//SRA   D
	#ifdef PRECODECB2A
		PRECODECB2A
	#endif
	setT8();
	loadD(z80SRA(regD));
	#ifdef POSTCODECB2A
		POSTCODECB2A
	#endif
}
void codeCB2B(){
	//SRA   E
	#ifdef PRECODECB2B
		PRECODECB2B
	#endif
	setT8();
	loadE(z80SRA(regE));
	#ifdef POSTCODECB2B
		POSTCODECB2B
	#endif
}
void codeCB2C(){
	//SRA   H
	#ifdef PRECODECB2C
		PRECODECB2C
	#endif
	setT8();
	loadH(z80SRA(regH));
	#ifdef POSTCODECB2C
		POSTCODECB2C
	#endif
}
void codeCB2D(){
	//SRA   L
	#ifdef PRECODECB2D
		PRECODECB2D
	#endif
	setT8();
	loadL(z80SRA(regL));
	#ifdef POSTCODECB2D
		POSTCODECB2D
	#endif
}
void codeCB2E(){
	//SRA   (HL)
	#ifdef PRECODECB2E
		PRECODECB2E
	#endif
	setT15();
	writeMemory(regHL,z80SRA(readMemory(regHL)));
	#ifdef POSTCODECB2E
		POSTCODECB2E
	#endif
}
void codeCB2F(){
	//SRA   A
	#ifdef PRECODECB2F
		PRECODECB2F
	#endif
	setT8();
	loadA(z80SRA(regA));
	#ifdef POSTCODECB2F
		POSTCODECB2F
	#endif
}
void codeCB38(){
	//SRL   B
	#ifdef PRECODECB38
		PRECODECB38
	#endif
	setT8();
	loadB(z80SRL(regB));
	#ifdef POSTCODECB38
		POSTCODECB38
	#endif
}
void codeCB39(){
	//SRL   C
	#ifdef PRECODECB39
		PRECODECB39
	#endif
	setT8();
	loadC(z80SRL(regC));
	#ifdef POSTCODECB39
		POSTCODECB39
	#endif
}
void codeCB3A(){
	//SRL   D
	#ifdef PRECODECB3A
		PRECODECB3A
	#endif
	setT8();
	loadD(z80SRL(regD));
	#ifdef POSTCODECB3A
		POSTCODECB3A
	#endif
}
void codeCB3B(){
	//SRL   E
	#ifdef PRECODECB3B
		PRECODECB3B
	#endif
	setT8();
	loadE(z80SRL(regE));
	#ifdef POSTCODECB3B
		POSTCODECB3B
	#endif
}
void codeCB3C(){
	//SRL   H
	#ifdef PRECODECB3C
		PRECODECB3C
	#endif
	setT8();
	loadH(z80SRL(regH));
	#ifdef POSTCODECB3C
		POSTCODECB3C
	#endif
}
void codeCB3D(){
	//SRL   L
	#ifdef PRECODECB3D
		PRECODECB3D
	#endif
	setT8();
	loadL(z80SRL(regL));
	#ifdef POSTCODECB3D
		POSTCODECB3D
	#endif
}
void codeCB3E(){
	//SRL   (HL)
	#ifdef PRECODECB3E
		PRECODECB3E
	#endif
	setT15();
	writeMemory(regHL,z80SRL(readMemory(regHL)));
	#ifdef POSTCODECB3E
		POSTCODECB3E
	#endif
}
void codeCB3F(){
	//SRL   A
	#ifdef PRECODECB3F
		PRECODECB3F
	#endif
	setT8();
	loadA(z80SRL(regA));
	#ifdef POSTCODECB3F
		POSTCODECB3F
	#endif
}
void codeCB40(){
	//BIT   0,B
	#ifdef PRECODECB40
		PRECODECB40
	#endif
	setT8();
	if (0x01&regB) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB40
		POSTCODECB40
	#endif
}
void codeCB41(){
	//BIT   0,C
	#ifdef PRECODECB41
		PRECODECB41
	#endif
	setT8();
	if (0x01&regC) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB41
		POSTCODECB41
	#endif
}
void codeCB42(){
	//BIT   0,D
	#ifdef PRECODECB42
		PRECODECB42
	#endif
	setT8();
	if (0x01&regD) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB42
		POSTCODECB42
	#endif
}
void codeCB43(){
	//BIT   0,E
	#ifdef PRECODECB43
		PRECODECB43
	#endif
	setT8();
	if (0x01&regE) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB43
		POSTCODECB43
	#endif
}
void codeCB44(){
	//BIT   0,H
	#ifdef PRECODECB44
		PRECODECB44
	#endif
	setT8();
	if (0x01&regH) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB44
		POSTCODECB44
	#endif
}
void codeCB45(){
	//BIT   0,L
	#ifdef PRECODECB45
		PRECODECB45
	#endif
	setT8();
	if (0x01&regL) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB45
		POSTCODECB45
	#endif
}
void codeCB46(){
	//BIT   0,(HL)
	#ifdef PRECODECB46
		PRECODECB46
	#endif
	setT12();
	if (0x01&readMemory(regHL)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB46
		POSTCODECB46
	#endif
}
void codeCB47(){
	//BIT   0,A
	#ifdef PRECODECB47
		PRECODECB47
	#endif
	setT8();
	if (0x01&regA) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB47
		POSTCODECB47
	#endif
}
void codeCB48(){
	//BIT   1,B
	#ifdef PRECODECB48
		PRECODECB48
	#endif
	setT8();
	if (0x02&regB) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB48
		POSTCODECB48
	#endif
}
void codeCB49(){
	//BIT   1,C
	#ifdef PRECODECB49
		PRECODECB49
	#endif
	setT8();
	if (0x02&regC) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB49
		POSTCODECB49
	#endif
}
void codeCB4A(){
	//BIT   1,D
	#ifdef PRECODECB4A
		PRECODECB4A
	#endif
	setT8();
	if (0x02&regD) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB4A
		POSTCODECB4A
	#endif
}
void codeCB4B(){
	//BIT   1,E
	#ifdef PRECODECB4B
		PRECODECB4B
	#endif
	setT8();
	if (0x02&regE) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB4B
		POSTCODECB4B
	#endif
}
void codeCB4C(){
	//BIT   1,H
	#ifdef PRECODECB4C
		PRECODECB4C
	#endif
	setT8();
	if (0x02&regH) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB4C
		POSTCODECB4C
	#endif
}
void codeCB4D(){
	//BIT   1,L
	#ifdef PRECODECB4D
		PRECODECB4D
	#endif
	setT8();
	if (0x02&regL) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB4D
		POSTCODECB4D
	#endif
}
void codeCB4E(){
	//BIT   1,(HL)
	#ifdef PRECODECB4E
		PRECODECB4E
	#endif
	setT12();
	if (0x02&readMemory(regHL)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB4E
		POSTCODECB4E
	#endif
}
void codeCB4F(){
	//BIT   1,A
	#ifdef PRECODECB4F
		PRECODECB4F
	#endif
	setT12();
	if (0x02&regA) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB4F
		POSTCODECB4F
	#endif
}
void codeCB50(){
	//BIT   2,B
	#ifdef PRECODECB50
		PRECODECB50
	#endif
	setT8();
	if (0x04&regB) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB50
		POSTCODECB50
	#endif
}
void codeCB51(){
	//BIT   2,C
	#ifdef PRECODECB51
		PRECODECB51
	#endif
	setT8();
	if (0x04&regC) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB51
		POSTCODECB51
	#endif
}
void codeCB52(){
	//BIT   2,D
	#ifdef PRECODECB52
		PRECODECB52
	#endif
	setT8();
	if (0x04&regD) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB52
		POSTCODECB52
	#endif
}
void codeCB53(){
	//BIT   2,E
	#ifdef PRECODECB53
		PRECODECB53
	#endif
	setT8();
	if (0x04&regE) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB53
		POSTCODECB53
	#endif
}
void codeCB54(){
	//BIT   2,H
	#ifdef PRECODECB54
		PRECODECB54
	#endif
	setT8();
	if (0x04&regH) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB54
		POSTCODECB54
	#endif
}
void codeCB55(){
	//BIT   2,L
	#ifdef PRECODECB55
		PRECODECB55
	#endif
	setT8();
	if (0x04&regL) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB55
		POSTCODECB55
	#endif
}
void codeCB56(){
	//BIT   2,(HL)
	#ifdef PRECODECB56
		PRECODECB56
	#endif
	setT12();
	if (0x04&readMemory(regHL)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB56
		POSTCODECB56
	#endif
}
void codeCB57(){
	//BIT   2,A
	#ifdef PRECODECB57
		PRECODECB57
	#endif
	setT8();
	if (0x04&regA) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB57
		POSTCODECB57
	#endif
}
void codeCB58(){
	//BIT   3,B
	#ifdef PRECODECB58
		PRECODECB58
	#endif
	setT8();
	if (0x08&regB) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB58
		POSTCODECB58
	#endif
}
void codeCB59(){
	//BIT   3,C
	#ifdef PRECODECB59
		PRECODECB59
	#endif
	setT8();
	if (0x08&regC) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB59
		POSTCODECB59
	#endif
}
void codeCB5A(){
	//BIT   3,D
	#ifdef PRECODECB5A
		PRECODECB5A
	#endif
	setT8();
	if (0x08&regD) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB5A
		POSTCODECB5A
	#endif
}
void codeCB5B(){
	//BIT   3,E
	#ifdef PRECODECB5B
		PRECODECB5B
	#endif
	setT8();
	if (0x08&regE) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB5B
		POSTCODECB5B
	#endif
}
void codeCB5C(){
	//BIT   3,H
	#ifdef PRECODECB5C
		PRECODECB5C
	#endif
	setT8();
	if (0x08&regH) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB5C
		POSTCODECB5C
	#endif
}
void codeCB5D(){
	//BIT   3,L
	#ifdef PRECODECB5D
		PRECODECB5D
	#endif
	setT8();
	if (0x08&regL) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB5D
		POSTCODECB5D
	#endif
}
void codeCB5E(){
	//BIT   3,(HL)
	#ifdef PRECODECB5E
		PRECODECB5E
	#endif
	setT12();
	if (0x08&readMemory(regHL)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB5E
		POSTCODECB5E
	#endif
}
void codeCB5F(){
	//BIT   3,A
	#ifdef PRECODECB5F
		PRECODECB5F
	#endif
	setT8();
	if (0x08&regA) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB5F
		POSTCODECB5F
	#endif
}
void codeCB60(){
	//BIT   4,B
	#ifdef PRECODECB60
		PRECODECB60
	#endif
	setT8();
	if (0x10&regB) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB60
		POSTCODECB60
	#endif
}
void codeCB61(){
	//BIT   4,C
	#ifdef PRECODECB61
		PRECODECB61
	#endif
	setT8();
	if (0x10&regC) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB61
		POSTCODECB61
	#endif
}
void codeCB62(){
	//BIT   4,D
	#ifdef PRECODECB62
		PRECODECB62
	#endif
	setT8();
	if (0x10&regD) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB62
		POSTCODECB62
	#endif
}
void codeCB63(){
	//BIT   4,E
	#ifdef PRECODECB63
		PRECODECB63
	#endif
	setT8();
	if (0x10&regE) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB63
		POSTCODECB63
	#endif
}
void codeCB64(){
	//BIT   4,H
	#ifdef PRECODECB64
		PRECODECB64
	#endif
	setT8();
	if (0x10&regH) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB64
		POSTCODECB64
	#endif
}
void codeCB65(){
	//BIT   4,L
	#ifdef PRECODECB65
		PRECODECB65
	#endif
	setT8();
	if (0x10&regL) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB65
		POSTCODECB65
	#endif
}
void codeCB66(){
	//BIT   4,(HL)
	#ifdef PRECODECB66
		PRECODECB66
	#endif
	setT12();
	if (0x10&readMemory(regHL)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB66
		POSTCODECB66
	#endif
}
void codeCB67(){
	//BIT   4,A
	#ifdef PRECODECB67
		PRECODECB67
	#endif
	setT8();
	if (0x10&regA) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB67
		POSTCODECB67
	#endif
}
void codeCB68(){
	//BIT   5,B
	#ifdef PRECODECB68
		PRECODECB68
	#endif
	setT8();
	if (0x20&regB) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB68
		POSTCODECB68
	#endif
}
void codeCB69(){
	//BIT   5,C
	#ifdef PRECODECB69
		PRECODECB69
	#endif
	setT8();
	if (0x20&regC) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB69
		POSTCODECB69
	#endif
}
void codeCB6A(){
	//BIT   5,D
	#ifdef PRECODECB6A
		PRECODECB6A
	#endif
	setT8();
	if (0x20&regD) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB6A
		POSTCODECB6A
	#endif
}
void codeCB6B(){
	//BIT   5,E
	#ifdef PRECODECB6B
		PRECODECB6B
	#endif
	setT8();
	if (0x20&regE) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB6B
		POSTCODECB6B
	#endif
}
void codeCB6C(){
	//BIT   5,H
	#ifdef PRECODECB6C
		PRECODECB6C
	#endif
	setT8();
	if (0x20&regH) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB6C
		POSTCODECB6C
	#endif
}
void codeCB6D(){
	//BIT   5,L
	#ifdef PRECODECB6D
		PRECODECB6D
	#endif
	setT8();
	if (0x20&regL) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB6D
		POSTCODECB6D
	#endif
}
void codeCB6E(){
	//BIT   5,(HL)
	#ifdef PRECODECB6E
		PRECODECB6E
	#endif
	setT12();
	if (0x20&readMemory(regHL)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB6E
		POSTCODECB6E
	#endif
}
void codeCB6F(){
	//BIT   5,A
	#ifdef PRECODECB6F
		PRECODECB6F
	#endif
	setT8();
	if (0x20&regA) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB6F
		POSTCODECB6F
	#endif
}
void codeCB70(){
	//BIT   6,B
	#ifdef PRECODECB70
		PRECODECB70
	#endif
	setT8();
	if (0x40&regB) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB70
		POSTCODECB70
	#endif
}
void codeCB71(){
	//BIT   6,C
	#ifdef PRECODECB71
		PRECODECB71
	#endif
	setT8();
	if (0x40&regC) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB71
		POSTCODECB71
	#endif
}
void codeCB72(){
	//BIT   6,D
	#ifdef PRECODECB72
		PRECODECB72
	#endif
	setT8();
	if (0x40&regD) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB72
		POSTCODECB72
	#endif
}
void codeCB73(){
	//BIT   6,E
	#ifdef PRECODECB73
		PRECODECB73
	#endif
	setT8();
	if (0x40&regE) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB73
		POSTCODECB73
	#endif
}
void codeCB74(){
	//BIT   6,H
	#ifdef PRECODECB74
		PRECODECB74
	#endif
	setT8();
	if (0x40&regH) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB74
		POSTCODECB74
	#endif
}
void codeCB75(){
	//BIT   6,L
	#ifdef PRECODECB75
		PRECODECB75
	#endif
	setT8();
	if (0x40&regL) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB75
		POSTCODECB75
	#endif
}
void codeCB76(){
	//BIT   6,(HL)
	#ifdef PRECODECB76
		PRECODECB76
	#endif
	setT12();
	if (0x40&readMemory(regHL)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB76
		POSTCODECB76
	#endif
}
void codeCB77(){
	//BIT   6,A
	#ifdef PRECODECB77
		PRECODECB77
	#endif
	setT8();
	if (0x40&regA) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB77
		POSTCODECB77
	#endif
}
void codeCB78(){
	//BIT   7,B
	#ifdef PRECODECB78
		PRECODECB78
	#endif
	setT8();
	if (0x80&regB) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB78
		POSTCODECB78
	#endif
}
void codeCB79(){
	//BIT   7,C
	#ifdef PRECODECB79
		PRECODECB79
	#endif
	setT8();
	if (0x80&regC) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB79
		POSTCODECB79
	#endif
}
void codeCB7A(){
	//BIT   7,D
	#ifdef PRECODECB7A
		PRECODECB7A
	#endif
	setT8();
	if (0x80&regD) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB7A
		POSTCODECB7A
	#endif
}
void codeCB7B(){
	//BIT   7,E
	#ifdef PRECODECB7B
		PRECODECB7B
	#endif
	setT8();
	if (0x80&regE) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB7B
		POSTCODECB7B
	#endif
}
void codeCB7C(){
	//BIT   7,H
	#ifdef PRECODECB7C
		PRECODECB7C
	#endif
	setT8();
	if (0x80&regH) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB7C
		POSTCODECB7C
	#endif
}
void codeCB7D(){
	//BIT   7,L
	#ifdef PRECODECB7D
		PRECODECB7D
	#endif
	setT8();
	if (0x80&regL) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB7D
		POSTCODECB7D
	#endif
}
void codeCB7E(){
	//BIT   7,(HL)
	#ifdef PRECODECB7E
		PRECODECB7E
	#endif
	setT12();
	if (0x80&readMemory(regHL)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB7E
		POSTCODECB7E
	#endif
}
void codeCB7F(){
	//BIT   7,A
	#ifdef PRECODECB7F
		PRECODECB7F
	#endif
	setT8();
	if (0x80&regA) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODECB7F
		POSTCODECB7F
	#endif
}
void codeCB80(){
	//RES   0,B
	#ifdef PRECODECB80
		PRECODECB80
	#endif
	setT8();
	loadB(0xFE&regB);
	#ifdef POSTCODECB80
		POSTCODECB80
	#endif
}
void codeCB81(){
	//RES   0,C
	#ifdef PRECODECB81
		PRECODECB81
	#endif
	setT8();
	loadC(0xFE&regC);
	#ifdef POSTCODECB81
		POSTCODECB81
	#endif
}
void codeCB82(){
	//RES   0,D
	#ifdef PRECODECB82
		PRECODECB82
	#endif
	setT8();
	loadD(0xFE&regD);
	#ifdef POSTCODECB82
		POSTCODECB82
	#endif
}
void codeCB83(){
	//RES   0,E
	#ifdef PRECODECB83
		PRECODECB83
	#endif
	setT8();
	loadE(0xFE&regE);
	#ifdef POSTCODECB83
		POSTCODECB83
	#endif
}
void codeCB84(){
	//RES   0,H
	#ifdef PRECODECB84
		PRECODECB84
	#endif
	setT8();
	loadH(0xFE&regH);
	#ifdef POSTCODECB84
		POSTCODECB84
	#endif
}
void codeCB85(){
	//RES   0,L
	#ifdef PRECODECB85
		PRECODECB85
	#endif
	setT8();
	loadL(0xFE&regL);
	#ifdef POSTCODECB85
		POSTCODECB85
	#endif
}
void codeCB86(){
	//RES   0,(HL)
	#ifdef PRECODECB86
		PRECODECB86
	#endif
	setT15();
	writeMemory(regHL,0xFE&readMemory(regHL));
	#ifdef POSTCODECB86
		POSTCODECB86
	#endif
}
void codeCB87(){
	//RES   0,A
	#ifdef PRECODECB87
		PRECODECB87
	#endif
	setT8();
	loadA(0xFE&regA);
	#ifdef POSTCODECB87
		POSTCODECB87
	#endif
}
void codeCB88(){
	//RES   1,B
	#ifdef PRECODECB88
		PRECODECB88
	#endif
	setT8();
	loadB(0xFD&regB);
	#ifdef POSTCODECB88
		POSTCODECB88
	#endif
}
void codeCB89(){
	//RES   1,C
	#ifdef PRECODECB89
		PRECODECB89
	#endif
	setT8();
	loadC(0xFD&regC);
	#ifdef POSTCODECB89
		POSTCODECB89
	#endif
}
void codeCB8A(){
	//RES   1,D
	#ifdef PRECODECB8A
		PRECODECB8A
	#endif
	setT8();
	loadD(0xFD&regD);
	#ifdef POSTCODECB8A
		POSTCODECB8A
	#endif
}
void codeCB8B(){
	//RES   1,E
	#ifdef PRECODECB8B
		PRECODECB8B
	#endif
	setT8();
	loadE(0xFD&regE);
	#ifdef POSTCODECB8B
		POSTCODECB8B
	#endif
}
void codeCB8C(){
	//RES   1,H
	#ifdef PRECODECB8C
		PRECODECB8C
	#endif
	setT8();
	loadH(0xFD&regH);
	#ifdef POSTCODECB8C
		POSTCODECB8C
	#endif
}
void codeCB8D(){
	//RES   1,L
	#ifdef PRECODECB8D
		PRECODECB8D
	#endif
	setT8();
	loadL(0xFD&regL);
	#ifdef POSTCODECB8D
		POSTCODECB8D
	#endif
}
void codeCB8E(){
	//RES   1,(HL)
	#ifdef PRECODECB8E
		PRECODECB8E
	#endif
	setT15();
	writeMemory(regHL,0xFD&readMemory(regHL));
	#ifdef POSTCODECB8E
		POSTCODECB8E
	#endif
}
void codeCB8F(){
	//RES   1,A
	#ifdef PRECODECB8F
		PRECODECB8F
	#endif
	setT8();
	loadA(0xFD&regA);
	#ifdef POSTCODECB8F
		POSTCODECB8F
	#endif
}
void codeCB90(){
	//RES   2,B
	#ifdef PRECODECB90
		PRECODECB90
	#endif
	setT8();
	loadB(0xFB&regB);
	#ifdef POSTCODECB90
		POSTCODECB90
	#endif
}
void codeCB91(){
	//RES   2,C
	#ifdef PRECODECB91
		PRECODECB91
	#endif
	setT8();
	loadC(0xFB&regC);
	#ifdef POSTCODECB91
		POSTCODECB91
	#endif
}
void codeCB92(){
	//RES   2,D
	#ifdef PRECODECB92
		PRECODECB92
	#endif
	setT8();
	loadD(0xFB&regD);
	#ifdef POSTCODECB92
		POSTCODECB92
	#endif
}
void codeCB93(){
	//RES   2,E
	#ifdef PRECODECB93
		PRECODECB93
	#endif
	setT8();
	loadE(0xFB&regE);
	#ifdef POSTCODECB93
		POSTCODECB93
	#endif
}
void codeCB94(){
	//RES   2,H
	#ifdef PRECODECB94
		PRECODECB94
	#endif
	setT8();
	loadH(0xFB&regH);
	#ifdef POSTCODECB94
		POSTCODECB94
	#endif
}
void codeCB95(){
	//RES   2,L
	#ifdef PRECODECB95
		PRECODECB95
	#endif
	setT8();
	loadL(0xFB&regL);
	#ifdef POSTCODECB95
		POSTCODECB95
	#endif
}
void codeCB96(){
	//RES   2,(HL)
	#ifdef PRECODECB96
		PRECODECB96
	#endif
	setT15();
	writeMemory(regHL,0xFB&readMemory(regHL));
	#ifdef POSTCODECB96
		POSTCODECB96
	#endif
}
void codeCB97(){
	//RES   2,A
	#ifdef PRECODECB97
		PRECODECB97
	#endif
	setT8();
	loadA(0xFB&regA);
	#ifdef POSTCODECB97
		POSTCODECB97
	#endif
}
void codeCB98(){
	//RES   3,B
	#ifdef PRECODECB98
		PRECODECB98
	#endif
	setT8();
	loadB(0xF7&regB);
	#ifdef POSTCODECB98
		POSTCODECB98
	#endif
}
void codeCB99(){
	//RES   3,C
	#ifdef PRECODECB99
		PRECODECB99
	#endif
	setT8();
	loadC(0xF7&regC);
	#ifdef POSTCODECB99
		POSTCODECB99
	#endif
}
void codeCB9A(){
	//RES   3,D
	#ifdef PRECODECB9A
		PRECODECB9A
	#endif
	setT8();
	loadD(0xF7&regD);
	#ifdef POSTCODECB9A
		POSTCODECB9A
	#endif
}
void codeCB9B(){
	//RES   3,E
	#ifdef PRECODECB9B
		PRECODECB9B
	#endif
	setT8();
	loadE(0xF7&regE);
	#ifdef POSTCODECB9B
		POSTCODECB9B
	#endif
}
void codeCB9C(){
	//RES   3,H
	#ifdef PRECODECB9C
		PRECODECB9C
	#endif
	setT8();
	loadH(0xF7&regH);
	#ifdef POSTCODECB9C
		POSTCODECB9C
	#endif
}
void codeCB9D(){
	//RES   3,L
	#ifdef PRECODECB9D
		PRECODECB9D
	#endif
	setT8();
	loadL(0xF7&regL);
	#ifdef POSTCODECB9D
		POSTCODECB9D
	#endif
}
void codeCB9E(){
	//RES   3,(HL)
	#ifdef PRECODECB9E
		PRECODECB9E
	#endif
	setT15();
	writeMemory(regHL,0xF7&readMemory(regHL));
	#ifdef POSTCODECB9E
		POSTCODECB9E
	#endif
}
void codeCB9F(){
	//RES   3,A
	#ifdef PRECODECB9F
		PRECODECB9F
	#endif
	setT8();
	loadA(0xF7&regA);
	#ifdef POSTCODECB9F
		POSTCODECB9F
	#endif
}
void codeCBA0(){
	//RES   4,B
	#ifdef PRECODECBA0
		PRECODECBA0
	#endif
	setT8();
	loadB(0xEF&regB);
	#ifdef POSTCODECBA0
		POSTCODECBA0
	#endif
}
void codeCBA1(){
	//RES   4,C
	#ifdef PRECODECBA1
		PRECODECBA1
	#endif
	setT8();
	loadC(0xEF&regC);
	#ifdef POSTCODECBA1
		POSTCODECBA1
	#endif
}
void codeCBA2(){
	//RES   4,D
	#ifdef PRECODECBA2
		PRECODECBA2
	#endif
	setT8();
	loadD(0xEF&regD);
	#ifdef POSTCODECBA2
		POSTCODECBA2
	#endif
}
void codeCBA3(){
	//RES   4,E
	#ifdef PRECODECBA3
		PRECODECBA3
	#endif
	setT8();
	loadE(0xEF&regE);
	#ifdef POSTCODECBA3
		POSTCODECBA3
	#endif
}
void codeCBA4(){
	//RES   4,H
	#ifdef PRECODECBA4
		PRECODECBA4
	#endif
	setT8();
	loadH(0xEF&regH);
	#ifdef POSTCODECBA4
		POSTCODECBA4
	#endif
}
void codeCBA5(){
	//RES   4,L
	#ifdef PRECODECBA5
		PRECODECBA5
	#endif
	setT8();
	loadL(0xEF&regL);
	#ifdef POSTCODECBA5
		POSTCODECBA5
	#endif
}
void codeCBA6(){
	//RES   4,(HL)
	#ifdef PRECODECBA6
		PRECODECBA6
	#endif
	setT15();
	writeMemory(regHL,0xEF&readMemory(regHL));
	#ifdef POSTCODECBA6
		POSTCODECBA6
	#endif
}
void codeCBA7(){
	//RES   4,A
	#ifdef PRECODECBA7
		PRECODECBA7
	#endif
	setT8();
	loadA(0xEF&regA);
	#ifdef POSTCODECBA7
		POSTCODECBA7
	#endif
}
void codeCBA8(){
	//RES   5,B
	#ifdef PRECODECBA8
		PRECODECBA8
	#endif
	setT8();
	loadB(0xDF&regB);
	#ifdef POSTCODECBA8
		POSTCODECBA8
	#endif
}
void codeCBA9(){
	//RES   5,C
	#ifdef PRECODECBA9
		PRECODECBA9
	#endif
	setT8();
	loadC(0xDF&regC);
	#ifdef POSTCODECBA9
		POSTCODECBA9
	#endif
}
void codeCBAA(){
	//RES   5,D
	#ifdef PRECODECBAA
		PRECODECBAA
	#endif
	setT8();
	loadD(0xDF&regD);
	#ifdef POSTCODECBAA
		POSTCODECBAA
	#endif
}
void codeCBAB(){
	//RES   5,E
	#ifdef PRECODECBAB
		PRECODECBAB
	#endif
	setT8();
	loadE(0xDF&regE);
	#ifdef POSTCODECBAB
		POSTCODECBAB
	#endif
}
void codeCBAC(){
	//RES   5,H
	#ifdef PRECODECBAC
		PRECODECBAC
	#endif
	setT8();
	loadH(0xDF&regH);
	#ifdef POSTCODECBAC
		POSTCODECBAC
	#endif
}
void codeCBAD(){
	//RES   5,L
	#ifdef PRECODECBAD
		PRECODECBAD
	#endif
	setT8();
	loadL(0xDF&regL);
	#ifdef POSTCODECBAD
		POSTCODECBAD
	#endif
}
void codeCBAE(){
	//RES   5,(HL)
	#ifdef PRECODECBAE
		PRECODECBAE
	#endif
	setT15();
	writeMemory(regHL,0xDF&readMemory(regHL));
	#ifdef POSTCODECBAE
		POSTCODECBAE
	#endif
}
void codeCBAF(){
	//RES   5,A
	#ifdef PRECODECBAF
		PRECODECBAF
	#endif
	setT8();
	loadA(0xDF&regA);
	#ifdef POSTCODECBAF
		POSTCODECBAF
	#endif
}
void codeCBB0(){
	//RES   6,B
	#ifdef PRECODECBB0
		PRECODECBB0
	#endif
	setT8();
	loadB(0xBF&regB);
	#ifdef POSTCODECBB0
		POSTCODECBB0
	#endif
}
void codeCBB1(){
	//RES   6,C
	#ifdef PRECODECBB1
		PRECODECBB1
	#endif
	setT8();
	loadC(0xBF&regC);
	#ifdef POSTCODECBB1
		POSTCODECBB1
	#endif
}
void codeCBB2(){
	//RES   6,D
	#ifdef PRECODECBB2
		PRECODECBB2
	#endif
	setT8();
	loadD(0xBF&regD);
	#ifdef POSTCODECBB2
		POSTCODECBB2
	#endif
}
void codeCBB3(){
	//RES   6,E
	#ifdef PRECODECBB3
		PRECODECBB3
	#endif
	setT8();
	loadE(0xBF&regE);
	#ifdef POSTCODECBB3
		POSTCODECBB3
	#endif
}
void codeCBB4(){
	//RES   6,H
	#ifdef PRECODECBB4
		PRECODECBB4
	#endif
	setT8();
	loadH(0xBF&regH);
	#ifdef POSTCODECBB4
		POSTCODECBB4
	#endif
}
void codeCBB5(){
	//RES   6,L
	#ifdef PRECODECBB5
		PRECODECBB5
	#endif
	setT8();
	loadL(0xBF&regL);
	#ifdef POSTCODECBB5
		POSTCODECBB5
	#endif
}
void codeCBB6(){
	//RES   6,(HL)
	#ifdef PRECODECBB6
		PRECODECBB6
	#endif
	setT15();
	writeMemory(regHL,0xBF&readMemory(regHL));
	#ifdef POSTCODECBB6
		POSTCODECBB6
	#endif
}
void codeCBB7(){
	//RES   6,A
	#ifdef PRECODECBB7
		PRECODECBB7
	#endif
	setT8();
	loadA(0xBF&regA);
	#ifdef POSTCODECBB7
		POSTCODECBB7
	#endif
}
void codeCBB8(){
	//RES   7,B
	#ifdef PRECODECBB8
		PRECODECBB8
	#endif
	setT8();
	loadB(0x7F&regB);
	#ifdef POSTCODECBB8
		POSTCODECBB8
	#endif
}
void codeCBB9(){
	//RES   7,C
	#ifdef PRECODECBB9
		PRECODECBB9
	#endif
	setT8();
	loadC(0x7F&regC);
	#ifdef POSTCODECBB9
		POSTCODECBB9
	#endif
}
void codeCBBA(){
	//RES   7,D
	#ifdef PRECODECBBA
		PRECODECBBA
	#endif
	setT8();
	loadD(0x7F&regD);
	#ifdef POSTCODECBBA
		POSTCODECBBA
	#endif
}
void codeCBBB(){
	//RES   7,E
	#ifdef PRECODECBBB
		PRECODECBBB
	#endif
	setT8();
	loadE(0x7F&regE);
	#ifdef POSTCODECBBB
		POSTCODECBBB
	#endif
}
void codeCBBC(){
	//RES   7,H
	#ifdef PRECODECBBC
		PRECODECBBC
	#endif
	setT8();
	loadH(0x7F&regH);
	#ifdef POSTCODECBBC
		POSTCODECBBC
	#endif
}
void codeCBBD(){
	//RES   7,L
	#ifdef PRECODECBBD
		PRECODECBBD
	#endif
	setT8();
	loadL(0x7F&regL);
	#ifdef POSTCODECBBD
		POSTCODECBBD
	#endif
}
void codeCBBE(){
	//RES   7,(HL)
	#ifdef PRECODECBBE
		PRECODECBBE
	#endif
	setT15();
	writeMemory(regHL,0x7F&readMemory(regHL));
	#ifdef POSTCODECBBE
		POSTCODECBBE
	#endif
}
void codeCBBF(){
	//RES   7,A
	#ifdef PRECODECBBF
		PRECODECBBF
	#endif
	setT8();
	loadA(0x7F&regA);
	#ifdef POSTCODECBBF
		POSTCODECBBF
	#endif
}
void codeCBC0(){
	//SET   0,B
	#ifdef PRECODECBC0
		PRECODECBC0
	#endif
	setT8();
	loadB(0x01|regB);
	#ifdef POSTCODECBC0
		POSTCODECBC0
	#endif
}
void codeCBC1(){
	//SET   0,C
	#ifdef PRECODECBC1
		PRECODECBC1
	#endif
	setT8();
	loadC(0x01|regC);
	#ifdef POSTCODECBC1
		POSTCODECBC1
	#endif
}
void codeCBC2(){
	//SET   0,D
	#ifdef PRECODECBC2
		PRECODECBC2
	#endif
	setT8();
	loadD(0x01|regD);
	#ifdef POSTCODECBC2
		POSTCODECBC2
	#endif
}
void codeCBC3(){
	//SET   0,E
	#ifdef PRECODECBC3
		PRECODECBC3
	#endif
	setT8();
	loadE(0x01|regE);
	#ifdef POSTCODECBC3
		POSTCODECBC3
	#endif
}
void codeCBC4(){
	//SET   0,H
	#ifdef PRECODECBC4
		PRECODECBC4
	#endif
	setT8();
	loadH(0x01|regH);
	#ifdef POSTCODECBC4
		POSTCODECBC4
	#endif
}
void codeCBC5(){
	//SET   0,L
	#ifdef PRECODECBC5
		PRECODECBC5
	#endif
	setT8();
	loadL(0x01|regL);
	#ifdef POSTCODECBC5
		POSTCODECBC5
	#endif
}
void codeCBC6(){
	//SET   0,(HL)
	#ifdef PRECODECBC6
		PRECODECBC6
	#endif
	setT15();
	writeMemory(regHL,0x01|readMemory(regHL));
	#ifdef POSTCODECBC6
		POSTCODECBC6
	#endif
}
void codeCBC7(){
	//SET   0,A
	#ifdef PRECODECBC7
		PRECODECBC7
	#endif
	setT8();
	loadA(0x01|regA);
	#ifdef POSTCODECBC7
		POSTCODECBC7
	#endif
}
void codeCBC8(){
	//SET   1,B
	#ifdef PRECODECBC8
		PRECODECBC8
	#endif
	setT8();
	loadB(0x02|regB);
	#ifdef POSTCODECBC8
		POSTCODECBC8
	#endif
}
void codeCBC9(){
	//SET   1,C
	#ifdef PRECODECBC9
		PRECODECBC9
	#endif
	setT8();
	loadC(0x02|regC);
	#ifdef POSTCODECBC9
		POSTCODECBC9
	#endif
}
void codeCBCA(){
	//SET   1,D
	#ifdef PRECODECBCA
		PRECODECBCA
	#endif
	setT8();
	loadD(0x02|regD);
	#ifdef POSTCODECBCA
		POSTCODECBCA
	#endif
}
void codeCBCB(){
	//SET   1,E
	#ifdef PRECODECBCB
		PRECODECBCB
	#endif
	setT8();
	loadE(0x02|regE);
	#ifdef POSTCODECBCB
		POSTCODECBCB
	#endif
}
void codeCBCC(){
	//SET   1,H
	#ifdef PRECODECBCC
		PRECODECBCC
	#endif
	setT8();
	loadH(0x02|regH);
	#ifdef POSTCODECBCC
		POSTCODECBCC
	#endif
}
void codeCBCD(){
	//SET   1,L
	#ifdef PRECODECBCD
		PRECODECBCD
	#endif
	setT8();
	loadL(0x02|regL);
	#ifdef POSTCODECBCD
		POSTCODECBCD
	#endif
}
void codeCBCE(){
	//SET   1,(HL)
	#ifdef PRECODECBCE
		PRECODECBCE
	#endif
	setT15();
	writeMemory(regHL,0x02|readMemory(regHL));
	#ifdef POSTCODECBCE
		POSTCODECBCE
	#endif
}
void codeCBCF(){
	//SET   1,A
	#ifdef PRECODECBCF
		PRECODECBCF
	#endif
	setT8();
	loadA(0x02|regA);
	#ifdef POSTCODECBCF
		POSTCODECBCF
	#endif
}
void codeCBD0(){
	//SET   2,B
	#ifdef PRECODECBD0
		PRECODECBD0
	#endif
	setT8();
	loadB(0x04|regB);
	#ifdef POSTCODECBD0
		POSTCODECBD0
	#endif
}
void codeCBD1(){
	//SET   2,C
	#ifdef PRECODECBD1
		PRECODECBD1
	#endif
	setT8();
	loadC(0x04|regC);
	#ifdef POSTCODECBD1
		POSTCODECBD1
	#endif
}
void codeCBD2(){
	//SET   2,D
	#ifdef PRECODECBD2
		PRECODECBD2
	#endif
	setT8();
	loadD(0x04|regD);
	#ifdef POSTCODECBD2
		POSTCODECBD2
	#endif
}
void codeCBD3(){
	//SET   2,E
	#ifdef PRECODECBD3
		PRECODECBD3
	#endif
	setT8();
	loadE(0x04|regE);
	#ifdef POSTCODECBD3
		POSTCODECBD3
	#endif
}
void codeCBD4(){
	//SET   2,H
	#ifdef PRECODECBD4
		PRECODECBD4
	#endif
	setT8();
	loadH(0x04|regH);
	#ifdef POSTCODECBD4
		POSTCODECBD4
	#endif
}
void codeCBD5(){
	//SET   2,L
	#ifdef PRECODECBD5
		PRECODECBD5
	#endif
	setT8();
	loadL(0x04|regL);
	#ifdef POSTCODECBD5
		POSTCODECBD5
	#endif
}
void codeCBD6(){
	//SET   2,(HL)
	#ifdef PRECODECBD6
		PRECODECBD6
	#endif
	setT15();
	writeMemory(regHL,0x04|readMemory(regHL));
	#ifdef POSTCODECBD6
		POSTCODECBD6
	#endif
}
void codeCBD7(){
	//SET   2,A
	#ifdef PRECODECBD7
		PRECODECBD7
	#endif
	setT8();
	loadA(0x04|regA);
	#ifdef POSTCODECBD7
		POSTCODECBD7
	#endif
}
void codeCBD8(){
	//SET   3,B
	#ifdef PRECODECBD8
		PRECODECBD8
	#endif
	setT8();
	loadB(0x08|regB);
	#ifdef POSTCODECBD8
		POSTCODECBD8
	#endif
}
void codeCBD9(){
	//SET   3,C
	#ifdef PRECODECBD9
		PRECODECBD9
	#endif
	setT8();
	loadC(0x08|regC);
	#ifdef POSTCODECBD9
		POSTCODECBD9
	#endif
}
void codeCBDA(){
	//SET   3,D
	#ifdef PRECODECBDA
		PRECODECBDA
	#endif
	setT8();
	loadD(0x08|regD);
	#ifdef POSTCODECBDA
		POSTCODECBDA
	#endif
}
void codeCBDB(){
	//SET   3,E
	#ifdef PRECODECBDB
		PRECODECBDB
	#endif
	setT8();
	loadE(0x08|regE);
	#ifdef POSTCODECBDB
		POSTCODECBDB
	#endif
}
void codeCBDC(){
	//SET   3,H
	#ifdef PRECODECBDC
		PRECODECBDC
	#endif
	setT8();
	loadH(0x08|regH);
	#ifdef POSTCODECBDC
		POSTCODECBDC
	#endif
}
void codeCBDD(){
	//SET   3,L
	#ifdef PRECODECBDD
		PRECODECBDD
	#endif
	setT8();
	loadL(0x08|regL);
	#ifdef POSTCODECBDD
		POSTCODECBDD
	#endif
}
void codeCBDE(){
	//SET   3,(HL)
	#ifdef PRECODECBDE
		PRECODECBDE
	#endif
	setT15();
	writeMemory(regHL,0x08|readMemory(regHL));
	#ifdef POSTCODECBDE
		POSTCODECBDE
	#endif
}
void codeCBDF(){
	//SET   3,A
	#ifdef PRECODECBDF
		PRECODECBDF
	#endif
	setT8();
	loadA(0x08|regA);
	#ifdef POSTCODECBDF
		POSTCODECBDF
	#endif
}
void codeCBE0(){
	//SET   4,B
	#ifdef PRECODECBE0
		PRECODECBE0
	#endif
	setT8();
	loadB(0x10|regB);
	#ifdef POSTCODECBE0
		POSTCODECBE0
	#endif
}
void codeCBE1(){
	//SET   4,C
	#ifdef PRECODECBE1
		PRECODECBE1
	#endif
	setT8();
	loadC(0x10|regC);
	#ifdef POSTCODECBE1
		POSTCODECBE1
	#endif
}
void codeCBE2(){
	//SET   4,D
	#ifdef PRECODECBE2
		PRECODECBE2
	#endif
	setT8();
	loadD(0x10|regD);
	#ifdef POSTCODECBE2
		POSTCODECBE2
	#endif
}
void codeCBE3(){
	//SET   4,E
	#ifdef PRECODECBE3
		PRECODECBE3
	#endif
	setT8();
	loadE(0x10|regE);
	#ifdef POSTCODECBE3
		POSTCODECBE3
	#endif
}
void codeCBE4(){
	//SET   4,H
	#ifdef PRECODECBE4
		PRECODECBE4
	#endif
	setT8();
	loadH(0x10|regH);
	#ifdef POSTCODECBE4
		POSTCODECBE4
	#endif
}
void codeCBE5(){
	//SET   4,L
	#ifdef PRECODECBE5
		PRECODECBE5
	#endif
	setT8();
	loadL(0x10|regL);
	#ifdef POSTCODECBE5
		POSTCODECBE5
	#endif
}
void codeCBE6(){
	//SET   4,(HL)
	#ifdef PRECODECBE6
		PRECODECBE6
	#endif
	setT15();
	writeMemory(regHL,0x10|readMemory(regHL));
	#ifdef POSTCODECBE6
		POSTCODECBE6
	#endif
}
void codeCBE7(){
	//SET   4,A
	#ifdef PRECODECBE7
		PRECODECBE7
	#endif
	setT8();
	loadA(0x10|regA);
	#ifdef POSTCODECBE7
		POSTCODECBE7
	#endif
}
void codeCBE8(){
	//SET   5,B
	#ifdef PRECODECBE8
		PRECODECBE8
	#endif
	setT8();
	loadB(0x20|regB);
	#ifdef POSTCODECBE8
		POSTCODECBE8
	#endif
}
void codeCBE9(){
	//SET   5,C
	#ifdef PRECODECBE9
		PRECODECBE9
	#endif
	setT8();
	loadC(0x20|regC);
	#ifdef POSTCODECBE9
		POSTCODECBE9
	#endif
}
void codeCBEA(){
	//SET   5,D
	#ifdef PRECODECBEA
		PRECODECBEA
	#endif
	setT8();
	loadD(0x20|regD);
	#ifdef POSTCODECBEA
		POSTCODECBEA
	#endif
}
void codeCBEB(){
	//SET   5,E
	#ifdef PRECODECBEB
		PRECODECBEB
	#endif
	setT8();
	loadE(0x20|regE);
	#ifdef POSTCODECBEB
		POSTCODECBEB
	#endif
}
void codeCBEC(){
	//SET   5,H
	#ifdef PRECODECBEC
		PRECODECBEC
	#endif
	setT8();
	loadH(0x20|regH);
	#ifdef POSTCODECBEC
		POSTCODECBEC
	#endif
}
void codeCBED(){
	//SET   5,L
	#ifdef PRECODECBED
		PRECODECBED
	#endif
	setT8();
	loadL(0x20|regL);
	#ifdef POSTCODECBED
		POSTCODECBED
	#endif
}
void codeCBEE(){
	//SET   5,(HL)
	#ifdef PRECODECBEE
		PRECODECBEE
	#endif
	setT15();
	writeMemory(regHL,0x20|readMemory(regHL));
	#ifdef POSTCODECBEE
		POSTCODECBEE
	#endif
}
void codeCBEF(){
	//SET   5,A
	#ifdef PRECODECBEF
		PRECODECBEF
	#endif
	setT8();
	loadA(0x20|regA);
	#ifdef POSTCODECBEF
		POSTCODECBEF
	#endif
}
void codeCBF0(){
	//SET   6,B
	#ifdef PRECODECBF0
		PRECODECBF0
	#endif
	setT8();
	loadB(0x40|regB);
	#ifdef POSTCODECBF0
		POSTCODECBF0
	#endif
}
void codeCBF1(){
	//SET   6,C
	#ifdef PRECODECBF1
		PRECODECBF1
	#endif
	setT8();
	loadC(0x40|regC);
	#ifdef POSTCODECBF1
		POSTCODECBF1
	#endif
}
void codeCBF2(){
	//SET   6,D
	#ifdef PRECODECBF2
		PRECODECBF2
	#endif
	setT8();
	loadD(0x40|regD);
	#ifdef POSTCODECBF2
		POSTCODECBF2
	#endif
}
void codeCBF3(){
	//SET   6,E
	#ifdef PRECODECBF3
		PRECODECBF3
	#endif
	setT8();
	loadE(0x40|regE);
	#ifdef POSTCODECBF3
		POSTCODECBF3
	#endif
}
void codeCBF4(){
	//SET   6,H
	#ifdef PRECODECBF4
		PRECODECBF4
	#endif
	setT8();
	loadH(0x40|regH);
	#ifdef POSTCODECBF4
		POSTCODECBF4
	#endif
}
void codeCBF5(){
	//SET   6,L
	#ifdef PRECODECBF5
		PRECODECBF5
	#endif
	setT8();
	loadL(0x40|regL);
	#ifdef POSTCODECBF5
		POSTCODECBF5
	#endif
}
void codeCBF6(){
	//SET   6,(HL)
	#ifdef PRECODECBF6
		PRECODECBF6
	#endif
	setT15();
	writeMemory(regHL,0x40|readMemory(regHL));
	#ifdef POSTCODECBF6
		POSTCODECBF6
	#endif
}
void codeCBF7(){
	//SET   6,A
	#ifdef PRECODECBF7
		PRECODECBF7
	#endif
	setT8();
	loadA(0x40|regA);
	#ifdef POSTCODECBF7
		POSTCODECBF7
	#endif
}
void codeCBF8(){
	//SET   7,B
	#ifdef PRECODECBF8
		PRECODECBF8
	#endif
	setT8();
	loadB(0x80|regB);
	#ifdef POSTCODECBF8
		POSTCODECBF8
	#endif
}
void codeCBF9(){
	//SET   7,C
	#ifdef PRECODECBF9
		PRECODECBF9
	#endif
	setT8();
	loadC(0x80|regC);
	#ifdef POSTCODECBF9
		POSTCODECBF9
	#endif
}
void codeCBFA(){
	//SET   7,D
	#ifdef PRECODECBFA
		PRECODECBFA
	#endif
	setT8();
	loadD(0x80|regD);
	#ifdef POSTCODECBFA
		POSTCODECBFA
	#endif
}
void codeCBFB(){
	//SET   7,E
	#ifdef PRECODECBFB
		PRECODECBFB
	#endif
	setT8();
	loadE(0x80|regE);
	#ifdef POSTCODECBFB
		POSTCODECBFB
	#endif
}
void codeCBFC(){
	//SET   7,H
	#ifdef PRECODECBFC
		PRECODECBFC
	#endif
	setT8();
	loadH(0x80|regH);
	#ifdef POSTCODECBFC
		POSTCODECBFC
	#endif
}
void codeCBFD(){
	//SET   7,L
	#ifdef PRECODECBFD
		PRECODECBFD
	#endif
	setT8();
	loadL(0x80|regL);
	#ifdef POSTCODECBFD
		POSTCODECBFD
	#endif
}
void codeCBFE(){
	//SET   7,(HL)
	#ifdef PRECODECBFE
		PRECODECBFE
	#endif
	setT15();
	writeMemory(regHL,0x80|readMemory(regHL));
	#ifdef POSTCODECBFE
		POSTCODECBFE
	#endif
}
void codeCBFF(){
	//SET   7,A
	#ifdef PRECODECBFF
		PRECODECBFF
	#endif
	setT8();
	loadA(0x80|regA);
	#ifdef POSTCODECBFF
		POSTCODECBFF
	#endif
}
void codeDD09(){
	UINT16 i16;
	UINT32 i32;
	//ADD   IX,BC
	#ifdef PRECODEDD09
		PRECODEDD09
	#endif
	setT15();
	i32=regIX+regBC;
	i16=(regIX&0x0FFF)+(regBC&0x0FFF);
	loadIX(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
	#ifdef POSTCODEDD09
		POSTCODEDD09
	#endif
}
void codeDD19(){
	UINT16 i16;
	UINT32 i32;
	//ADD   IX,DE
	#ifdef PRECODEDD19
		PRECODEDD19
	#endif
	setT15();
	i32=regIX+regDE;
	i16=(regIX&0x0FFF)+(regDE&0x0FFF);
	loadIX(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
	#ifdef POSTCODEDD19
		POSTCODEDD19
	#endif
}
void codeDD21(){
	UINT16 i16;
	//LD    IX,nn
	#ifdef PRECODEDD21
		PRECODEDD21
	#endif
	setT14();
	i16=getCode();
	i16|=getCode()<<8;
	loadIX(i16);
	#ifdef POSTCODEDD21
		POSTCODEDD21
	#endif
}
void codeDD22(){
	UINT16 i16;
	//LD    (nn),IX
	#ifdef PRECODEDD22
		PRECODEDD22
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	writeMemory(i16,regIXl);
	writeMemory(i16+1,regIXh);
	#ifdef POSTCODEDD22
		POSTCODEDD22
	#endif
}
void codeDD23(){
	//INC   IX
	#ifdef PRECODEDD23
		PRECODEDD23
	#endif
	setT10();
	loadIX(regIX+1);
	#ifdef POSTCODEDD23
		POSTCODEDD23
	#endif
}
void codeDD29(){
	UINT16 i16;
	UINT32 i32;
	//ADD   IX,IX
	#ifdef PRECODEDD29
		PRECODEDD29
	#endif
	setT15();
	i32=regIX<<1;
	i16=(regIX&0x0FFF)<<1;
	loadIX(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
	#ifdef POSTCODEDD29
		POSTCODEDD29
	#endif
}
void codeDD2A(){
	UINT16 i16;
	//LD    IX,(nn)
	#ifdef PRECODEDD2A
		PRECODEDD2A
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	loadIXl(readMemory(i16));
	loadIXh(readMemory(i16+1));
	#ifdef POSTCODEDD2A
		POSTCODEDD2A
	#endif
}
void codeDD2B(){
	//DEC   IX
	#ifdef PRECODEDD2B
		PRECODEDD2B
	#endif
	setT10();
	loadIX(regIX-1);
	#ifdef POSTCODEDD2B
		POSTCODEDD2B
	#endif
}
void codeDD34(){
	UINT8 i8;
	UINT16 i16;
	//INC   (IX+d)
	#ifdef PRECODEDD34
		PRECODEDD34
	#endif
	setT23();
	i16=regIX+getCodeIndex(i8);
	i8=readMemory(i16)+1;
	writeMemory(i16,i8);
	flag8inc(i8);
	#ifdef POSTCODEDD34
		POSTCODEDD34
	#endif
}
void codeDD35(){
	UINT8 i8;
	UINT16 i16;
	//DEC   (IX+D)
	#ifdef PRECODEDD35
		PRECODEDD35
	#endif
	setT23();
	i16=regIX+getCodeIndex(i8);
	i8=readMemory(i16)-1;
	writeMemory(i16,i8);
	flag8dec(i8);
	#ifdef POSTCODEDD35
		POSTCODEDD35
	#endif
}
void codeDD36(){
	UINT8 i8;
	UINT16 i16;
	//LD    (IX+d),n
	#ifdef PRECODEDD36
		PRECODEDD36
	#endif
	setT19();
	i16=regIX+getCodeIndex(i8);
	writeMemory(i16,getCode());
	#ifdef POSTCODEDD36
		POSTCODEDD36
	#endif
}
void codeDD39(){
	UINT16 i16;
	UINT32 i32;
	//ADD   IX,SP
	#ifdef PRECODEDD39
		PRECODEDD39
	#endif
	setT15();
	i32=regIX+regSP;
	i16=(regIX&0x0FFF)+(regSP&0x0FFF);
	loadIX(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
	#ifdef POSTCODEDD39
		POSTCODEDD39
	#endif
}
void codeDD46(){
	UINT8 i8;
	//LD    B,(IX+d)
	#ifdef PRECODEDD46
		PRECODEDD46
	#endif
	setT19();
	loadB(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD46
		POSTCODEDD46
	#endif
}
void codeDD4E(){
	UINT8 i8;
	//LD    C,(IX+d)
	#ifdef PRECODEDD4E
		PRECODEDD4E
	#endif
	setT19();
	loadC(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD4E
		POSTCODEDD4E
	#endif
}
void codeDD56(){
	UINT8 i8;
	//LD    D,(IX+d)
	#ifdef PRECODEDD56
		PRECODEDD56
	#endif
	setT19();
	loadD(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD56
		POSTCODEDD56
	#endif
}
void codeDD5E(){
	UINT8 i8;
	//LD    E,(IX+d)
	#ifdef PRECODEDD5E
		PRECODEDD5E
	#endif
	setT19();
	loadE(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD5E
		POSTCODEDD5E
	#endif
}
void codeDD66(){
	UINT8 i8;
	//LD    H,(IX+d)
	#ifdef PRECODEDD66
		PRECODEDD66
	#endif
	setT19();
	loadH(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD66
		POSTCODEDD66
	#endif
}
void codeDD6E(){
	UINT8 i8;
	//LD    L,(IX+d)
	#ifdef PRECODEDD6E
		PRECODEDD6E
	#endif
	setT19();
	loadL(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD6E
		POSTCODEDD6E
	#endif
}
void codeDD70(){
	UINT8 i8;
	//LD    (IX+d),B
	#ifdef PRECODEDD70
		PRECODEDD70
	#endif
	setT19();
	writeMemory(regIX+getCodeIndex(i8),regB);
	#ifdef POSTCODEDD70
		POSTCODEDD70
	#endif
}
void codeDD71(){
	UINT8 i8;
	//LD    (IX+d),C
	#ifdef PRECODEDD71
		PRECODEDD71
	#endif
	setT19();
	writeMemory(regIX+getCodeIndex(i8),regC);
	#ifdef POSTCODEDD71
		POSTCODEDD71
	#endif
}
void codeDD72(){
	UINT8 i8;
	//LD    (IX+d),D
	#ifdef PRECODEDD72
		PRECODEDD72
	#endif
	setT19();
	writeMemory(regIX+getCodeIndex(i8),regD);
	#ifdef POSTCODEDD72
		POSTCODEDD72
	#endif
}
void codeDD73(){
	UINT8 i8;
	//LD    (IX+d),E
	#ifdef PRECODEDD73
		PRECODEDD73
	#endif
	setT19();
	writeMemory(regIX+getCodeIndex(i8),regE);
	#ifdef POSTCODEDD73
		POSTCODEDD73
	#endif
}
void codeDD74(){
	UINT8 i8;
	//LD    (IX+d),H
	#ifdef PRECODEDD74
		PRECODEDD74
	#endif
	setT19();
	writeMemory(regIX+getCodeIndex(i8),regH);
	#ifdef POSTCODEDD74
		POSTCODEDD74
	#endif
}
void codeDD75(){
	UINT8 i8;
	//LD    (IX+d),L
	#ifdef PRECODEDD75
		PRECODEDD75
	#endif
	setT19();
	writeMemory(regIX+getCodeIndex(i8),regL);
	#ifdef POSTCODEDD75
		POSTCODEDD75
	#endif
}
void codeDD77(){
	UINT8 i8;
	//LD    (IX+d),A
	#ifdef PRECODEDD77
		PRECODEDD77
	#endif
	setT19();
	writeMemory(regIX+getCodeIndex(i8),regA);
	#ifdef POSTCODEDD77
		POSTCODEDD77
	#endif
}
void codeDD7E(){
	UINT8 i8;
	//LD    A,(IX+d)
	#ifdef PRECODEDD7E
		PRECODEDD7E
	#endif
	setT19();
	loadA(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD7E
		POSTCODEDD7E
	#endif
}
void codeDD86(){
	UINT8 i8;
	//ADD   A,(IX+d)
	#ifdef PRECODEDD86
		PRECODEDD86
	#endif
	setT19();
	z80ADD(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD86
		POSTCODEDD86
	#endif
}
void codeDD8E(){
	UINT8 i8;
	//ADC   A,(IX+d)
	#ifdef PRECODEDD8E
		PRECODEDD8E
	#endif
	setT19();
	z80ADC(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD8E
		POSTCODEDD8E
	#endif
}
void codeDD96(){
	UINT8 i8;
	//SUB   A,(IX+d)
	#ifdef PRECODEDD96
		PRECODEDD96
	#endif
	setT19();
	z80SUB(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD96
		POSTCODEDD96
	#endif
}
void codeDD9E(){
	UINT8 i8;
	//SBC   A,(IX+d)
	#ifdef PRECODEDD9E
		PRECODEDD9E
	#endif
	setT19();
	z80SBC(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDD9E
		POSTCODEDD9E
	#endif
}
void codeDDA6(){
	UINT8 i8;
	//AND   (IX+d)
	#ifdef PRECODEDDA6
		PRECODEDDA6
	#endif
	setT19();
	z80AND(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDDA6
		POSTCODEDDA6
	#endif
}
void codeDDAE(){
	UINT8 i8;
	//XOR   (IX+d)
	#ifdef PRECODEDDAE
		PRECODEDDAE
	#endif
	setT19();
	z80XOR(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDDAE
		POSTCODEDDAE
	#endif
}
void codeDDB6(){
	UINT8 i8;
	//OR    (IX+d)
	#ifdef PRECODEDDB6
		PRECODEDDB6
	#endif
	setT19();
	z80OR(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDDB6
		POSTCODEDDB6
	#endif
}
void codeDDBE(){
	UINT8 i8;
	//CP    (IX+d)
	#ifdef PRECODEDDBE
		PRECODEDDBE
	#endif
	setT19();
	z80CP(readMemory(regIX+getCodeIndex(i8)));
	#ifdef POSTCODEDDBE
		POSTCODEDDBE
	#endif
}
void codeDDCB06(UINT16 i16){
	//RLC   (IX+d)
	#ifdef PRECODEDDCB06
		PRECODEDDCB06
	#endif
	setT23();
	writeMemory(i16,z80RLC(readMemory(i16)));
	#ifdef POSTCODEDDCB06
		POSTCODEDDCB06
	#endif
}
void codeDDCB0E(UINT16 i16){
	//RRC   (IX+d)
	#ifdef PRECODEDDCB0E
		PRECODEDDCB0E
	#endif
	setT23();
	writeMemory(i16,z80RRC(readMemory(i16)));
	#ifdef POSTCODEDDCB0E
		POSTCODEDDCB0E
	#endif
}
void codeDDCB16(UINT16 i16){
	//RL    (IX+d)
	#ifdef PRECODEDDCB16
		PRECODEDDCB16
	#endif
	setT23();
	writeMemory(i16,z80RL(readMemory(i16)));
	#ifdef POSTCODEDDCB16
		POSTCODEDDCB16
	#endif
}
void codeDDCB1E(UINT16 i16){
	//RR    (IX+d)
	#ifdef PRECODEDDCB1E
		PRECODEDDCB1E
	#endif
	setT23();
	writeMemory(i16,z80RR(readMemory(i16)));
	#ifdef POSTCODEDDCB1E
		POSTCODEDDCB1E
	#endif
}
void codeDDCB26(UINT16 i16){
	//SLA   (IX+d)
	#ifdef PRECODEDDCB26
		PRECODEDDCB26
	#endif
	setT23();
	writeMemory(i16,z80SLA(readMemory(i16)));
	#ifdef POSTCODEDDCB26
		POSTCODEDDCB26
	#endif
}
void codeDDCB2E(UINT16 i16){
	//SRA   (IX+d)
	#ifdef PRECODEDDCB2E
		PRECODEDDCB2E
	#endif
	setT23();
	writeMemory(i16,z80SRA(readMemory(i16)));
	#ifdef POSTCODEDDCB2E
		POSTCODEDDCB2E
	#endif
}
void codeDDCB3E(UINT16 i16){
	//SRL   (IX+d)
	#ifdef PRECODEDDCB3E
		PRECODEDDCB3E
	#endif
	setT23();
	writeMemory(i16,z80SRL(readMemory(i16)));
	#ifdef POSTCODEDDCB3E
		POSTCODEDDCB3E
	#endif
}
void codeDDCB46(UINT16 i16){
	//BIT   0,(IX+d)
	#ifdef PRECODEDDCB46
		PRECODEDDCB46
	#endif
	setT20();
	if (0x01&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEDDCB46
		POSTCODEDDCB46
	#endif
}
void codeDDCB4E(UINT16 i16){
	//BIT   1,(IX+d)
	#ifdef PRECODEDDCB4E
		PRECODEDDCB4E
	#endif
	setT20();
	if (0x02&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEDDCB4E
		POSTCODEDDCB4E
	#endif
}
void codeDDCB56(UINT16 i16){
	//BIT   2,(IX+d)
	#ifdef PRECODEDDCB56
		PRECODEDDCB56
	#endif
	setT20();
	if (0x04&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEDDCB56
		POSTCODEDDCB56
	#endif
}
void codeDDCB5E(UINT16 i16){
	//BIT   3,(IX+d)
	#ifdef PRECODEDDCB5E
		PRECODEDDCB5E
	#endif
	setT20();
	if (0x08&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEDDCB5E
		POSTCODEDDCB5E
	#endif
}
void codeDDCB66(UINT16 i16){
	//BIT   4,(IX+d)
	#ifdef PRECODEDDCB66
		PRECODEDDCB66
	#endif
	setT20();
	if (0x10&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEDDCB66
		POSTCODEDDCB66
	#endif
}
void codeDDCB6E(UINT16 i16){
	//BIT   5,(IX+d)
	#ifdef PRECODEDDCB6E
		PRECODEDDCB6E
	#endif
	setT20();
	if (0x20&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEDDCB6E
		POSTCODEDDCB6E
	#endif
}
void codeDDCB76(UINT16 i16){
	//BIT   6,(IX+d)
	#ifdef PRECODEDDCB76
		PRECODEDDCB76
	#endif
	setT20();
	if (0x40&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEDDCB76
		POSTCODEDDCB76
	#endif
}
void codeDDCB7E(UINT16 i16){
	//BIT   7,(IX+d)
	#ifdef PRECODEDDCB7E
		PRECODEDDCB7E
	#endif
	setT20();
	if (0x80&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEDDCB7E
		POSTCODEDDCB7E
	#endif
}
void codeDDCB86(UINT16 i16){
	//RES   0,(IX+d)
	#ifdef PRECODEDDCB86
		PRECODEDDCB86
	#endif
	setT23();
	writeMemory(i16,0xFE&readMemory(i16));
	#ifdef POSTCODEDDCB86
		POSTCODEDDCB86
	#endif
}
void codeDDCB8E(UINT16 i16){
	//RES   1,(IX+d)
	#ifdef PRECODEDDCB8E
		PRECODEDDCB8E
	#endif
	setT23();
	writeMemory(i16,0xFD&readMemory(i16));
	#ifdef POSTCODEDDCB8E
		POSTCODEDDCB8E
	#endif
}
void codeDDCB96(UINT16 i16){
	//RES   2,(IX+d)
	#ifdef PRECODEDDCB96
		PRECODEDDCB96
	#endif
	setT23();
	writeMemory(i16,0xFB&readMemory(i16));
	#ifdef POSTCODEDDCB96
		POSTCODEDDCB96
	#endif
}
void codeDDCB9E(UINT16 i16){
	//RES   3,(IX+d)
	#ifdef PRECODEDDCB9E
		PRECODEDDCB9E
	#endif
	setT23();
	writeMemory(i16,0xF7&readMemory(i16));
	#ifdef POSTCODEDDCB9E
		POSTCODEDDCB9E
	#endif
}
void codeDDCBA6(UINT16 i16){
	//RES   4,(IX+d)
	#ifdef PRECODEDDCBA6
		PRECODEDDCBA6
	#endif
	setT23();
	writeMemory(i16,0xEF&readMemory(i16));
	#ifdef POSTCODEDDCBA6
		POSTCODEDDCBA6
	#endif
}
void codeDDCBAE(UINT16 i16){
	//RES   5,(IX+d)
	#ifdef PRECODEDDCBAE
		PRECODEDDCBAE
	#endif
	setT23();
	writeMemory(i16,0xDF&readMemory(i16));
	#ifdef POSTCODEDDCBAE
		POSTCODEDDCBAE
	#endif
}
void codeDDCBB6(UINT16 i16){
	//RES   6,(IX+d)
	#ifdef PRECODEDDCBB6
		PRECODEDDCBB6
	#endif
	setT23();
	writeMemory(i16,0xBF&readMemory(i16));
	#ifdef POSTCODEDDCBB6
		POSTCODEDDCBB6
	#endif
}
void codeDDCBBE(UINT16 i16){
	//RES   7,(IX+d)
	#ifdef PRECODEDDCBBE
		PRECODEDDCBBE
	#endif
	setT23();
	writeMemory(i16,0x7F&readMemory(i16));
	#ifdef POSTCODEDDCBBE
		POSTCODEDDCBBE
	#endif
}
void codeDDCBC6(UINT16 i16){
	//SET   0,(IX+d)
	#ifdef PRECODEDDCBC6
		PRECODEDDCBC6
	#endif
	setT23();
	writeMemory(i16,0x01|readMemory(i16));
	#ifdef POSTCODEDDCBC6
		POSTCODEDDCBC6
	#endif
}
void codeDDCBCE(UINT16 i16){
	//SET   1,(IX+d)
	#ifdef PRECODEDDCBCE
		PRECODEDDCBCE
	#endif
	setT23();
	writeMemory(i16,0x02|readMemory(i16));
	#ifdef POSTCODEDDCBCE
		POSTCODEDDCBCE
	#endif
}
void codeDDCBD6(UINT16 i16){
	//SET   2,(IX+d)
	#ifdef PRECODEDDCBD6
		PRECODEDDCBD6
	#endif
	setT23();
	writeMemory(i16,0x04|readMemory(i16));
	#ifdef POSTCODEDDCBD6
		POSTCODEDDCBD6
	#endif
}
void codeDDCBDE(UINT16 i16){
	//SET   3,(IX+d)
	#ifdef PRECODEDDCBDE
		PRECODEDDCBDE
	#endif
	setT23();
	writeMemory(i16,0x08|readMemory(i16));
	#ifdef POSTCODEDDCBDE
		POSTCODEDDCBDE
	#endif
}
void codeDDCBE6(UINT16 i16){
	//SET   4,(IX+d)
	#ifdef PRECODEDDCBE6
		PRECODEDDCBE6
	#endif
	setT23();
	writeMemory(i16,0x10|readMemory(i16));
	#ifdef POSTCODEDDCBE6
		POSTCODEDDCBE6
	#endif
}
void codeDDCBEE(UINT16 i16){
	//SET   5,(IX+d)
	#ifdef PRECODEDDCBEE
		PRECODEDDCBEE
	#endif
	setT23();
	writeMemory(i16,0x20|readMemory(i16));
	#ifdef POSTCODEDDCBEE
		POSTCODEDDCBEE
	#endif
}
void codeDDCBF6(UINT16 i16){
	//SET   6,(IX+d)
	#ifdef PRECODEDDCBF6
		PRECODEDDCBF6
	#endif
	setT23();
	writeMemory(i16,0x40|readMemory(i16));
	#ifdef POSTCODEDDCBF6
		POSTCODEDDCBF6
	#endif
}
void codeDDCBFE(UINT16 i16){
	//SET   7,(IX+d)
	#ifdef PRECODEDDCBFE
		PRECODEDDCBFE
	#endif
	setT23();
	writeMemory(i16,0x80|readMemory(i16));
	#ifdef POSTCODEDDCBFE
		POSTCODEDDCBFE
	#endif
}
void codeDDE1(){
	//POP   IX
	#ifdef PRECODEDDE1
		PRECODEDDE1
	#endif
	setT14();
	loadIXl(readMemory(regSP));
	loadIXh(readMemory(regSP+1));
	loadSP(regSP+2);
	#ifdef POSTCODEDDE1
		POSTCODEDDE1
	#endif
}
void codeDDE3(){
	UINT8 i8;
	UINT8 i82;
	//DD E3        EX    (SP),IX
	#ifdef PRECODEDDE3
		PRECODEDDE3
	#endif
	setT23();
	i8=readMemory(regSP);
	i82=readMemory(regSP+1);
	writeMemory(regSP,regIXl);
	writeMemory(regSP+1,regIXh);
	loadIXl(i8);
	loadIXh(i82);
	#ifdef POSTCODEDDE3
		POSTCODEDDE3
	#endif
}
void codeDDE5(){
	//PUSH   IX
	#ifdef PRECODEDDE5
		PRECODEDDE5
	#endif
	setT15();
	loadSP(regSP-2);
	writeMemory(regSP,regIXl);
	writeMemory(regSP+1,regIXh);
	#ifdef POSTCODEDDE5
		POSTCODEDDE5
	#endif
}
void codeDDE9(){
	//JP    (IX)
	#ifdef PRECODEDDE9
		PRECODEDDE9
	#endif
	setT8();
	loadPC(regIX);
	#ifdef POSTCODEDDE9
		POSTCODEDDE9
	#endif
}
void codeDDF9(){
	//LD    SP,IX
	#ifdef PRECODEDDF9
		PRECODEDDF9
	#endif
	setT10();
	loadSP(regIX);
	#ifdef POSTCODEDDF9
		POSTCODEDDF9
	#endif
}
void codeED40(){
	//IN    B,(C)
	#ifdef PRECODEED40
		PRECODEED40
	#endif
	UINT8 i8,j8;
	setT12();
	i8=readIO(regC, regB);
	loadB(i8);
	if (i8&0x80) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	#ifdef POSTCODEED40
		POSTCODEED40
	#endif
}
void codeED41(){
	//OUT   (C),B
	#ifdef PRECODEED41
		PRECODEED41
	#endif
	setT12();
	writeIO(regC, regB, regB);
	#ifdef POSTCODEED41
		POSTCODEED41
	#endif
}
void codeED42(){
	//SBC   HL,BC
	#ifdef PRECODEED42
		PRECODEED42
	#endif
	setT15();
	z80SBC16(regBC);
	#ifdef POSTCODEED42
		POSTCODEED42
	#endif
}
void codeED43(){
	UINT16 i16;
	//LD    (nn),BC
	#ifdef PRECODEED43
		PRECODEED43
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	writeMemory(i16,regC);
	writeMemory(i16+1,regB);
	#ifdef POSTCODEED43
		POSTCODEED43
	#endif
}
void codeED44(){
	UINT8 i8;
	//NEG
	#ifdef PRECODEED44
		PRECODEED44
	#endif
	setT8();
	if (0x80==regA) setPflag();
	else clearPflag();
	i8=0-regA;
	if ((i8^regA)&0x10) setHflag();
	else clearHflag();
	loadA(i8);
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8) {
		clearZflag();
		setCflag();
	} else {
		setZflag();
		clearCflag();
	}
	#ifdef POSTCODEED44
		POSTCODEED44
	#endif
}
void codeED45(){
	UINT8 i8;
	UINT16 i16;
	//RETN
	#ifdef PRECODEED45
		PRECODEED45
	#endif
	setT14();
	i8=readMemory(regSP);
	i16=readMemory(regSP+1)<<8;
	i16|=i8;
	loadPC(i16);
	loadSP(regSP+2);
	loadIFF1(flagIFF2);
	#ifdef POSTCODEED45
		POSTCODEED45
	#endif
}
void codeED46(){
	//IM    0
	#ifdef PRECODEED46
		PRECODEED46
	#endif
	setT8();
	loadIM(0);
	#ifdef POSTCODEED46
		POSTCODEED46
	#endif
}
void codeED47(){
	//LD    I,A
	#ifdef PRECODEED47
		PRECODEED47
	#endif
	setT9();
	loadI(regA);
	#ifdef POSTCODEED47
		POSTCODEED47
	#endif
}
void codeED48(){
	//IN    C,(C)
	#ifdef PRECODEED48
		PRECODEED48
	#endif
	UINT8 i8,j8;
	setT12();
	i8=readIO(regC, regB);
	loadC(i8);
	if (i8&0x80) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	#ifdef POSTCODEED48
		POSTCODEED48
	#endif
}
void codeED49(){
	//OUT   (C),C
	#ifdef PRECODEED49
		PRECODEED49
	#endif
	setT12();
	writeIO(regC, regB, regC);
	#ifdef POSTCODEED49
		POSTCODEED49
	#endif
}
void codeED4A(){
	//ADC   HL,BC
	#ifdef PRECODEED4A
		PRECODEED4A
	#endif
	setT15();
	z80ADC16(regBC);
	#ifdef POSTCODEED4A
		POSTCODEED4A
	#endif
}
void codeED4B(){
	UINT16 i16;
	//LD    BC,(nn)
	#ifdef PRECODEED4B
		PRECODEED4B
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	loadC(readMemory(i16));
	loadB(readMemory(i16+1));
	#ifdef POSTCODEED4B
		POSTCODEED4B
	#endif
}
void codeED4D(){
	UINT8 i8;
	UINT16 i16;
	//RETI
	#ifdef PRECODEED4D
		PRECODEED4D
	#endif
	setT14();
	i8=readMemory(regSP);
	i16=readMemory(regSP+1)<<8;
	i16|=i8;
	loadPC(i16);
	loadSP(regSP+2);
	#ifdef POSTCODEED4D
		POSTCODEED4D
	#endif
}
void codeED4F(){
	//LD    R,A
	#ifdef PRECODEED4F
		PRECODEED4F
	#endif
	setT9();
	loadR(regA);
	#ifdef POSTCODEED4F
		POSTCODEED4F
	#endif
}
void codeED50(){
	//IN    D,(C)
	#ifdef PRECODEED50
		PRECODEED50
	#endif
	UINT8 i8,j8;
	setT12();
	i8=readIO(regC, regB);
	loadD(i8);
	if (i8&0x80) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	#ifdef POSTCODEED50
		POSTCODEED50
	#endif
}
void codeED51(){
	//OUT   (C),D
	#ifdef PRECODEED51
		PRECODEED51
	#endif
	setT12();
	writeIO(regC, regB, regD);
	#ifdef POSTCODEED51
		POSTCODEED51
	#endif
}
void codeED52(){
	//SBC   HL,DE
	#ifdef PRECODEED52
		PRECODEED52
	#endif
	setT15();
	z80SBC16(regDE);
	#ifdef POSTCODEED52
		POSTCODEED52
	#endif
}
void codeED53(){
	UINT16 i16;
	//LD    (nn),DE
	#ifdef PRECODEED53
		PRECODEED53
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	writeMemory(i16,regE);
	writeMemory(i16+1,regD);
	#ifdef POSTCODEED53
		POSTCODEED53
	#endif
}
void codeED56(){
	//IM    1
	#ifdef PRECODEED56
		PRECODEED56
	#endif
	setT8();
	loadIM(1);
	#ifdef POSTCODEED56
		POSTCODEED56
	#endif
}
void codeED57(){
	//ED 57   LD    A,I
	#ifdef PRECODEED57
		PRECODEED57
	#endif
	setT9();
	loadA(regI);
	if (flagIFF2) setPflag();
	else clearPflag();
	#ifdef POSTCODEED57
		POSTCODEED57
	#endif
}
void codeED58(){
	//IN    E,(C)
	#ifdef PRECODEED58
		PRECODEED58
	#endif
	UINT8 i8,j8;
	setT12();
	i8=readIO(regC, regB);
	loadE(i8);
	if (i8&0x80) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	#ifdef POSTCODEED58
		POSTCODEED58
	#endif
}
void codeED59(){
	//OUT   (C),E
	#ifdef PRECODEED59
		PRECODEED59
	#endif
	setT12();
	writeIO(regC, regB, regE);
	#ifdef POSTCODEED59
		POSTCODEED59
	#endif
}
void codeED5A(){
	//ADC   HL,DE
	#ifdef PRECODEED5A
		PRECODEED5A
	#endif
	setT15();
	z80ADC16(regDE);
	#ifdef POSTCODEED5A
		POSTCODEED5A
	#endif
}
void codeED5B(){
	UINT16 i16;
	//LD    DE,(nn)
	#ifdef PRECODEED5B
		PRECODEED5B
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	loadE(readMemory(i16));
	loadD(readMemory(i16+1));
	#ifdef POSTCODEED5B
		POSTCODEED5B
	#endif
}
void codeED5E(){
	//IM    2
	#ifdef PRECODEED5E
		PRECODEED5E
	#endif
	setT8();
	loadIM(2);
	#ifdef POSTCODEED5E
		POSTCODEED5E
	#endif
}
void codeED5F(){
	//ED 5F   LD    A,R
	#ifdef PRECODEED5F
		PRECODEED5F
	#endif
	setT9();
	loadA(regR);
	if (flagIFF2) setPflag();
	else clearPflag();
	#ifdef POSTCODEED5F
		POSTCODEED5F
	#endif
}
void codeED60(){
	//IN    H,(C)
	#ifdef PRECODEED60
		PRECODEED60
	#endif
	UINT8 i8,j8;
	setT12();
	i8=readIO(regC, regB);
	loadH(i8);
	if (i8&0x80) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	#ifdef POSTCODEED60
		POSTCODEED60
	#endif
}
void codeED61(){
	//OUT   (C),H
	#ifdef PRECODEED61
		PRECODEED61
	#endif
	setT12();
	writeIO(regC, regB, regH);
	#ifdef POSTCODEED61
		POSTCODEED61
	#endif
}
void codeED62(){
	//SBC   HL,HL
	#ifdef PRECODEED62
		PRECODEED62
	#endif
	setT15();
	z80SBC16(regHL);
	#ifdef POSTCODEED62
		POSTCODEED62
	#endif
}
void codeED63(){
	UINT16 i16;
	//LD (nn),HL
	#ifdef PRECODEED63
		PRECODEED63
	#endif
	i16=getCode();
	i16|=getCode()<<8;
	writeMemory(i16,regL);
	writeMemory(i16+1,regH);
	#ifdef POSTCODEED63
		POSTCODEED63
	#endif
}
void codeED67(){
	UINT8 i8;
	//RRD
	#ifdef PRECODEED67
		PRECODEED67
	#endif
	i8=readMemory(regHL);
	writeMemory(regHL,(i8>>4)|(regA<<4));
	loadA(regA&0xf0 | i8&0x0f);
	if (regA&0x80) setSflag();
	else clearSflag();
	if (regA) clearZflag();
	else setZflag();
	clearHflag();
	clearNflag();
	setZ80Parity(regA,i8);
	#ifdef POSTCODEED67
		POSTCODEED67
	#endif
}
void codeED68(){
	//IN    L,(C)
	#ifdef PRECODEED68
		PRECODEED68
	#endif
	UINT8 i8,j8;
	setT12();
	i8=readIO(regC, regB);
	loadL(i8);
	if (i8&0x80) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	#ifdef POSTCODEED68
		POSTCODEED68
	#endif
}
void codeED69(){
	//OUT   (C),L
	#ifdef PRECODEED69
		PRECODEED69
	#endif
	setT12();
	writeIO(regC, regB, regL);
	#ifdef POSTCODEED69
		POSTCODEED69
	#endif
}
void codeED6A(){
	//ADC   HL,HL
	#ifdef PRECODEED6A
		PRECODEED6A
	#endif
	setT15();
	z80ADC16(regHL);
	#ifdef POSTCODEED6A
		POSTCODEED6A
	#endif
}
void codeED6B(){
	UINT16 i16;
	//LD HL,(nn)
	#ifdef PRECODEED6B
		PRECODEED6B
	#endif
	i16=getCode();
	i16|=getCode()<<8;
	loadL(readMemory(i16));
	loadH(readMemory(i16+1));
	#ifdef POSTCODEED6B
		POSTCODEED6B
	#endif
}
void codeED6F(){
	UINT8 i8;
	//RLD
	#ifdef PRECODEED6F
		PRECODEED6F
	#endif
	i8=readMemory(regHL);
	writeMemory(regHL,(i8<<4)|(regA&0x0f));
	loadA(regA&0xf0 | (i8>>4));
	if (regA&0x80) setSflag();
	else clearSflag();
	if (regA) clearZflag();
	else setZflag();
	clearHflag();
	clearNflag();
	setZ80Parity(regA,i8);
	#ifdef POSTCODEED6F
		POSTCODEED6F
	#endif
}
void codeED72(){
	//SBC   HL,SP
	#ifdef PRECODEED72
		PRECODEED72
	#endif
	setT15();
	z80SBC16(regSP);
	#ifdef POSTCODEED72
		POSTCODEED72
	#endif
}
void codeED73(){
	UINT16 i16;
	//LD    (nn),SP
	#ifdef PRECODEED73
		PRECODEED73
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	writeMemory(i16,regSPl);
	writeMemory(i16+1,regSPh);
	#ifdef POSTCODEED73
		POSTCODEED73
	#endif
}
void codeED78(){
	//IN    A,(C)
	#ifdef PRECODEED78
		PRECODEED78
	#endif
	UINT8 i8,j8;
	setT12();
	i8=readIO(regC, regB);
	loadA(i8);
	if (i8&0x80) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	#ifdef POSTCODEED78
		POSTCODEED78
	#endif
}
void codeED79(){
	//OUT   (c),A
	#ifdef PRECODEED79
		PRECODEED79
	#endif
	setT12();
	writeIO(regC, regB, regA);
	#ifdef POSTCODEED79
		POSTCODEED79
	#endif
}
void codeED7A(){
	//ADC   HL,SP
	#ifdef PRECODEED7A
		PRECODEED7A
	#endif
	setT15();
	z80ADC16(regSP);
	#ifdef POSTCODEED7A
		POSTCODEED7A
	#endif
}
void codeED7B(){
	UINT16 i16;
	//LD    SP,(nn)
	#ifdef PRECODEED7B
		PRECODEED7B
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	loadSPl(readMemory(i16));
	loadSPh(readMemory(i16+1));
	#ifdef POSTCODEED7B
		POSTCODEED7B
	#endif
}
void codeEDA0(){
	//LDI
	#ifdef PRECODEEDA0
		PRECODEEDA0
	#endif
	//(DE) © (HL), DE © DE + 1, HL © HL + 1, BC © BC -1
	setT16();
	writeMemory(regDE,readMemory(regHL));
	loadDE(regDE+1);
	loadHL(regHL+1);
	loadBC(regBC-1);
	clearHflag();
	if (regBC) setPflag();
	else clearPflag();
	clearNflag();
	#ifdef POSTCODEEDA0
		POSTCODEEDA0
	#endif
}
void codeEDA1(){
	UINT8 i8;
	UINT8 i82;
	//CPI
	#ifdef PRECODEEDA1
		PRECODEEDA1
	#endif
	//A- (HL), HL © HL +1, BC © BC -1
	setT16();
	i8=readMemory(regHL);
	i82=(0x0F&regA)-(0x0F&i8);
	i8=regA-i8;
	loadHL(regHL+1);
	loadBC(regBC-1);
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	if (0x80&i82) setHflag();
	else clearHflag();
	if (regBC) setPflag();
	else clearPflag();
	setNflag();
	#ifdef POSTCODEEDA1
		POSTCODEEDA1
	#endif
}
void codeEDA2(){
	//INI
	#ifdef PRECODEEDA2
		PRECODEEDA2
	#endif
	//(HL) © (C), B © B -1, HL © HL + 1
	setT16();
	writeMemory(regHL,readIO(regC,regB));
	loadHL(regHL+1);
	loadB(regB-1);
	if (regB) clearZflag();
	else setZflag();
	setNflag();
	#ifdef POSTCODEEDA2
		POSTCODEEDA2
	#endif
}
void codeEDA3(){
	//OUTI
	#ifdef PRECODEEDA3
		PRECODEEDA3
	#endif
	//(C) © (HL), B © B -1, HL © HL + 1
	setT16();
	writeIO(regC,regB,readMemory(regHL));
	loadHL(regHL+1);
	loadB(regB-1);
	if (regB) clearZflag();
	else setZflag();
	setNflag();	
	#ifdef POSTCODEEDA3
		POSTCODEEDA3
	#endif
}
void codeEDA8(){
	//LDD
	#ifdef PRECODEEDA8
		PRECODEEDA8
	#endif
	//(DE) © (HL), DE © DE -1, HL © HL-1, BC © BC-1
	setT16();
	writeMemory(regDE,readMemory(regHL));
	loadDE(regDE-1);
	loadHL(regHL-1);
	loadBC(regBC-1);
	clearHflag();
	if (regBC) setPflag();
	else clearPflag();
	clearNflag();
	#ifdef POSTCODEEDA8
		POSTCODEEDA8
	#endif
}
void codeEDA9(){
	UINT8 i8;
	UINT8 i82;
	//CPD
	#ifdef PRECODEEDA9
		PRECODEEDA9
	#endif
	//A -(HL), HL © HL -1, BC © BC -1
	setT16();
	i8=readMemory(regHL);
	i82=(0x0F&regA)-(0x0F&i8);
	i8=regA-i8;
	loadHL(regHL-1);
	loadBC(regBC-1);
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	if (0x80&i82) setHflag();
	else clearHflag();
	if (regBC) setPflag();
	else clearPflag();
	setNflag();
	#ifdef POSTCODEEDA9
		POSTCODEEDA9
	#endif
}
void codeEDAA(){
	//IND
	#ifdef PRECODEEDAA
		PRECODEEDAA
	#endif
	//(HL) © (C), B © B -1, HL © HL -1
	setT16();
	writeMemory(regHL,readIO(regC,regB));
	loadHL(regHL-1);
	loadB(regB-1);
	if (regB) clearZflag();
	else setZflag();
	setNflag();
	#ifdef POSTCODEEDAA
		POSTCODEEDAA
	#endif
}
void codeEDAB(){
	//OUTD
	#ifdef PRECODEEDAB
		PRECODEEDAB
	#endif
	//(C) © (HL), B © B -1, HL © HL -1
	setT16();
	writeIO(regC,regB,readMemory(regHL));
	loadHL(regHL-1);
	loadB(regB-1);
	if (regB) clearZflag();
	else setZflag();
	setNflag();	
	#ifdef POSTCODEEDAB
		POSTCODEEDAB
	#endif
}
void codeEDB0(){
	//LDIR
	#ifdef PRECODEEDB0
		PRECODEEDB0
	#endif
	//(DE) © (HL), DE © DE + 1, HL © HL + 1, BC F? BC -1
	if (regBC==1) {
		setT16();
	} else {
		setT21();
		loadPC(regPC-2);
	}
	writeMemory(regDE,readMemory(regHL));
	loadDE(regDE+1);
	loadHL(regHL+1);
	loadBC(regBC-1);
	clearHflag();
	clearPflag();
	clearNflag();
	#ifdef POSTCODEEDB0
		POSTCODEEDB0
	#endif
}
void codeEDB1(){
	UINT8 i8;
	UINT8 i82;
	//CPIR
	#ifdef PRECODEEDB1
		PRECODEEDB1
	#endif
	//A-(HL), HL © HL+1, BC © BC-1
	if (regBC==1 || regA==readMemory(regHL)) {
		setT16();
	} else {
		setT21();
		loadPC(regPC-2);
	}
	i8=readMemory(regHL);
	i82=(0x0F&regA)-(0x0F&i8);
	i8=regA-i8;
	loadHL(regHL+1);
	loadBC(regBC-1);
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	if (0x80&i82) setHflag();
	else clearHflag();
	if (regBC) setPflag();
	else clearPflag();
	setNflag();
	#ifdef POSTCODEEDB1
		POSTCODEEDB1
	#endif
}
void codeEDB2(){
	//INIR
	#ifdef PRECODEEDB2
		PRECODEEDB2
	#endif
	//(HL) © (C), B © B -1, HL © HL +1
	if (regB==1) {
		setT16();
	} else {
		setT21();
		loadPC(regPC-2);
	}
	writeMemory(regHL,readIO(regC,regB));
	loadHL(regHL+1);
	loadB(regB-1);
	setZflag();
	setNflag();
	#ifdef POSTCODEEDB2
		POSTCODEEDB2
	#endif
}
void codeEDB3(){
	//OTIR
	#ifdef PRECODEEDB3
		PRECODEEDB3
	#endif
	//(C) © (HL), B © B -1, HL © HL + 1
	if (regB==1) {
		setT16();
	} else {
		setT21();
		loadPC(regPC-2);
	}
	writeIO(regC,regB,readMemory(regHL));
	loadHL(regHL+1);
	loadB(regB-1);
	setZflag();
	setNflag();	
	#ifdef POSTCODEEDB3
		POSTCODEEDB3
	#endif
}
void codeEDB8(){
	//LDDR
	#ifdef PRECODEEDB8
		PRECODEEDB8
	#endif
	if (regBC==1) {
		setT16();
	} else {
		setT21();
		loadPC(regPC-2);
	}
	writeMemory(regDE,readMemory(regHL));
	loadDE(regDE-1);
	loadHL(regHL-1);
	loadBC(regBC-1);
	clearHflag();
	clearPflag();
	clearNflag();
	#ifdef POSTCODEEDB8
		POSTCODEEDB8
	#endif
}
void codeEDB9(){
	UINT8 i8;
	UINT8 i82;
	//CPDR
	#ifdef PRECODEEDB9
		PRECODEEDB9
	#endif
	if (regBC==1 || regA==readMemory(regHL)) {
		setT16();
	} else {
		setT21();
		loadPC(regPC-2);
	}
	i8=readMemory(regHL);
	i82=(0x0F&regA)-(0x0F&i8);
	i8=regA-i8;
	loadHL(regHL-1);
	loadBC(regBC-1);
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8) clearZflag();
	else setZflag();
	if (0x80&i82) setHflag();
	else clearHflag();
	if (regBC) setPflag();
	else clearPflag();
	setNflag();
	#ifdef POSTCODEEDB9
		POSTCODEEDB9
	#endif
}
void codeEDBA(){
	//INDR
	#ifdef PRECODEEDBA
		PRECODEEDBA
	#endif
	if (regB==1) {
		setT16();
	} else {
		setT21();
		loadPC(regPC-2);
	}
	writeMemory(regHL,readIO(regC,regB));
	loadHL(regHL-1);
	loadB(regB-1);
	setZflag();
	setNflag();
	#ifdef POSTCODEEDBA
		POSTCODEEDBA
	#endif
}
void codeEDBB(){
	//OTDR
	#ifdef PRECODEEDBB
		PRECODEEDBB
	#endif
	if (regB==1) {
		setT16();
	} else {
		setT21();
		loadPC(regPC-2);
	}
	writeIO(regC,regB,readMemory(regHL));
	loadHL(regHL-1);
	loadB(regB-1);
	setZflag();
	setNflag();	
	#ifdef POSTCODEEDBB
		POSTCODEEDBB
	#endif
}
void codeFD09(){
	UINT16 i16;
	UINT32 i32;
	//ADD   IY,BC
	#ifdef PRECODEFD09
		PRECODEFD09
	#endif
	setT15();
	i32=regIY+regBC;
	i16=(regIY&0x0FFF)+(regBC&0x0FFF);
	loadIY(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
	#ifdef POSTCODEFD09
		POSTCODEFD09
	#endif
}
void codeFD19(){
	UINT16 i16;
	UINT32 i32;
	//ADD   IY,DE
	#ifdef PRECODEFD19
		PRECODEFD19
	#endif
	setT15();
	i32=regIY+regDE;
	i16=(regIY&0x0FFF)+(regDE&0x0FFF);
	loadIY(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
	#ifdef POSTCODEFD19
		POSTCODEFD19
	#endif
}
void codeFD21(){
	UINT16 i16;
	//LD    IY,nn
	#ifdef PRECODEFD21
		PRECODEFD21
	#endif
	setT14();
	i16=getCode();
	i16|=getCode()<<8;
	loadIY(i16);
	#ifdef POSTCODEFD21
		POSTCODEFD21
	#endif
}
void codeFD22(){
	UINT16 i16;
	//LD    (nn),IY
	#ifdef PRECODEFD22
		PRECODEFD22
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	writeMemory(i16,regIYl);
	writeMemory(i16+1,regIYh);
	#ifdef POSTCODEFD22
		POSTCODEFD22
	#endif
}
void codeFD23(){
	//INC   IY
	#ifdef PRECODEFD23
		PRECODEFD23
	#endif
	setT10();
	loadIY(regIY+1);
	#ifdef POSTCODEFD23
		POSTCODEFD23
	#endif
}
void codeFD29(){
	UINT16 i16;
	UINT32 i32;
	//ADD   IY,IY
	#ifdef PRECODEFD29
		PRECODEFD29
	#endif
	setT15();
	i32=regIY<<1;
	i16=(regIY&0x0FFF)<<1;
	loadIY(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
	#ifdef POSTCODEFD29
		POSTCODEFD29
	#endif
}
void codeFD2A(){
	UINT16 i16;
	//LD    IY,(nn)
	#ifdef PRECODEFD2A
		PRECODEFD2A
	#endif
	setT20();
	i16=getCode();
	i16|=getCode()<<8;
	loadIYl(readMemory(i16));
	loadIYh(readMemory(i16+1));
	#ifdef POSTCODEFD2A
		POSTCODEFD2A
	#endif
}
void codeFD2B(){
	//DEC   IY
	#ifdef PRECODEFD2B
		PRECODEFD2B
	#endif
	setT10();
	loadIY(regIY-1);
	#ifdef POSTCODEFD2B
		POSTCODEFD2B
	#endif
}
void codeFD34(){
	UINT8 i8;
	UINT16 i16;
	//INC   (IY+d)
	#ifdef PRECODEFD34
		PRECODEFD34
	#endif
	setT23();
	i16=regIY+getCodeIndex(i8);
	i8=readMemory(i16)+1;
	writeMemory(i16,i8);
	flag8inc(i8);
	#ifdef POSTCODEFD34
		POSTCODEFD34
	#endif
}
void codeFD35(){
	UINT8 i8;
	UINT16 i16;
	//DEC   (IY+D)
	#ifdef PRECODEFD35
		PRECODEFD35
	#endif
	setT23();
	i16=regIY+getCodeIndex(i8);
	i8=readMemory(i16)-1;
	writeMemory(i16,i8);
	flag8dec(i8);
	#ifdef POSTCODEFD35
		POSTCODEFD35
	#endif
}
void codeFD36(){
	UINT8 i8;
	UINT16 i16;
	//LD    (IY+d),n
	#ifdef PRECODEFD36
		PRECODEFD36
	#endif
	setT19();
	i16=regIY+getCodeIndex(i8);
	writeMemory(i16,getCode());
	#ifdef POSTCODEFD36
		POSTCODEFD36
	#endif
}
void codeFD39(){
	UINT16 i16;
	UINT32 i32;
	//ADD   IY,SP
	#ifdef PRECODEFD39
		PRECODEFD39
	#endif
	setT15();
	i32=regIY+regSP;
	i16=(regIY&0x0FFF)+(regSP&0x0FFF);
	loadIY(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
	#ifdef POSTCODEFD39
		POSTCODEFD39
	#endif
}
void codeFD46(){
	UINT8 i8;
	//LD    B,(IY+d)
	#ifdef PRECODEFD46
		PRECODEFD46
	#endif
	setT19();
	loadB(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD46
		POSTCODEFD46
	#endif
}
void codeFD4E(){
	UINT8 i8;
	//LD    C,(IY+d)
	#ifdef PRECODEFD4E
		PRECODEFD4E
	#endif
	setT19();
	loadC(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD4E
		POSTCODEFD4E
	#endif
}
void codeFD56(){
	UINT8 i8;
	//LD    D,(IY+d)
	#ifdef PRECODEFD56
		PRECODEFD56
	#endif
	setT19();
	loadD(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD56
		POSTCODEFD56
	#endif
}
void codeFD5E(){
	UINT8 i8;
	//LD    E,(IY+d)
	#ifdef PRECODEFD5E
		PRECODEFD5E
	#endif
	setT19();
	loadE(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD5E
		POSTCODEFD5E
	#endif
}
void codeFD66(){
	UINT8 i8;
	//LD    H,(IY+d)
	#ifdef PRECODEFD66
		PRECODEFD66
	#endif
	setT19();
	loadH(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD66
		POSTCODEFD66
	#endif
}
void codeFD6E(){
	UINT8 i8;
	//LD    L,(IY+d)
	#ifdef PRECODEFD6E
		PRECODEFD6E
	#endif
	setT19();
	loadL(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD6E
		POSTCODEFD6E
	#endif
}
void codeFD70(){
	UINT8 i8;
	//LD    (IY+d),B
	#ifdef PRECODEFD70
		PRECODEFD70
	#endif
	setT19();
	writeMemory(regIY+getCodeIndex(i8),regB);
	#ifdef POSTCODEFD70
		POSTCODEFD70
	#endif
}
void codeFD71(){
	UINT8 i8;
	//LD    (IY+d),C
	#ifdef PRECODEFD71
		PRECODEFD71
	#endif
	setT19();
	writeMemory(regIY+getCodeIndex(i8),regC);
	#ifdef POSTCODEFD71
		POSTCODEFD71
	#endif
}
void codeFD72(){
	UINT8 i8;
	//LD    (IY+d),D
	#ifdef PRECODEFD72
		PRECODEFD72
	#endif
	setT19();
	writeMemory(regIY+getCodeIndex(i8),regD);
	#ifdef POSTCODEFD72
		POSTCODEFD72
	#endif
}
void codeFD73(){
	UINT8 i8;
	//LD    (IY+d),E
	#ifdef PRECODEFD73
		PRECODEFD73
	#endif
	setT19();
	writeMemory(regIY+getCodeIndex(i8),regE);
	#ifdef POSTCODEFD73
		POSTCODEFD73
	#endif
}
void codeFD74(){
	UINT8 i8;
	//LD    (IY+d),H
	#ifdef PRECODEFD74
		PRECODEFD74
	#endif
	setT19();
	writeMemory(regIY+getCodeIndex(i8),regH);
	#ifdef POSTCODEFD74
		POSTCODEFD74
	#endif
}
void codeFD75(){
	UINT8 i8;
	//LD    (IY+d),L
	#ifdef PRECODEFD75
		PRECODEFD75
	#endif
	setT19();
	writeMemory(regIY+getCodeIndex(i8),regL);
	#ifdef POSTCODEFD75
		POSTCODEFD75
	#endif
}
void codeFD77(){
	UINT8 i8;
	//LD    (IY+d),A
	#ifdef PRECODEFD77
		PRECODEFD77
	#endif
	setT19();
	writeMemory(regIY+getCodeIndex(i8),regA);
	#ifdef POSTCODEFD77
		POSTCODEFD77
	#endif
}
void codeFD7E(){
	UINT8 i8;
	//LD    A,(IY+d)
	#ifdef PRECODEFD7E
		PRECODEFD7E
	#endif
	setT19();
	loadA(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD7E
		POSTCODEFD7E
	#endif
}
void codeFD86(){
	UINT8 i8;
	//ADD   A,(IY+d)
	#ifdef PRECODEFD86
		PRECODEFD86
	#endif
	setT19();
	z80ADD(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD86
		POSTCODEFD86
	#endif
}
void codeFD8E(){
	UINT8 i8;
	//ADC   A,(IY+d)
	#ifdef PRECODEFD8E
		PRECODEFD8E
	#endif
	setT19();
	z80ADC(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD8E
		POSTCODEFD8E
	#endif
}
void codeFD96(){
	UINT8 i8;
	//SUB   A,(IY+d)
	#ifdef PRECODEFD96
		PRECODEFD96
	#endif
	setT19();
	z80SUB(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD96
		POSTCODEFD96
	#endif
}
void codeFD9E(){
	UINT8 i8;
	//SBC   A,(IY+d)
	#ifdef PRECODEFD9E
		PRECODEFD9E
	#endif
	setT19();
	z80SBC(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFD9E
		POSTCODEFD9E
	#endif
}
void codeFDA6(){
	UINT8 i8;
	//AND   (IY+d)
	#ifdef PRECODEFDA6
		PRECODEFDA6
	#endif
	setT19();
	z80AND(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFDA6
		POSTCODEFDA6
	#endif
}
void codeFDAE(){
	UINT8 i8;
	//XOR   (IY+d)
	#ifdef PRECODEFDAE
		PRECODEFDAE
	#endif
	setT19();
	z80XOR(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFDAE
		POSTCODEFDAE
	#endif
}
void codeFDB6(){
	UINT8 i8;
	//OR    (IY+d)
	#ifdef PRECODEFDB6
		PRECODEFDB6
	#endif
	setT19();
	z80OR(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFDB6
		POSTCODEFDB6
	#endif
}
void codeFDBE(){
	UINT8 i8;
	//CP    (IY+d)
	#ifdef PRECODEFDBE
		PRECODEFDBE
	#endif
	setT19();
	z80CP(readMemory(regIY+getCodeIndex(i8)));
	#ifdef POSTCODEFDBE
		POSTCODEFDBE
	#endif
}
void codeFDCB06(UINT16 i16){
	//RLC   (IY+d)
	#ifdef PRECODEFDCB06
		PRECODEFDCB06
	#endif
	setT23();
	writeMemory(i16,z80RLC(readMemory(i16)));
	#ifdef POSTCODEFDCB06
		POSTCODEFDCB06
	#endif
}
void codeFDCB0E(UINT16 i16){
	//RRC   (IY+d)
	#ifdef PRECODEFDCB0E
		PRECODEFDCB0E
	#endif
	setT23();
	writeMemory(i16,z80RRC(readMemory(i16)));
	#ifdef POSTCODEFDCB0E
		POSTCODEFDCB0E
	#endif
}
void codeFDCB16(UINT16 i16){
	//RL    (IY+d)
	#ifdef PRECODEFDCB16
		PRECODEFDCB16
	#endif
	setT23();
	writeMemory(i16,z80RL(readMemory(i16)));
	#ifdef POSTCODEFDCB16
		POSTCODEFDCB16
	#endif
}
void codeFDCB1E(UINT16 i16){
	//RR    (IY+d)
	#ifdef PRECODEFDCB1E
		PRECODEFDCB1E
	#endif
	setT23();
	writeMemory(i16,z80RR(readMemory(i16)));
	#ifdef POSTCODEFDCB1E
		POSTCODEFDCB1E
	#endif
}
void codeFDCB26(UINT16 i16){
	//SLA   (IY+d)
	#ifdef PRECODEFDCB26
		PRECODEFDCB26
	#endif
	setT23();
	writeMemory(i16,z80SLA(readMemory(i16)));
	#ifdef POSTCODEFDCB26
		POSTCODEFDCB26
	#endif
}
void codeFDCB2E(UINT16 i16){
	//SRA   (IY+d)
	#ifdef PRECODEFDCB2E
		PRECODEFDCB2E
	#endif
	setT23();
	writeMemory(i16,z80SRA(readMemory(i16)));
	#ifdef POSTCODEFDCB2E
		POSTCODEFDCB2E
	#endif
}
void codeFDCB3E(UINT16 i16){
	//SRL   (IY+d)
	#ifdef PRECODEFDCB3E
		PRECODEFDCB3E
	#endif
	setT23();
	writeMemory(i16,z80SRL(readMemory(i16)));
	#ifdef POSTCODEFDCB3E
		POSTCODEFDCB3E
	#endif
}
void codeFDCB46(UINT16 i16){
	//BIT   0,(IY+d)
	#ifdef PRECODEFDCB46
		PRECODEFDCB46
	#endif
	setT20();
	if (0x01&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEFDCB46
		POSTCODEFDCB46
	#endif
}
void codeFDCB4E(UINT16 i16){
	//BIT   1,(IY+d)
	#ifdef PRECODEFDCB4E
		PRECODEFDCB4E
	#endif
	setT20();
	if (0x02&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEFDCB4E
		POSTCODEFDCB4E
	#endif
}
void codeFDCB56(UINT16 i16){
	//BIT   2,(IY+d)
	#ifdef PRECODEFDCB56
		PRECODEFDCB56
	#endif
	setT20();
	if (0x04&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEFDCB56
		POSTCODEFDCB56
	#endif
}
void codeFDCB5E(UINT16 i16){
	//BIT   3,(IY+d)
	#ifdef PRECODEFDCB5E
		PRECODEFDCB5E
	#endif
	setT20();
	if (0x08&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEFDCB5E
		POSTCODEFDCB5E
	#endif
}
void codeFDCB66(UINT16 i16){
	//BIT   4,(IY+d)
	#ifdef PRECODEFDCB66
		PRECODEFDCB66
	#endif
	setT20();
	if (0x10&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEFDCB66
		POSTCODEFDCB66
	#endif
}
void codeFDCB6E(UINT16 i16){
	//BIT   5,(IY+d)
	#ifdef PRECODEFDCB6E
		PRECODEFDCB6E
	#endif
	setT20();
	if (0x20&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEFDCB6E
		POSTCODEFDCB6E
	#endif
}
void codeFDCB76(UINT16 i16){
	//BIT   6,(IY+d)
	#ifdef PRECODEFDCB76
		PRECODEFDCB76
	#endif
	setT20();
	if (0x40&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEFDCB76
		POSTCODEFDCB76
	#endif
}
void codeFDCB7E(UINT16 i16){
	//BIT   7,(IY+d)
	#ifdef PRECODEFDCB7E
		PRECODEFDCB7E
	#endif
	setT20();
	if (0x80&readMemory(i16)) clearZflag();
	else setZflag();
	setHflag();
	clearNflag();
	#ifdef POSTCODEFDCB7E
		POSTCODEFDCB7E
	#endif
}
void codeFDCB86(UINT16 i16){
	//RES   0,(IY+d)
	#ifdef PRECODEFDCB86
		PRECODEFDCB86
	#endif
	setT23();
	writeMemory(i16,0xFE&readMemory(i16));
	#ifdef POSTCODEFDCB86
		POSTCODEFDCB86
	#endif
}
void codeFDCB8E(UINT16 i16){
	//RES   1,(IY+d)
	#ifdef PRECODEFDCB8E
		PRECODEFDCB8E
	#endif
	setT23();
	writeMemory(i16,0xFD&readMemory(i16));
	#ifdef POSTCODEFDCB8E
		POSTCODEFDCB8E
	#endif
}
void codeFDCB96(UINT16 i16){
	//RES   2,(IY+d)
	#ifdef PRECODEFDCB96
		PRECODEFDCB96
	#endif
	setT23();
	writeMemory(i16,0xFB&readMemory(i16));
	#ifdef POSTCODEFDCB96
		POSTCODEFDCB96
	#endif
}
void codeFDCB9E(UINT16 i16){
	//RES   3,(IY+d)
	#ifdef PRECODEFDCB9E
		PRECODEFDCB9E
	#endif
	setT23();
	writeMemory(i16,0xF7&readMemory(i16));
	#ifdef POSTCODEFDCB9E
		POSTCODEFDCB9E
	#endif
}
void codeFDCBA6(UINT16 i16){
	//RES   4,(IY+d)
	#ifdef PRECODEFDCBA6
		PRECODEFDCBA6
	#endif
	setT23();
	writeMemory(i16,0xEF&readMemory(i16));
	#ifdef POSTCODEFDCBA6
		POSTCODEFDCBA6
	#endif
}
void codeFDCBAE(UINT16 i16){
	//RES   5,(IY+d)
	#ifdef PRECODEFDCBAE
		PRECODEFDCBAE
	#endif
	setT23();
	writeMemory(i16,0xDF&readMemory(i16));
	#ifdef POSTCODEFDCBAE
		POSTCODEFDCBAE
	#endif
}
void codeFDCBB6(UINT16 i16){
	//RES   6,(IY+d)
	#ifdef PRECODEFDCBB6
		PRECODEFDCBB6
	#endif
	setT23();
	writeMemory(i16,0xBF&readMemory(i16));
	#ifdef POSTCODEFDCBB6
		POSTCODEFDCBB6
	#endif
}
void codeFDCBBE(UINT16 i16){
	//RES   7,(IY+d)
	#ifdef PRECODEFDCBBE
		PRECODEFDCBBE
	#endif
	setT23();
	writeMemory(i16,0x7F&readMemory(i16));
	#ifdef POSTCODEFDCBBE
		POSTCODEFDCBBE
	#endif
}
void codeFDCBC6(UINT16 i16){
	//SET   0,(IY+d)
	#ifdef PRECODEFDCBC6
		PRECODEFDCBC6
	#endif
	setT23();
	writeMemory(i16,0x01|readMemory(i16));
	#ifdef POSTCODEFDCBC6
		POSTCODEFDCBC6
	#endif
}
void codeFDCBCE(UINT16 i16){
	//SET   1,(IY+d)
	#ifdef PRECODEFDCBCE
		PRECODEFDCBCE
	#endif
	setT23();
	writeMemory(i16,0x02|readMemory(i16));
	#ifdef POSTCODEFDCBCE
		POSTCODEFDCBCE
	#endif
}
void codeFDCBD6(UINT16 i16){
	//SET   2,(IY+d)
	#ifdef PRECODEFDCBD6
		PRECODEFDCBD6
	#endif
	setT23();
	writeMemory(i16,0x04|readMemory(i16));
	#ifdef POSTCODEFDCBD6
		POSTCODEFDCBD6
	#endif
}
void codeFDCBDE(UINT16 i16){
	//SET   3,(IY+d)
	#ifdef PRECODEFDCBDE
		PRECODEFDCBDE
	#endif
	setT23();
	writeMemory(i16,0x08|readMemory(i16));
	#ifdef POSTCODEFDCBDE
		POSTCODEFDCBDE
	#endif
}
void codeFDCBE6(UINT16 i16){
	//SET   4,(IY+d)
	#ifdef PRECODEFDCBE6
		PRECODEFDCBE6
	#endif
	setT23();
	writeMemory(i16,0x10|readMemory(i16));
	#ifdef POSTCODEFDCBE6
		POSTCODEFDCBE6
	#endif
}
void codeFDCBEE(UINT16 i16){
	//SET   5,(IY+d)
	#ifdef PRECODEFDCBEE
		PRECODEFDCBEE
	#endif
	setT23();
	writeMemory(i16,0x20|readMemory(i16));
	#ifdef POSTCODEFDCBEE
		POSTCODEFDCBEE
	#endif
}
void codeFDCBF6(UINT16 i16){
	//SET   6,(IY+d)
	#ifdef PRECODEFDCBF6
		PRECODEFDCBF6
	#endif
	setT23();
	writeMemory(i16,0x40|readMemory(i16));
	#ifdef POSTCODEFDCBF6
		POSTCODEFDCBF6
	#endif
}
void codeFDCBFE(UINT16 i16){
	//SET   7,(IY+d)
	#ifdef PRECODEFDCBFE
		PRECODEFDCBFE
	#endif
	setT23();
	writeMemory(i16,0x80|readMemory(i16));
	#ifdef POSTCODEFDCBFE
		POSTCODEFDCBFE
	#endif
}
void codeFDE1(){
	//POP   IY
	#ifdef PRECODEFDE1
		PRECODEFDE1
	#endif
	setT14();
	loadIYl(readMemory(regSP));
	loadIYh(readMemory(regSP+1));
	loadSP(regSP+2);
	#ifdef POSTCODEFDE1
		POSTCODEFDE1
	#endif
}
void codeFDE3(){
	UINT8 i8;
	UINT8 i82;
	//DD E3        EX    (SP),IY
	#ifdef PRECODEFDE3
		PRECODEFDE3
	#endif
	setT23();
	i8=readMemory(regSP);
	i82=readMemory(regSP+1);
	writeMemory(regSP,regIYl);
	writeMemory(regSP+1,regIYh);
	loadIYl(i8);
	loadIYh(i82);
	#ifdef POSTCODEFDE3
		POSTCODEFDE3
	#endif
}
void codeFDE5(){
	//PUSH   IY
	#ifdef PRECODEFDE5
		PRECODEFDE5
	#endif
	setT15();
	loadSP(regSP-2);
	writeMemory(regSP,regIYl);
	writeMemory(regSP+1,regIYh);
	#ifdef POSTCODEFDE5
		POSTCODEFDE5
	#endif
}
void codeFDE9(){
	//JP    (IY)
	#ifdef PRECODEFDE9
		PRECODEFDE9
	#endif
	setT8();
	loadPC(regIY);
	#ifdef POSTCODEFDE9
		POSTCODEFDE9
	#endif
}
void codeFDF9(){
	//LD    SP,IY
	#ifdef PRECODEFDF9
		PRECODEFDF9
	#endif
	setT10();
	loadSP(regIY);
	#ifdef POSTCODEFDF9
		POSTCODEFDF9
	#endif
}
void codeCB();
void codeDD();
void codeED();
void codeFD();
void codeDDCB();
void codeFDCB();
#endif //Z80
#include "z80jump.h"
