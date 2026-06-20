#include <xc.h>

#pragma config OSC = INTIO67
#pragma config PWRT = ON
#pragma config BOREN = OFF
#pragma config WDT = OFF
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

#define LED PORTBbits.RB0

// Function Prototype
void TMR2_delay(void);

void main(void)
{
    OSCCON = 0XEF;
    TRISB = 0x00;

    PR2 = 200;
    T2CON = 0x00;

    TRISDbits.RD6 = 0;

    while (1)
    {
        LED = 1;
        TMR2_delay();

        LED = 0;
        TMR2_delay();
    }

}   // End of main()

// Timer2 delay routine
void TMR2_delay(void)
{
    TMR2 = 0;
    TMR2IF = 0;
    TMR2ON = 1;

    while (TMR2IF == 0);

    TMR2ON = 0;
    TMR2IF = 0;
}