/* Developed By - 
                Anirudh Patil 
*/

#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#pragma config OSC = INTIO67
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF       // Oscillator Switchover mode disabled
#pragma config PWRT = ON        // power up timer enabled
#pragma config BOREN= OFF   // Brown-out Reset enabled in hardware only (SBOREN is disabled) 
#pragma config WDT  = OFF       // WDT disabled
//#pragma config WDTPS =32768
#pragma config MCLRE= OFF  
#pragma config STVREN = OFF   
#pragma config LVP  = OFF 
#pragma config PBADEN  = OFF 
#pragma config EBTR0   = OFF 
#pragma config EBTR1   = OFF 
#pragma config EBTR2   = OFF
#pragma config EBTR3   = OFF
#pragma config EBTRB   = OFF 
#pragma config WRTD    = OFF 
#pragma config CPD = ON
#pragma config DEBUG = OFF 
#pragma config CP0 = ON 
#pragma config CP1 = ON 
#pragma config CP2 = ON 
#pragma config CP3 = ON 
#pragma config CPB = ON 
#pragma config CCP2MX=PORTBE

#define BLUE PORTDbits.RD0
#define PINK PORTDbits.RD1
#define YELLOW PORTDbits.RD2
#define ORANGE PORTDbits.RD3


#define _XTAL_FREQ 4000000


void main(void)
{
    

OSCCON=0xEF; //EF 4 MHz

ADCON1=0X0F;
TRISB=0X00;
TRISD=0X00;
PORTB=0x00;
PORTD=0x00;

unsigned int j;



 for(j=1;j<260;j++)
    {
    
    BLUE=1;  
    PINK=1;   
    YELLOW=0;   
    ORANGE=0;   
     __delay_ms(10);
    BLUE=0;  
    PINK=1;   
    YELLOW=0;   
    ORANGE=0;   
 __delay_ms(10);
    BLUE=0;   
    PINK=1;
    YELLOW=1;
    ORANGE=0;
     __delay_ms(10);
    BLUE=0;   
    PINK=0;
    YELLOW=1;
    ORANGE=0;
    __delay_ms(10);
     BLUE=0;
    PINK=0;
    YELLOW=1;
    ORANGE=1;
     __delay_ms(10);
    BLUE=0;
    PINK=0;
    YELLOW=0;
    ORANGE=1;
    __delay_ms(10);
     
    BLUE=1;
    PINK=0;
    YELLOW=0;
    ORANGE=1;
     __delay_ms(10);
     
    BLUE=1;
    PINK=0;
    YELLOW=0;
    ORANGE=0;
     __delay_ms(10);
    }


    BLUE=0;
    PINK=0;
    YELLOW=0;
    ORANGE=0;
while(1)
  {


}
    

}