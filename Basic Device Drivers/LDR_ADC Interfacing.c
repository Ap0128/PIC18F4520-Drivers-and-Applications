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

unsigned char m1,m2,m3,m4;

#define en PORTCbits.RC2
#define rs PORTCbits.RC1
#define rw PORTCbits.RC3
#define relay PORTCbits.RC0
#define button PORTBbits.RB0


void lcd_string(unsigned char *S);
void lcdinit(void);
void lcdcmd(unsigned char data);
void lcddata(unsigned char data);
unsigned int atod(void);
void modulo_division(unsigned int temp1);



///////////////////////////////////////////////////////////////////////////////////

void lcd_string(unsigned char *S)
{
	while(*S)
    {
    	lcddata(*S);
		S++;
		}
}
//////////////////////////////////////

void lcdcmd(unsigned char data)
{
	PORTD=data;
	rs=0;
	en=1;
	__delay_ms(1);
	en=0;
	
}

////////////////////////////////////////////////////
void lcddata(unsigned char data)
{
	PORTD=data;
	rs=1;
	en=1;
	__delay_ms(1);
	en=0;
}
////////////////////////////////////////////////////
void lcdinit(void)
{
	
	lcdcmd(0x01);
	__delay_ms(80);
	lcdcmd(0x38);
	__delay_ms(10);
    lcdcmd(0x0E);
	__delay_ms(10);
	lcdcmd(0x06);
	__delay_ms(10);
	lcdcmd(0x80);

}
//////////////////////////////////////////////////////////////////

void main(void)
{
OSCCON=0xEF; //EF 4 MHz

ADCON0=0X01;
ADCON1=0X07;
ADCON2=0XA4;
TRISAbits.TRISA0=1;
TRISB=0X01;
TRISC=0x00;
TRISD=0x00;
rw = 0;
__delay_ms(10);

lcdinit();
lcd_string("RIT WELCOMES YOU");
__delay_ms(1000);
 
unsigned int LIGHT,counter;
lcdinit();
lcd_string("Ligt:");
while(1)
{
    lcdcmd(0x01);
    lcdcmd(0x80);
    lcd_string("Ligt:");
    LIGHT=atod();
    modulo_division(LIGHT);
    lcddata(m4);
    lcddata(m3);
    lcddata(m2);
    lcddata(m1);
    
    lcdcmd(0xC0);
    
    if(relay==1)
    {
    lcd_string("Light ON");
    }
    else
      {
    lcd_string("Light OFF");
    }  
    
    if(LIGHT>=819 && button==0)
    {
        lcdcmd(0x01);
        lcdcmd(0xC0);
         lcd_string("Light ON");
        relay=1;
        for(counter=1;counter<=10;counter++)
        {
        __delay_ms(1000);
        if(button==0)
        {
            
            lcdcmd(0xC0);
            lcd_string("Motion Detected");
            counter=1;
        }
        
    }
     relay=0;
   
    }        
    __delay_ms(2000);
}
}

///////////////////////////////////////////////////
unsigned int atod(void)
{
    unsigned int VR;
	ADCON0=0X01;   //channel AN0
	ADCON0bits.GO=1;
	while(ADCON0bits.DONE==1);
		
   VR=ADRESH;
   VR=(VR << 8) | ADRESL;

   return (VR);
}
/////////////////////////////////
void modulo_division(unsigned int data)
{
unsigned int tmp;
unsigned char y;

m1=data%10;
tmp=data/10;
m2=tmp%10;
y=tmp/10;
m3=(y%10);
m4=(y/10);

m1=m1+0x30;
m2=m2+0x30;
m3=m3+0x30;
m4=m4+0x30;


}

