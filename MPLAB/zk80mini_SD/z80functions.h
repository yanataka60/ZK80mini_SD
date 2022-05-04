/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

/*	ADD and ADC instructions
	Flag register: SZ-H-PNC
	S is set if result is negative; reset otherwise
	Z is set if result is zero; reset otherwise
	H is set if carry from bit 3; reset otherwise
	P/V is set if overflow; reset otherwise
	N is reset
	C is set if carry from bit 7; reset otherwise
*/
void z80ADD(UINT8 i8){
	UINT8 j8;
	UINT16 i16;
	INT16 p;
	// Preparation
	i16=i8&0xff;
	j8=i8&0x7F;
	i8=i8&0x0F;
	// Prepare P flag
	p=(regA&0x80)?((UINT16)regA-256):(regA);
	p+=(i16&0x80)?((UINT16)i16-256):(i16);
	// Calculation
	i8=(regA&0x0F)+i8;
	j8=(regA&0x7F)+j8;
	i16=regA+i16;
	// Load A
	loadA(i16);
	// Set flags
	i8=i8&0x10;                // H flag
	i8|=i16&0x80;              // S flag
	if (!(i16&0xFF)) i8|=0x40; // Z flag
	if (p<-128 || 127<p)
	                 i8|=0x04; // P flag
	if (i16&0x100)   i8|=0x01; // C flag
	loadF(i8);
}
void z80ADC(UINT8 i8){
	UINT8 j8;
	UINT16 i16;
	INT16 p;
	// Preparation
	i16=i8&0xff;
	j8=i8&0x7F;
	i8=i8&0x0F;
	// Prepare P flag
	p=(regA&0x80)?((UINT16)regA-256):(regA);
	p+=(i16&0x80)?((UINT16)i16-256):(i16);
	// Calculation
	i8=(regA&0x0F)+i8;
	j8=(regA&0x7F)+j8;
	i16=regA+i16;
	if (flagC) {
		i8++;
		j8++;
		i16++;
		p++;
	}
	// Load A
	loadA(i16);
	// Set flags
	i8=i8&0x10;                // H flag
	i8|=i16&0x80;              // S flag
	if (!(i16&0xFF)) i8|=0x40; // Z flag
	if (p<-128 || 127<p)
	                 i8|=0x04; // P flag
	if (i16&0x100)   i8|=0x01; // C flag
	loadF(i8);
}

/*	SUB, CP and SBC insgtructions
	Flag register: SZ-H-PNC
	S is set if result is negative; reset otherwise
	Z is set if result is zero; reset otherwise
	H is set if borrow from bit 4; reset otherwise
	P/V is set if overflow; reset otherwise
	N is set
	C is set if borrow; reset otherwise
*/
void z80SUB(UINT8 i8){
	UINT8 j8;
	UINT16 i16;
	INT16 p;
	// Preparation
	i16=i8&0xff;
	j8=i8&0x7F;
	i8=i8&0x0F;
	// Prepare P flag
	p=(regA&0x80)?((UINT16)regA-256):(regA);
	p-=(i16&0x80)?((UINT16)i16-256):(i16);
	// Calculation
	i8=(regA&0x0F)-i8;
	j8=(regA&0x7F)-j8;
	i16=256+regA-i16;
	// Load A
	loadA(i16);
	// Set flags
	i8=i8&0x10;                // H flag
	i8|=i16&0x80;              // S flag
	if (!(i16&0xFF)) i8|=0x40; // Z flag
	if (p<-128 || 127<p)
	                 i8|=0x04; // P flag
	if (!(i16&0x100)) i8|=0x01;// C flag
	i8|=0x02;                  // N flag
	loadF(i8);
}
void z80CP(UINT8 i8){
	UINT8 j8;
	UINT16 i16;
	INT16 p;
	// Preparation
	i16=i8&0xff;
	j8=i8&0x7F;
	i8=i8&0x0F;
	// Prepare P flag
	p=(regA&0x80)?((UINT16)regA-256):(regA);
	p-=(i16&0x80)?((UINT16)i16-256):(i16);
	// Calculation
	i8=(regA&0x0F)-i8;
	j8=(regA&0x7F)-j8;
	i16=256+regA-i16;
	// Load A
	// Set flags
	i8=i8&0x10;                // H flag
	i8|=i16&0x80;              // S flag
	if (!(i16&0xFF)) i8|=0x40; // Z flag
	if (p<-128 || 127<p)
	                 i8|=0x04; // P flag
	if (!(i16&0x100)) i8|=0x01;// C flag
	i8|=0x02;                  // N flag
	loadF(i8);
}
void z80SBC(UINT8 i8){
	UINT8 j8;
	UINT16 i16;
	INT16 p;
	// Preparation
	i16=i8&0xff;
	j8=i8&0x7F;
	i8=i8&0x0F;
	// Prepare P flag
	p=(regA&0x80)?((UINT16)regA-256):(regA);
	p-=(i16&0x80)?((UINT16)i16-256):(i16);
	// Calculation
	i8=(regA&0x0F)-i8;
	j8=(regA&0x7F)-j8;
	i16=256+regA-i16;
	if (flagC) {
		i8--;
		j8--;
		i16--;
		p--;
	}
	// Load A
	loadA(i16);
	// Set flags
	i8=i8&0x10;                // H flag
	i8|=i16&0x80;              // S flag
	if (!(i16&0xFF)) i8|=0x40; // Z flag
	if (p<-128 || 127<p)
	                 i8|=0x04; // P flag
	if (!(i16&0x100)) i8|=0x01;// C flag
	i8|=0x02;                  // N flag
	loadF(i8);
}

