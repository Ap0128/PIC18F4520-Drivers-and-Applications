#include <xc.h>

#pragma config OSC = INTIO67
#pragma config PWRT = OFF  // power up timer enabled
#pragma config BOREN = OFF // Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config WDT = OFF   // WDT disabled
#pragma config MCLRE = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF
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

void Timer0ISR(void);

void main(void)
{
    OSCCON = 0xEF; 

    TRISB = 0X00;

    T0CON = 0X03;

    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;

    while (1)
    {
        Timer0ISR();
        led1 = ~led1;
        led2 = ~led2;
        led3 = ~led3;
        led4 = ~led4;
    }

}

void Timer0ISR(void)
{
    INTCONbits.TMR0IF = 0;
    TMR0H = 0x0B;
    TMR0L = 0xDB;
    T0CONbits.TMR0ON = 1;
    while (TMR0IF == 0)
    {
    }
    T0CONbits.TMR0ON = 0;
}