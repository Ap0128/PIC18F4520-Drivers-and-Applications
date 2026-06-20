/* Developed By - 
                Anirudh Patil 
*/

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

#define _XTAL_FREQ 4000000

unsigned char data;

void mem_wrt(unsigned char,unsigned char);
unsigned char mem_rd(unsigned char);

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////
unsigned char mem_rd(unsigned char addr)
{
	EEADR=addr;
	EECON1bits.EEPGD=0;
	EECON1bits.CFGS=0;
	EECON1bits.RD=1;
	return(EEDATA);
		
}

//////////////////////******************
void mem_wrt(unsigned char addr,unsigned char data)
{
INTCONbits.GIE=0;
EEADR=addr;
EEDATA=data;
EECON1bits.EEPGD=0;
EECON1bits.CFGS=0;
EECON1bits.WREN=1;
EECON2=0X55;
EECON2=0XAA;
EECON1bits.WR=1;
INTCONbits.GIE=1;
}

//////////////////////////////////////////////////////////////////////
void main(void)
{
OSCCON=0xEF; //EF 4 MHz

TRISC=0x00;
__delay_ms(500);

mem_wrt(0x20,0xBC);
data= mem_rd(0x20);
PORTC=data;

while(1)
{
    
}        
    
}

