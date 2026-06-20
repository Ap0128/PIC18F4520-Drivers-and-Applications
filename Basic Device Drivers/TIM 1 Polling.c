#include <xc.h>

#pragma config OSC = INTIO67
#pragma config PWRT = OFF        // power up timer enabled
#pragma config BOREN= OFF   // Brown-out Reset enabled in hardware only (SBOREN is disabled) 
#pragma config WDT  = OFF       // WDT disabled
#pragma config MCLRE= OFF 
#pragma config LVP  = OFF 
#pragma config PBADEN  = OFF 
#pragma config CPD = ON
#pragma config DEBUG = OFF 
#pragma config CP0 = ON 
#pragma config CP1 = ON 
#pragma config CP2 = ON 
#pragma config CP3 = ON 
#pragma config CPB = ON 


#define led1 PORTBbits.RB0
#define led2 PORTBbits.RB1
#define led3 PORTBbits.RB2
#define led4 PORTBbits.RB3

void Timer1ISR(void);

void main(void)
{
OSCCON=0xEF; //EF 4 MHz

TRISB=0X00;

T1CON=0X00;
PIR1bits.TMR1IF=0;

led1=0;
led2=0;
led3=0;
led4=0;

while(1)
{
Timer1ISR();
led1=~led1;
led2=~led2;
led3=~led3;
led4=~led4;

}        
    
}

void Timer1ISR(void)
{
PIR1bits.TMR1IF=0;
TMR1H=0xB1;
TMR1L=0xDF;
T1CONbits.TMR1ON=1;
while(TMR1IF==0)
{
}
T1CONbits.TMR1ON=0;

}