/*	AND instruction
	Flag register: SZ-H-PNC
	S is set if result is negative; reset otherwise
	Z is set if result is zero; reset otherwise
	H is set
	P/V is reset if overflow; reset otherwise (no, should be parity)
	N is reset
	C is reset
*/
void z80AND(UINT8 i8){
	UINT8 j8;
	i8&=regA;
	j8=i8&0x80;        // S flag
	if (!i8) j8|=0x40; // Z flag
	j8|=0x10;          // H flag
	loadA(i8);
	loadF(j8);
	setZ80Parity(i8,j8); // P flag
}

/*	OR instruction
	Flag register: SZ-H-PNC
	S is set if result is negative; reset otherwise
	Z is set if result is zero; reset otherwise
	H is reset
	P/V is set if overflow; reset otherwise  (no, should be parity)
	N is reset
	C is reset
*/
void z80OR(UINT8 i8){
	UINT8 j8;
	i8|=regA;
	j8=i8&0x80;        // S flag
	if (!i8) j8|=0x40; // Z flag
	loadA(i8);
	loadF(j8);
	setZ80Parity(i8,j8); // P flag
}

/*	XOR instruction
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity even; reset otherwise
N is reset
C is reset
*/
void z80XOR(UINT8 i8){
	UINT8 j8;
	i8^=regA;
	j8=i8&0x80;          // S flag
	if (!i8) j8|=0x40;   // Z flag
	loadA(i8);
	loadF(j8);
	setZ80Parity(i8,j8); // P flag
}

/* RLC instuction: CY <- r7<-r0 <- r7
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity even; reset otherwise
N is reset
C is data from bit 7 of source register
*/
UINT8 z80RLC(UINT8 i8){
	UINT8 j8;
	i8&=0xff;
	if (0x80&i8) {
		i8=i8<<1;
		i8|=0x01;
		setCflag();
	} else {
		i8=i8<<1;
		i8&=0xFE;
		clearCflag();
	}
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8==0x00) setZflag();
	else clearZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	return i8;
}

/* RRC instuction: r0 -> r7->r0 -> CY
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity even; reset otherwise,
N is reset
C is data from bit 0 of source register
*/
UINT8 z80RRC(UINT8 i8){
	UINT8 j8;
	i8&=0xff;
	if (0x01&i8) {
		i8=i8>>1;
		i8|=0x80;
		setCflag();
	} else {
		i8=i8>>1;
		i8&=0x7F;
		clearCflag();
	}
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8==0x00) setZflag();
	else clearZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	return i8;
}

/* RL instuction: CY <- r7<-r0 <- CY
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity even; reset otherwise
N is reset
C is data from bit 7 of source register
*/
UINT8 z80RL(UINT8 i8){
	UINT8 j8;
	i8&=0xff;
	if (0x80&i8) {
		i8=i8<<1;
		if (flagC) i8|=0x01;
		else i8&=0xFE;
		setCflag();
	} else {
		i8=i8<<1;
		if (flagC) i8|=0x01;
		else i8&=0xFE;
		clearCflag();
	}
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8==0x00) setZflag();
	else clearZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	return i8;
}

/* RR instuction: CY -> r7->r0 -> CY
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity even; reset otherwise,
N is reset
C is data from bit 0 of source register
*/
UINT8 z80RR(UINT8 i8){
	UINT8 j8;
	i8&=0xff;
	if (0x01&i8) {
		i8=i8>>1;
		if (flagC) i8|=0x80;
		else i8&=0x7F;
		setCflag();
	} else {
		i8=i8>>1;
		if (flagC) i8|=0x80;
		else i8&=0x7F;
		clearCflag();
	}
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8==0x00) setZflag();
	else clearZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	return i8;
}

