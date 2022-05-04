/*
   This program is provided under the LGPL license ver 2.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

#define MAIN
#include "main.h"
// SD�p�C�� LIBRARY�ǉ� 
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

// SD�p�C��
unsigned char data[512]; //�t�@�C���ǂݍ��݃o�b�t�@

// SD�p�C�� ASCII�R�[�h����16�i���֕ϊ�
unsigned int trans(unsigned char c){
	if('0'<=c && '9'>=c) return (c-0x30);//0x30��'0'�̕����R�[�h
	if('A'<=c && 'F'>=c) return (c+0x0A-0x41);//0x41��'A'�̕����R�[�h
	if('a'<=c && 'f'>=c) return (c+0x0A-0x61);//0x61��'a'�̕����R�[�h
	return 0;
}
// SD�p�C�� Load���� zk8 tk8 bin
// 8000h����ǂݏo���镪����������
// �������A83B0h�`83D0h�A83E0h�`83FFh�AF200h�`�ւ̏����݂͖���
int readfile(unsigned char *imagefile){
//ZK8�ATK8�ABIN�t�@�C�����I�[�v�����A�������ɓǂݍ���
//imagefile:�t�@�C�����̃|�C���^
	int i,j,k,l;
	FSFILE *fp;
	fp=FSfopen(imagefile,"r");//�ǂݍ��݂ŃI�[�v��
	if(fp==NULL) return -1; //�t�@�C���I�[�v���G���[
	k=0;
	while(1){
		i=FSfread(data,1,512,fp); //512�o�C�g�������ǂݍ��݁B�r����EOF�̏ꍇ�Ai�ɓǂݍ��񂾃o�C�g��
		if(i==0) break;
		for(j=0;j<i;j++){
			l = k*512+j;
			if((l < 944)||((l > 976) && (l < 992))||((l > 1023) && (l < 29184))){RAM[l]=data[j];}
		}
		k++;
	}
	FSfclose(fp); //�t�@�C���N���[�Y
	RAM[0x03EC]=( 0x8000 + l ) % 256;
	RAM[0x03ED]=( 0x8000 + l ) / 256;
	RAM[0x03EE]=0x8000 % 256;
	RAM[0x03EF]=0x8000 / 256;
	return 0;
}

// SD�p�C�� Load���� btk
// �w�b�_�ɋL�q���ꂽ�J�n�ʒu����ǂݏo���镪����������
// �������A83B0h�`83D0h�A83E0h�`83FFh�AF200h�`�ւ̏����݂͖���
int readfile2(unsigned char *imagefile){
//BTK�t�@�C�����I�[�v�����A�������ɓǂݍ���
//imagefile:�t�@�C�����̃|�C���^
	int i,j,k;
	long sadr,eadr,padr;
	FSFILE *fp;
	fp=FSfopen(imagefile,"r");//�ǂݍ��݂ŃI�[�v��
	if(fp==NULL) return -1; //�t�@�C���I�[�v���G���[

	i=FSfread(data,1,512,fp); //512�o�C�g�������ǂݍ��݁B�r����EOF�̏ꍇ�Ai�ɓǂݍ��񂾃o�C�g��
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
			i=FSfread(data,1,512,fp); //512�o�C�g�������ǂݍ��݁B�r����EOF�̏ꍇ�Ai�ɓǂݍ��񂾃o�C�g��
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

	FSfclose(fp); //�t�@�C���N���[�Y
	eadr--;
	RAM[0x03EC]=eadr % 256;
	RAM[0x03ED]=eadr / 256;
	RAM[0x03EE]=sadr % 256;
	RAM[0x03EF]=sadr / 256;
	return 0;
}
// SD�p�C�� Load���� hex
// hex�t�@�C���̃w�b�_�ɏ]���ď�������
// �������A83B0h�`83D0h�A83E0h�`83FFh�AF200h�`�ւ̏����݂͖���
int readfile3(unsigned char *imagefile){
//HEX�t�@�C�����I�[�v�����A�������ɓǂݍ���
//imagefile:�t�@�C�����̃|�C���^
	int i,j,k,l,dcnt;
	long sadr,eadr,dadr;
	FSFILE *fp;
	fp=FSfopen(imagefile,"r");//�ǂݍ��݂ŃI�[�v��
	if(fp==NULL) return -1; //�t�@�C���I�[�v���G���[
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
	FSfclose(fp); //�t�@�C���N���[�Y
	RAM[0x03EC]=eadr % 256;
	RAM[0x03ED]=eadr / 256;
	RAM[0x03EE]=sadr % 256;
	RAM[0x03EF]=sadr / 256;
	return 0;
}
// SD�p�C�� Save����
int writefile(unsigned char *imagefile){
//�t�@�C�����I�[�v�����A�������̓��e�������o��
//imagefile:�t�@�C�����̃|�C���^
	int i,j,k;
	FSFILE *fp;

	fp=FSfopen(imagefile,"w");//�����o���ŃI�[�v��
	if(fp==NULL) return -1; //�t�@�C���I�[�v���G���[
// SD�p�C�� Save�͒P����8000h����57*512Byte(8000h�`F1FFh)��Save
		for(k=0;k<57;k++){
			for(j=0;j<512;j++){
				data[j]=RAM[k*512+j];
			}
			i=FSfwrite(data,1,512,fp); //512�o�C�g�����������o���B
		}
	FSfclose(fp); //�t�@�C���N���[�Y
	return 0;
}

void main(){
	long i;
	// Weak pull up for RB3
	CNPUB=0x08;
	// RA1, RA2, RA3, RB2, RB3: digital inputs but not analog ones
// SD�p�C��
	ANSELA=0x11;
	ANSELB=0xF3;
// SD�p�C�� �u�U�[�ڑ��p(RA1)
// SD-CARD CD�ƌ��p�ASD-CARD�ɃA�N�Z�X����Ƃ��ɂ͓��͂ɐݒ�
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
// SD�p�C�� �d��ON���̂�RAM�N���A���A�e�X�g�v���O������LOAD
		for(i=0;i<0x7200;i++){
			RAM[i]=0x00;
		}
		for(i=0;i<sizeof PROG;i++){
			RAM[i]=PROG[i];
		}
	}

// SD�p�C�� ���Ӌ@�\�s�����蓖��
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
