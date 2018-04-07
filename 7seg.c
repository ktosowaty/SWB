#include <REGX52.H>

unsigned char code slimak[6] = {0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
unsigned char code cyfry[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //0 1 2 3 4 5 6 7 8 9
unsigned char xdata prawy _at_ 0xFD00;
unsigned char xdata lewy _at_ 0xFE00;
unsigned char licznik = 0;
unsigned char okrazenia = 0;
unsigned char pomoc1, pomoc2, pomoc3;

void timerInit(void)
{
	IP = 0x05;
	TH1 = 0x00;
	TL1 = 0x00;
	TCON = 0x00;
	TMOD = 0x20;
}

void init(void)
{
	EX0 = 1;
	IT0 = 1;
	EX1 = 1;
	IT1 = 1;
	ET1 = 1;
	EA = 1;
	TR1 = 1;
}

void przerwanie0(void) interrupt 0
{
	licznik++;
	if(licznik == 6)
	{
		licznik = 0;
		okrazenia++;
		if(okrazenia == 10)
			okrazenia = 0;
	}	
}

void przerwanie1(void) interrupt 2
{
	licznik = 0;
	okrazenia = 0;
}

void timer1(void) interrupt 3
{
	pomoc1 = slimak[licznik];
	pomoc2 = cyfry[okrazenia];
	for(pomoc3=0; pomoc3<7; pomoc3++)
	{
		P2_0 = 1;
		P2_1 = 0;
		lewy = pomoc1;
		lewy = 0;
		P2_0 = 0;
		P2_1 = 1;
		prawy = pomoc2;
		prawy = 0;
	}
}

void main(void)
{
	timerInit();
	init();
	while(1)
	{;}
} 