/* SLA instuction: CY <- r7<-r0 <- 0
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity is even; reset otherwise
N is reset
C is data from bit 7
*/
UINT8 z80SLA(UINT8 i8){
	UINT8 j8;
	i8&=0xff;
	if (0x80&i8) {
		i8=i8<<1;
		i8&=0xFE;
		setCflag();
	} else {
		i8=i8<<1;
		i8&=0xFE;
		clearCflag();
	}
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8==0x00) setZflag();
	else clearZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	return i8;
}

/* SRA instuction: r7 -> r7->r0 -> CY
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity is even; reset otherwise
N is reset
C is data from bit 0 of source register
*/
UINT8 z80SRA(UINT8 i8){
	UINT8 j8;
	i8&=0xff;
	if (0x01&i8) {
		i8=i8>>1;
		if (0x40 & i8) i8|=0x80;
		else i8&=0x7F;
		setCflag();
	} else {
		i8=i8>>1;
		if (0x40 & i8) i8|=0x80;
		else i8&=0x7F;
		clearCflag();
	}
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8==0x00) setZflag();
	else clearZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	return i8;
}

/* SRL instuction: 0 -> r7->r0 -> CY
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is reset
P/V is set if parity is even; reset otherwise
N is reset
C is data from bit 0 of source register
*/
UINT8 z80SRL(UINT8 i8){
	UINT8 j8;
	i8&=0xff;
	if (0x01&i8) {
		i8=i8>>1;
		i8&=0x7F;
		setCflag();
	} else {
		i8=i8>>1;
		i8&=0x7F;
		clearCflag();
	}
	if (0x80&i8) setSflag();
	else clearSflag();
	if (i8==0x00) setZflag();
	else clearZflag();
	clearHflag();
	setZ80Parity(i8,j8);
	clearNflag();
	return i8;
}

/* ADD HL,ss
S is not affected
Z is not affected
H is set if carry out of bit 11; reset otherwise
P/V is not affected
N is reset
C is set if carry from bit 15; reset otherwise
*/
void z80ADD16(UINT16 reg16){
	UINT16 i16;
	UINT32 i32;
	i32=regHL;
	i32+=reg16;
	i16=regHL&0x0FFF;
	i16+=reg16&0x0FFF;
	i16&=0xFFFF;   // Force unsigned short
	i32&=0xFFFFFF; // Force unsigned long
	loadHL(i32);
	if (0xFFFF<i32) setCflag();
	else clearCflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	clearNflag();
}

/* SBC HL,ss
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
H is set if a borrow from bit 12; reset otherwise
P/V is set if overflow; reset otherwise
N is set
C is set if borrow; reset otherwise
*/
void z80SBC16(UINT16 reg16){
	UINT16 i16;
	UINT32 i32;
	i32=regHL;
	i32-=reg16;
	i16=regHL&0x0FFF;
	i16-=reg16&0x0FFF;
	if (flagC) {
		i32--;
		i16--;
	}
	i16&=0xFFFF;   // Force unsigned short
	i32&=0xFFFFFF; // Force unsigned long
	loadHL(i32);
	if (0x8000&i32) setSflag();
	else clearSflag();
	if (i32) clearZflag();
	else setZflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	if (0xFFFF<i32) {
		setCflag();
		setPflag();
	} else {
		clearCflag();
		clearPflag();
	}
	setNflag();
}
/* ADC HL,ss
S is set if result is negative; reset otherwise
Z is set if result is zero; reset otherwise
R is set if carry out of bit 11;. reset otherwise
P/V is set if overflow; reset otherwise
N is reset
C is set if carry from bit 15; reset otherwise
*/
void z80ADC16(UINT16 reg16){
	UINT16 i16;
	UINT32 i32;
	i32=regHL;
	i32+=reg16;
	i16=regHL&0x0FFF;
	i16+=reg16&0x0FFF;
	if (flagC) {
		i32++;
		i16++;
	}
	i16&=0xFFFF;   // Force unsigned short
	i32&=0xFFFFFF; // Force unsigned long
	loadHL(i32);
	if (0x8000&i32) setSflag();
	else clearSflag();
	if (i32) clearZflag();
	else setZflag();
	if (0x0FFF<i16) setHflag();
	else clearHflag();
	if (0xFFFF<i32) {
		setCflag();
		setPflag();
	} else {
		clearCflag();
		clearPflag();
	}
	clearNflag();
}

