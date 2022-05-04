 #include "main.h"

void init_led(){
	// Timer1 settings, ON=1, SIDL=1, TWDIS=0, TGATE=0, 1:1 prescale, TCS=0
	PR1=TIMR1HSTEP-1;
	TMR1=0;
	g_TMR1h=0;
	g_timer1=0;
	IFS0bits.T1IF=0;
	T1CON=0xA000;
	// Timer1 interrupt: priority 4
	IPC1bits.T1IP=4;
	IPC1bits.T1IS=0;
	IEC0bits.T1IE=1;
	// Set "case 0x00000000" values in timerInt() function
	LATB =0x00F0;
// SD—pC³ PB INOUT Ý’è•ÏX 
	TRISB=0xFFFD;
	CNPUBCLR=0x00F0;
// SD—pC³ PULLUPÝ’è•ÏX
	CNPDBSET=0x7E03;
	// Initialize key matrix
	g_keymatrix[0]=0xFF;
	g_keymatrix[1]=0xFF;
	g_keymatrix[2]=0xFF;
}

// When common-anode mode (0 for active row), input key data from three columns.
// The data will be stored in g_keymatrix[] dimension (see readIO() function in peripheral.h). 
// SD—pC³ RA0 -> RA2 RA1 -> RA3
#define readKeyRow(x) \
	if (PORTAbits.RA2) {g_keymatrix[0]|=(1<<x);} else {g_keymatrix[0]&=(0xFF ^ (1<<x));}\
	if (PORTAbits.RA3) {g_keymatrix[1]|=(1<<x);} else {g_keymatrix[1]&=(0xFF ^ (1<<x));}\
	if (PORTBbits.RB2) {g_keymatrix[2]|=(1<<x);} else {g_keymatrix[2]&=(0xFF ^ (1<<x));}

#pragma interrupt timer1Int IPL4SOFT vector 4
void timer1Int(){
	unsigned long mask;
	// This occurs every 0.78125 msec (1280 Hz).
	IFS0CLR=_IFS0_T1IF_MASK; //IFS0bits.T1IF=0;
	// Update timer values
	g_TMR1h+=TIMR1HSTEP;
	if (g_TMR1h==0) g_timer1&=TIMR1HSTEP-1;

	// Determine which LED will be on in each 7-segment display
	// Also read signal from keys
	switch (g_TMR1h&(TIMR1HSTEP*15)) {
		// Following eight cases are for common anode 7 segment LEDs (RAM[0x3F8]-RAM[0x3FB])
		// For bright LED, output 0 to RB2,RB9-14,RB3 and output 1 to RB4-7
		case TIMR1HSTEP*0:
// SD—pC³ PB INOUT Ý’è•ÏX 
			TRISB=0xFFFD;
			LATB =0x00F0;
			CNPUBCLR=0x00F0;
// SD—pC³ PULLUPÝ’è•ÏX
			CNPDBSET=0x7E03;
			break;
		case TIMR1HSTEP*1:
			readKeyRow(7);
			TRISB=0xBFFF;
			break;
		case TIMR1HSTEP*2:
			readKeyRow(6);
			TRISB=0xDFFF;
			break;
		case TIMR1HSTEP*3:
			readKeyRow(5);
			TRISB=0xEFFF;
			break;
		case TIMR1HSTEP*4:
			readKeyRow(4);
			TRISB=0xF7FF;
			break;
		case TIMR1HSTEP*5:
			readKeyRow(3);
			TRISB=0xFBFF;
			break;
		case TIMR1HSTEP*6:
			readKeyRow(2);
			TRISB=0xFDFF;
			break;
		case TIMR1HSTEP*7:
			readKeyRow(1);
// SD—pC³ PB INOUT Ý’è•ÏX 
			TRISB=0xFFFE;
			break;
		// Following eight cases are for common cathode 7 segment LEDs RAM[0x3FC]-RAM[0x3FF]
		// For bright LED, output 1 to RB2,RB9-14,RB3 and output 0 to RB4-7
		case TIMR1HSTEP*8:
			readKeyRow(0);
// SD—pC³ PB INOUT Ý’è•ÏX 
			TRISB=0xFFFD;
// SD—pC³ PB o—Í•ÏX 
			LATB =0x7E03;
			CNPDBCLR=0x00F0;
// SD—pC³ PULLUPÝ’è•ÏX
			CNPUBSET=0x7E03;
			break;
		case TIMR1HSTEP*9:
			TRISB=0xBFFF;
			break;
		case TIMR1HSTEP*10:
			TRISB=0xDFFF;
			break;
		case TIMR1HSTEP*11:
			TRISB=0xEFFF;
			break;
		case TIMR1HSTEP*12:
			TRISB=0xF7FF;
			break;
		case TIMR1HSTEP*13:
			TRISB=0xFBFF;
			break;
		case TIMR1HSTEP*14:
			TRISB=0xFDFF;
			break;
		default:
			TRISB=0xFFFE;
			break;
	}

	// Determine which 7-LED segment will be turned on.
	mask=g_TMR1h;
	mask=mask>>TIMER1LEN;
	mask=mask&7;
	mask=1<<mask;
	switch (g_TMR1h&(TIMR1HSTEP*16*3)) {
		case TIMR1HSTEP*16*0:
			if (g_TMR1h&(TIMR1HSTEP*8)) {
				if (RAM[0x3FC]&mask) TRISBbits.TRISB4=0;
			} else {
				if (RAM[0x3F8]&mask) TRISBbits.TRISB4=0;
			}
			break;
		case TIMR1HSTEP*16*1:
			if (g_TMR1h&(TIMR1HSTEP*8)) {
				if (RAM[0x3FD]&mask) TRISBbits.TRISB5=0;
			} else {
				if (RAM[0x3F9]&mask) TRISBbits.TRISB5=0;
			}
			break;
		case TIMR1HSTEP*16*2:
			if (g_TMR1h&(TIMR1HSTEP*8)) {
				if (RAM[0x3FE]&mask) TRISBbits.TRISB6=0;
			} else {
				if (RAM[0x3FA]&mask) TRISBbits.TRISB6=0;
			}
			break;
		default:
			if (g_TMR1h&(TIMR1HSTEP*8)) {
				if (RAM[0x3FF]&mask) TRISBbits.TRISB7=0;
			} else {
				if (RAM[0x3FB]&mask) TRISBbits.TRISB7=0;
			}
			break;
	}
}