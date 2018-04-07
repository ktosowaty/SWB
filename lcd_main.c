#include <REGX52.H>

extern void LcdInit();
extern void LcdWelcome();
extern void Lcd_Cursor (char row, char column);
extern void Lcd_DisplayCharacter (char a_char);
extern void Lcd_DisplayString (char row, char column, char *string);
extern void Lcd_DisplayScreen (char *ptr);
extern void Lcd_WriteData (unsigned char LcdData);
extern void charInit(void);

unsigned char Var1, Var2, Var3;
unsigned char code witam[] =					"RYBOZORD GAME   "
                                      "MOVE FISH TO EAT"
                                      "WANNA PLAY?     "
																			"YES-INT0 NO-INT1";
unsigned char code GameOver[] =				"U LOST. U GAINED"
                                      "   POINTS. WANNA"
                                      "PLAY AGAIN?     "
																			"YES-INT0 NO-INT1";
unsigned char code nope[] =						"OKAY THEN       "
                                      "IF U CHANGE YOUR"
                                      "MIND I WILL BE  "
																			"AROUND          ";
unsigned char wiersze = 2, kolumny = 5, punktyJednosci = 0, punktyDziesiatki = 0, jedzenieWiersz = 3, jedzenieKolumna = 12, licznik = 0;

void start(void)
{
	Lcd_Cursor(wiersze, kolumny);
	Lcd_WriteData(licznik);
	Lcd_Cursor(jedzenieWiersz, jedzenieKolumna);
	Lcd_WriteData(4);
}

void serial(void) interrupt 4
{
	if(RI == 1)
	{
		RI = 0;		
		Lcd_Cursor(wiersze, kolumny);
		Lcd_DisplayCharacter(' ');
		if(SBUF == '2')
		{
			wiersze--;
			licznik = 2;
		}
		else if(SBUF == '8') 
		{
			wiersze++;
			licznik = 3;
		}			
		
		else if(SBUF == '4')
		{
			kolumny--;
			licznik = 1;
		}	
		else if(SBUF == '6')
		{
			kolumny++;
			licznik = 0;
		}
		if(wiersze == 0 || wiersze == 5 || kolumny == 0 || kolumny == 17)
		{
			Lcd_DisplayScreen(GameOver);
			Lcd_Cursor(2, 1);
			Lcd_DisplayCharacter(punktyDziesiatki + '0');
			Lcd_Cursor(2, 2);
			Lcd_DisplayCharacter(punktyJednosci + '0');
			ES = 0;
		}
		else
		{
			Lcd_Cursor(wiersze, kolumny);
			Lcd_WriteData(licznik);
			if(wiersze == jedzenieWiersz && kolumny == jedzenieKolumna)
			{
				punktyJednosci++;
				if(punktyJednosci == 10)
				{
					punktyJednosci = 0;
					punktyDziesiatki++;
				}
				jedzenieWiersz = (wiersze+kolumny/3)%4+1;
				jedzenieKolumna = (wiersze+kolumny+7)%16+1;
				Lcd_Cursor(jedzenieWiersz, jedzenieKolumna);
				Lcd_WriteData(4);
			}
		}	
	}
}

void przerwanie0(void) interrupt 0
{
	wiersze = 2;
	kolumny = 5;
	punktyJednosci = 0;
	punktyDziesiatki = 0;
	LcdWelcome();
	start();
	ES = 1;
}

void przerwanie1(void) interrupt 2
{
	Lcd_DisplayScreen(nope);
}

void init(void)
{
	EX0 = 1;
	IT0 = 1;
	EX1 = 1;
	IT1 = 1;
	EA = 1;
	
	P3_4 = 0;
	SCON = 0x50;
	T2CON = 0x20;
	RCAP2H = TH2 = 0xFF;
	RCAP2L = TL2 = 0xDC;
	ES = 0;
	TR2 = 1;
}

void main(void){
  LcdInit();
	init();
	charInit();
	Lcd_DisplayScreen(witam);
  while(1) {;}
}