#include <REGX52.H>

char code tab[4] = {0x7F, 0xBF, 0xDF, 0xEF};
char code wcisniete[12] = {0x7B, 0xE7, 0xEB, 0xED, 0xD7, 0xDB, 0xDD, 0xB7, 0xBB, 0xBD, 0x77, 0x7D}; // 0 1 2 3 4 5 6 7 8 9 * #

void serialInit(void)
{
	TH2 = RCAP2H = 0xFF;
	TL2 = RCAP2L = 0xDC;
	T2CON = 0x10;
	SCON = 0x40;
	ES = 1;
	P3_4 = 0;
	EA = 1;
	TR2 = 1;
}

void nadawanie(char znak)
{
	P3_4 = 1;
	TI = 0;
	SBUF = znak;
	while(TI == 0) {;}
	TI = 0;
	P3_4 = 0;
}

void delay(void)
{
	int i, j;
	for(i=0; i<70; i++)
		for(j=0; j<70; j++)
		{}
}

void mruganie(int ile, int pomoc)
{
	int c;
	if((pomoc)%16 == 0) pomoc -= 7;
	else pomoc--;
	for(c=0; c<ile; c++)
	{
		P1 = pomoc-c;
		P0_0 = 0;
		delay();
		P0_0 = 1;
		delay();
		if((pomoc-c)%16 == 0) pomoc -= 6;
	}
}

void main(void)
{	
	char i = 0;
	char val = 0;
	int a = 0, b = 0;
	int ile = 0, pomoc = 0;
	serialInit();
	while(1)
	{
		if(i == 4) i = 0;
		P2 = tab[i++];
		val = P2;
		if(val == tab[i-1]) {} //nic nie wcisnieto
		else
		{
			if(P2 == wcisniete[10])
				{
					ile = 0;
					P1 = 0;
					b = 0;
					pomoc = 0;
				}
			else if(P2 == wcisniete[11])
				{
					mruganie(ile, pomoc);
					ile = 0;
					b = 0;
					pomoc = 0;
				}
			else
			{
				for(a=0; a<10; a++)
				{
					if(P2 == wcisniete[a])
					{
						nadawanie(a + '0');
						P1 = 16*b + a;
						delay();
						ile = 10*b + a;
						pomoc = 16*b + a;
						b = a;
					}	
				}
			}
		}
	}
}