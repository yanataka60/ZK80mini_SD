/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

#define MAIN
#include "main.h"
// SD用修正 LIBRARY追加 
#include "SDFSIO.h"

// Clock settings
// SYSCLK = 40 Mhz, PBCLK = 40 Mhz.

// Primary oscillator not used.
#pragma config POSCMOD = OFF
// Fast RC Osc with PLL (~8 MHz)
#pragma config FNOSC = FRCPLL
// Div 2 to make 4 MHz
#pragma config FPLLIDIV = DIV_2
// Mul 24 to make 80 MHz
#pragma config FPLLMUL = MUL_20
// Div 2 to make 40 MHz
#pragma config FPLLODIV = DIV_2
// PBCLK = SYSCLK
#pragma config FPBDIV = DIV_1

// MISC disabled
#pragma config FSOSCEN = OFF
#pragma config IESO = OFF
#pragma config OSCIOFNC = OFF
#pragma config FCKSM = CSDCMD
#pragma config JTAGEN = OFF
#pragma config ICESEL = ICS_PGx1
#pragma config DEBUG = OFF
#pragma config PMDL1WAY = OFF
#pragma config IOL1WAY = OFF
#pragma config FUSBIDIO = OFF
#pragma config FVBUSONIO = OFF

// WDT disabled
#pragma config WDTPS = PS1, FWDTEN = OFF, WINDIS = OFF, FWDTWINSZ = WISZ_25

// protection all off
#pragma config PWP = OFF, BWP = OFF, CP = OFF

// SD用修正
unsigned char data[512]; //ファイル読み込みバッファ

// SD用修正 ASCIIコードから16進数へ変換
unsigned int trans(unsigned char c){
	if('0'<=c && '9'>=c) return (c-0x30);//0x30は'0'の文字コード
	if('A'<=c && 'F'>=c) return (c+0x0A-0x41);//0x41は'A'の文字コード
	if('a'<=c && 'f'>=c) return (c+0x0A-0x61);//0x61は'a'の文字コード
	return 0;
}
// SD用修正 Load処理 zk8 tk8 bin
// 8000hから読み出せる分を書き込み
// ただし、83B0h～83D0h、83E0h～83FFh、F200h～への書込みは無視
int readfile(unsigned char *imagefile){
//ZK8、TK8、BINファイルをオープンし、メモリに読み込み
//imagefile:ファイル名のポインタ
	int i,j,k,l;
	FSFILE *fp;
	fp=FSfopen(imagefile,"r");//読み込みでオープン
	if(fp==NULL) return -1; //ファイルオープンエラー
	k=0;
	while(1){
		i=FSfread(data,1,512,fp); //512バイト文字分読み込み。途中でEOFの場合、iに読み込んだバイト数
		if(i==0) break;
		for(j=0;j<i;j++){
			l = k*512+j;
			if((l < 944)||((l > 976) && (l < 992))||((l > 1023) && (l < 29184))){RAM[l]=data[j];}
		}
		k++;
	}
	FSfclose(fp); //ファイルクローズ
	RAM[0x03EC]=( 0x8000 + l ) % 256;
	RAM[0x03ED]=( 0x8000 + l ) / 256;
	RAM[0x03EE]=0x8000 % 256;
	RAM[0x03EF]=0x8000 / 256;
	return 0;
}

