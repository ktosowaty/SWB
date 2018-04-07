#include <REGX52.H>

sbit IN1 = P2^1;
sbit IN2 = P2^2;
sbit EN1 = P2^3;
sbit EN2 = P2^4;
sbit IN3 = P2^5;
sbit IN4 = P2^6;

unsigned char licznikDolny = 0;
unsigned char licznikGorny = 0;

void przerwanie0(void) interrupt 0 //dolny
{
	licznikDolny++;
	if(licznikDolny == 5)
	{
		EN2 = 0;
		IN3 = ~IN3;
		IN4 = ~IN4;
		licznikDolny = 0;
	}
}

void przerwanie1(void) interrupt 2 //gorny
{
	licznikGorny++;
	if(licznikGorny == 5)
	{
		EN1 = 0;
		IN1 = ~IN1;
		IN2 = ~IN2;
		licznikGorny = 0;
	}
}

void serial(void) interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
		if(SBUF == '1' || SBUF == '3') EN1 = 1;
		else if(SBUF == '7' || SBUF == '9') EN2 = 1;
	}
}

void init(void)
{	
	EX0 = 1;
	IT0 = 1;
	EX1 = 1;
	IT1 = 1;
	EA = 1;
	
	IN1 = 1;
	IN2 = 0;
	EN1 = 0;
	IN3 = 0;
	IN4 = 1;
	EN2 = 0;
	
	P3_4 = 0;
	SCON = 0x50;
	T2CON = 0x20;
	RCAP2H = TH2 = 0xFF;
	RCAP2L = TL2 = 0xDC;
	ES = 1;
	TR2 = 1;
}

void main (void)
{
	init();
	while(1)
	{;}
}