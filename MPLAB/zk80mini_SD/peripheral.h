/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

/*	Environment(machine)-specific basic functions follow 
	These are specified to access to MZ-80K (with 28 KB RAM) memory map.
	I/O ports are connected to PORTB of PIC32MX150F128B.
	To emulate the other computer, these must be modified.
*/

// _getCode() macro (as inline function) that fetches a code using PC, and increment PC.
// yanataka customize start
#include "SDFSIO.h"
#include "stdio.h"
// yanataka customize end

// yanataka customize
#define _getCode() (\
	(regPC<0x0300) ? ROM[regPC++] :(\
	(0x7FFF<regPC && regPC<0xF200) ? RAM[(regPC++)&0x7FFF] : 0xFF\
	))
//#define getCode() _getCode()

UINT8 getCode(){
	// Using getCode() as inline function for all will use much memory to exceed the maximum.
	return _getCode();
}
//*/

unsigned char readMemory(UINT16 addr){
// yanataka customize
	long i;
	addr&=0xffff;
	if (addr<0x0300) {
		return ROM[addr];
	} else if (addr<0x8000) {
		return 0xFF; // RST 38
// yanataka customize start
	} else if (addr<0xF200) {
		return RAM[addr&0x7FFF];

	} else if (addr==0xFFFF) {
		for(i=0;i<sizeof PROG;i++){
			RAM[i]=PROG[i];
  		} 		
		return 0xA0; // RST 38
    } else {
// yanataka customize end
		return 0xFF; // RST 38
	}
}

void writeMemory(UINT16 addr, UINT8 data){
	addr&=0xffff;
	data&=0xff;
	if (addr<0x8000) {
		return;
// yanataka customize start
	} else if (addr<0xF200) {
		RAM[addr&0x7FFF]=data;
// yanataka customize end
	} else {
		return;
	}
}

// Global 8255 values
UINT8 g_porta, g_portb, g_portc;

// readIO() function
unsigned char readIO(UINT8 addrL, UINT8 addrH){
	// Key input support (Port A)
	switch (addrL) {
		case 0xF8:
			return g_porta;
		case 0xF9:
			return g_portb;
		case 0xFA:
			return g_portc;
		default:
			return 0xFF;
	}
}
// yanataka customize start
// writeIO() function
void writeIO(UINT8 addrL, UINT8 addrH, UINT8 data){
	long i,j;
	unsigned char fname[10];
	unsigned char ramH,ramL;
	// Key input support
	switch (addrL) {
		case 0x9e: // Event handler 
			j=RAM[0x03EC]+RAM[0x03ED]*256;
			ramL=RAM[0x03EC];
			ramH=RAM[0x03ED];
			sprintf(fname,"%04x.zk8",j);
			switch (data) {
				case 0x00: // STORE DATA
					if (j > 0x7FFF) {
						//Initialize the media
//						TRISA=0x1F;
    					while (!MDD_MediaDetect()) ; //SDカード検出待ち
						//ファイルシステム初期化
						if(FSInit())
							{i=writefile(fname);  }   
						if(i==0){
							RAM[0x03EC]=0xC0;
							RAM[0x03ED]=0xC0;
						} else {
							RAM[0x03EC]=0xFF;
							RAM[0x03ED]=0xFF;
   						}			
						RAM[0x03EE]=ramL;
						RAM[0x03EF]=ramH;
					} else {
						RAM[0x03EC]=0xEE;
						RAM[0x03ED]=0xEE;
						RAM[0x03EE]=ramL;
						RAM[0x03EF]=ramH;
					}
					return;
				case 0x01: // LOAD DATA
				    //Initialize the media
//					TRISA=0x1F;
    				while (!MDD_MediaDetect()) ; //SDカード検出待ち
					//ファイルシステム初期化
					RAM[0x03EE]=ramL;
					RAM[0x03EF]=ramH;
					if(!FSInit()) {
                                   RAM[0x03EC]=0xE0;
     		                       RAM[0x03ED]=0xE0;
                      } else {
                              i=readfile(fname);
					          if(i!=0){
					                   sprintf(fname,"%04x.tk8",j);
							           FSInit();
                                       i=readfile(fname);
							           if(i!=0){
                                                sprintf(fname,"%04x.bin",j);
							                    FSInit();
                                                i=readfile(fname);
							                    if(i!=0){
								                         sprintf(fname,"%04x.btk",j);
								                         FSInit();
                                                         i=readfile2(fname);
								                         if(i!=0){
									                              sprintf(fname,"%04x.hex",j);
									                              FSInit();
                                                                  i=readfile3(fname);
									                              if(i!=0){
										                                   RAM[0x03EC]=0xFF;
										                                   RAM[0x03ED]=0xFF;
									                              }
								                         }
							                    }
						               }
   					          }
                    }          
					return;
				default:
					return;
			}
		case 0x02: // Set row in key matrix (TK-80)
// ブザー接続用(TK80用 8255 PC1 ONで RA1出力)
			if (data&0x02)
			 { LATA=0x02;
			 } else {
			   LATA=0x00;}
			return;
		case 0x98: 
// ブザー接続用(ND80Z3用 0x98 Bit5 ONで RA1出力)
			if (data&0x20)
			 { LATA=0x02;
			 } else {
			   LATA=0x00;}
			return;
// yanataka customize end
		case 0xfa: // Set row in key matrix (TK-80)
			g_portc=data;
			g_porta=0xff;
			if (!(data&0x10)) g_porta&=g_keymatrix[0];
			if (!(data&0x20)) g_porta&=g_keymatrix[1];
			if (!(data&0x40)) g_porta&=g_keymatrix[2];
// yanataka customize start
// ブザー接続用(TK80用 8255 PC1 ONで RA1出力)
			if (data&0x02)
			 { LATA=0x02;
			 } else {
			   LATA=0x00;}
// yanataka customize end
			return;
		case 0xfb: // 8255 control (TK-80)
			if (data&0x80) return; // Ignore mode change.
			data&=0x0f; // Bit change in Port C follows.
			g_portc&=(1<<(data>>1))^0xff;
			g_portc|=(data&0x01)<<(data>>1);
			data=g_portc;
			g_porta=0xff;
			if (!(data&0x10)) g_porta&=g_keymatrix[0];
			if (!(data&0x20)) g_porta&=g_keymatrix[1];
			if (!(data&0x40)) g_porta&=g_keymatrix[2];
// yanataka customize start
// ブザー接続用(TK80用 8255 PC1 ONで RA1出力)
			if (data&0x02)
			 { LATA=0x02;
			 } else {
			   LATA=0x00;}
// yanataka customize end
			return;
		default:
			return;
	}
}

void triggerInt(){
	if (0x8000<=z80PC) intZ80(0xFF);
}

/*	End of environment-specific basic functions */