// SD用修正 Load処理 btk
// ヘッダに記述された開始位置から読み出せる分を書き込み
// ただし、83B0h～83D0h、83E0h～83FFh、F200h～への書込みは無視
int readfile2(unsigned char *imagefile){
//BTKファイルをオープンし、メモリに読み込み
//imagefile:ファイル名のポインタ
	int i,j,k;
	long sadr,eadr,padr;
	FSFILE *fp;
	fp=FSfopen(imagefile,"r");//読み込みでオープン
	if(fp==NULL) return -1; //ファイルオープンエラー

	i=FSfread(data,1,512,fp); //512バイト文字分読み込み。途中でEOFの場合、iに読み込んだバイト数
	if(i!=0) {
		sadr=data[0]*256+data[1];
		eadr=data[2]*256+data[3]+1;
		padr=sadr;
		for(j=0;j<i-4;j++){
			if(((padr > 0x7FFF) && (padr < 0x83B0))||((padr > 0x83D0) && (padr < 0x83E0))||((padr > 0x83FF) && (padr < 0xF200))){
				RAM[padr - 0x8000]=data[j + 4];
			}
			padr=padr++;
		}
		k=1;
		while(1){
			i=FSfread(data,1,512,fp); //512バイト文字分読み込み。途中でEOFの場合、iに読み込んだバイト数
			if(i==0) break;
			for(j=0;j<i;j++){
				if(((padr > 0x7FFF) && (padr < 0x83B0))||((padr > 0x83D0) && (padr < 0x83E0))||((padr > 0x83FF) && (padr < 0xF200))){
					RAM[padr - 0x8000]=data[j];
				}
				padr=padr++;
			}
			k++;
		}
	}

	FSfclose(fp); //ファイルクローズ
	eadr--;
	RAM[0x03EC]=eadr % 256;
	RAM[0x03ED]=eadr / 256;
	RAM[0x03EE]=sadr % 256;
	RAM[0x03EF]=sadr / 256;
	return 0;
}
// SD用修正 Load処理 hex
// hexファイルのヘッダに従って書き込み
// ただし、83B0h～83D0h、83E0h～83FFh、F200h～への書込みは無視
int readfile3(unsigned char *imagefile){
//HEXファイルをオープンし、メモリに読み込み
//imagefile:ファイル名のポインタ
	int i,j,k,l,dcnt;
	long sadr,eadr,dadr;
	FSFILE *fp;
	fp=FSfopen(imagefile,"r");//読み込みでオープン
	if(fp==NULL) return -1; //ファイルオープンエラー
	sadr=0;
	while(FSfeof(fp)==0){
		i=FSfread(data,1,3,fp);
		if(i==0) break;
		dcnt=trans(data[1])*16+trans(data[2]);
		if(dcnt==0) break;
		i=FSfread(data,1,dcnt*2+10,fp);
		if(i==0) break;
		dadr=trans(data[0])*4096+trans(data[1])*256+trans(data[2])*16+trans(data[3]);
		if(sadr==0) sadr=dadr;
		k=6;
		for(j=0;j<dcnt;j++){
			if(((dadr > 0x7FFF) && (dadr < 0x83B0))||((dadr > 0x83D0) && (dadr < 0x83E0))||((dadr > 0x83FF) && (dadr < 0xF200))){
				RAM[dadr - 0x8000]=trans(data[k])*16+trans(data[k+1]);
			}
			dadr++;
			k=k+2;
		}
	}
	eadr=dadr-1;
	FSfclose(fp); //ファイルクローズ
	RAM[0x03EC]=eadr % 256;
	RAM[0x03ED]=eadr / 256;
	RAM[0x03EE]=sadr % 256;
	RAM[0x03EF]=sadr / 256;
	return 0;
}
// SD用修正 Save処理
int writefile(unsigned char *imagefile){
//ファイルをオープンし、メモリの内容を書き出し
//imagefile:ファイル名のポインタ
	int i,j,k;
	FSFILE *fp;

	fp=FSfopen(imagefile,"w");//書き出しでオープン
	if(fp==NULL) return -1; //ファイルオープンエラー
// SD用修正 Saveは単純に8000hから57*512Byte(8000h～F1FFh)をSave
		for(k=0;k<57;k++){
			for(j=0;j<512;j++){
				data[j]=RAM[k*512+j];
			}
			i=FSfwrite(data,1,512,fp); //512バイト文字分書き出し。
		}
	FSfclose(fp); //ファイルクローズ
	return 0;
}

void main(){
	long i;
	// Weak pull up for RB3
	CNPUB=0x08;
	// RA1, RA2, RA3, RB2, RB3: digital inputs but not analog ones
// SD用修正
	ANSELA=0x11;
	ANSELB=0xF3;
// SD用修正 ブザー接続用(RA1)
// SD-CARD CDと兼用、SD-CARDにアクセスするときには入力に設定
	TRISA=0x1D;
	LATA=0x00;
	// Initialize interface (TRISB will be also set here.)
	init_led();
	// Other initializations
	INTEnableSystemSingleVectoredInt();
	INTEnableSystemMultiVectoredInt();
	resetZ80();
	// Load test program
	// See main.h; RAM is set as persistent.
	if (RCONbits.POR){
		RCONbits.POR=0;
// SD用修正 電源ON時のみRAMクリアし、テストプログラムをLOAD
		for(i=0;i<0x7200;i++){
			RAM[i]=0x00;
		}
		for(i=0;i<sizeof PROG;i++){
			RAM[i]=PROG[i];
		}
	}

// SD用修正 周辺機能ピン割り当て
	SDI2R=2; //RPA4:SDI2
	RPB8R=4; //RPB8:SDO2

	while(1){
		// Wait until next timing to execute Z80 code
		while((unsigned long)(g_TMR1h|TMR1)<g_timer1);
		// Now, execute the Z80 code.
		// Note that g_timer1 will increment due to each code's T cycles
		execZ80code();
		// Interrupt
		if (!PORTBbits.RB3) {
			triggerInt();
		}
	}
}
