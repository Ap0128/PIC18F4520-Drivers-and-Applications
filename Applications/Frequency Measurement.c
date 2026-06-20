#include <xc.h>

#pragma config OSC = INTIO67
#pragma config PWRT = OFF
#pragma config BOREN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON
#pragma config LVP = OFF
#pragma config PBADEN = OFF
#pragma config CPD = ON
#pragma config DEBUG = OFF
#pragma config CP0 = ON
#pragma config CP1 = ON
#pragma config CP2 = ON
#pragma config CP3 = ON
#pragma config CPB = ON

// LCD Control Pins
#define en PORTCbits.RC3
#define rs PORTCbits.RC1
#define rw1 PORTCbits.RC2

// Function Prototypes
void lcd_string(unsigned char *S);
void lcdinit(void);
void lcdcmd(unsigned char data);
void lcddata(unsigned char data);
void Timer0ISR(void);
void digit_separate(unsigned int temp1);

unsigned int frequency;
unsigned char m1, m2, m3, m4;

#define _XTAL_FREQ 4000000

// Display string on LCD
void lcd_string(unsigned char *S)
{
    while (*S)
    {
        lcddata(*S);
        S++;
    }
}

// Send command to LCD
void lcdcmd(unsigned char data)
{
    PORTD = data;
    en = 0;
    rs = 0;
    __delay_ms(1);
    en = 1;
    __delay_ms(1);
    en = 0;
}

// Send data to LCD
void lcddata(unsigned char data)
{
    PORTD = data;
    en = 0;
    rs = 1;
    __delay_ms(1);
    en = 1;
    __delay_ms(1);
    en = 0;
}

// Initialize LCD
void lcdinit(void)
{
    lcdcmd(0x01);
    __delay_ms(70);

    lcdcmd(0x38);
    __delay_ms(1);

    lcdcmd(0x0E);
    __delay_ms(1);

    lcdcmd(0x06);
    __delay_ms(1);

    lcdcmd(0x80);
}

void main(void)
{
    OSCCON = 0xEF;      // 4 MHz Internal Oscillator
    ADCON1 = 0X0F;

    TRISB = 0X00;
    TRISC = 0x01;
    TRISD = 0x00;

    T0CON = 0X04;
    T1CON = 0x02;

    lcdinit();
    lcd_string("RIT WELCOMES YOU");
    __delay_ms(1000);

    while (1)
    {
        TMR1L = 0;
        TMR1H = 0;

        TMR1ON = 1;
        Timer0ISR();      // Generate 1-second delay
        TMR1ON = 0;

        frequency = TMR1H;
        frequency = frequency << 8;
        frequency = frequency | TMR1L;

        lcdcmd(0x01);
        lcd_string("Frequency");

        digit_separate(frequency);

        lcdcmd(0xC0);
        lcddata(m4);
        lcddata(m3);
        lcddata(m2);
        lcddata(m1);
        lcd_string(" Hz");

        __delay_ms(2000);
    }
}

// Timer0 delay routine
void Timer0ISR(void)
{
    INTCONbits.TMR0IF = 0;

    TMR0H = 0x85;
    TMR0L = 0xED;

    T0CONbits.TMR0ON = 1;

    while (TMR0IF == 0)
    {
    }

    T0CONbits.TMR0ON = 0;
}

// Convert integer to ASCII digits
void digit_separate(unsigned int temp1)
{
    unsigned int tmp;
    unsigned char y;

    m1 = temp1 % 10;
    tmp = temp1 / 10;
    m2 = tmp % 10;
    y = tmp / 10;
    m3 = (y % 10);
    m4 = (y / 10);

    m1 = m1 + 0x30;
    m2 = m2 + 0x30;
    m3 = m3 + 0x30;
    m4 = m4 + 0x30;
}