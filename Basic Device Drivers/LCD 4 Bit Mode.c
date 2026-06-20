
#include <xc.h>

#pragma config OSC = INTIO67
#pragma config PWRT = ON        // power up timer enabled
#pragma config BOREN= OFF   // Brown-out Reset enabled in hardware only (SBOREN is disabled) 
#pragma config WDT  = OFF       // WDT disabled
#pragma config MCLRE= ON  
#pragma config LVP  = OFF 
#pragma config PBADEN  = OFF 
#pragma config CPD = ON
#pragma config DEBUG = OFF 
#pragma config CP0 = ON 
#pragma config CP1 = ON 
#pragma config CP2 = ON 
#pragma config CP3 = ON 
#pragma config CPB = ON 



unsigned char m1,m2,m3,m4;

#define en PORTCbits.RC2
#define rs PORTCbits.RC1

void lcd_string(unsigned char *S);
void lcdinit(void);
void lcdcmd(unsigned char data);
void lcddata(unsigned char data);
void lcdcmd1(unsigned char command);
void lcddata1(unsigned char data);


void lcd_string(unsigned char *S)
{
	while(*S)
    {
    	lcddata(*S);
		S++;
		}
}

 void lcdcmd1(unsigned char command)
{
    PORTDbits.RD4 = (command) & 0x01;		
	PORTDbits.RD5 = (command >> 1 ) & 0x01;	
	PORTDbits.RD6 = (command >> 2)  & 0x01;	
	PORTDbits.RD7 = (command >> 3 ) & 0x01;	
     
	rs=0;
	__delay_ms(1);
	en=1;
	__delay_ms(1);
	en=0;
	
}
void lcdcmd(unsigned char value)
{
    char lowernib=0,highernib=0;
	lowernib = value & 0x0f;					//lower_nibble  = 0x08			
	highernib = value & 0xf0;				//higher_nibble = 0x30		
	highernib = highernib  >>4;	
	lcdcmd1(highernib);
	lcdcmd1(lowernib);
	__delay_ms(10);
}
void lcddata1(unsigned char data)
{
	PORTDbits.RD4 = (data) & 0x1;		    
	PORTDbits.RD5 = (data >> 1 ) & 0x01;	
	PORTDbits.RD6 = (data >> 2)  & 0x01;	
	PORTDbits.RD7 = (data >> 3 ) & 0x01;	
	
    rs=1;
	__delay_ms(1);
	en=1;
	__delay_ms(1);
	en=0;
	
}
void lcddata(unsigned char value)
{
    char lowernib=0,highernib=0;
	lowernib  = value & 0x0f;						
	highernib = value & 0xf0;						
	highernib = highernib  >>4 ;	
	lcddata1(highernib);
	lcddata1(lowernib);
	__delay_ms(20);
}
void lcdinit(void)
{
   	lcdcmd(0x02);
	__delay_ms(5)(50);
	lcdcmd(0x28);
	__delay_ms(5)(50);
	lcdcmd(0x0C);
	lcdcmd(0x06);
    lcdcmd(0x01);
    lcdcmd(0x80);
}



void main(void)
{
OSCCON=0xEF; //EF 4 MHz

ADCON1=0X07;

TRISB=0X00;
TRISC=0x00;
TRISD=0x00;
en=0;

lcdinit();

lcd_string("WC To My REPO");

while(1)
{
    
}        


}

