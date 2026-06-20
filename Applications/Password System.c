#include <xc.h>
#include <string.h>

#pragma config OSC = INTIO67
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF  // Oscillator Switchover mode disabled
#pragma config PWRT = ON   // power up timer enabled
#pragma config BOREN = OFF // Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config WDT = OFF   // WDT disabled
#pragma config MCLRE = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
#pragma config WRTD = OFF
#pragma config CPD = ON
#pragma config DEBUG = OFF
#pragma config CP0 = ON
#pragma config CP1 = ON
#pragma config CP2 = ON
#pragma config CP3 = ON
#pragma config CPB = ON
#pragma config CCP2MX = PORTBE

#define C1 PORTBbits.RB0
#define C2 PORTBbits.RB1
#define C3 PORTBbits.RB2
#define C4 PORTBbits.RB3

#define en PORTCbits.RC2
#define rs PORTCbits.RC1
#define rw1 PORTCbits.RC3

#define R1 PORTBbits.RB4
#define R2 PORTBbits.RB5
#define R3 PORTBbits.RB6
#define R4 PORTBbits.RB7

int key_detect(void);
void lcd_string(unsigned char *Spointer);
void lcdinit(void);
void lcdcmd(unsigned char data);
void lcddata(unsigned char data);
int pass_detect(int a, int b, int c, int d)

#define _XTAL_FREQ 4000000

    void lcd_string(unsigned char *Spointer)
{

    while (*Spointer)
    {
        lcddata(*Spointer);
        Spointer++;
    }
}

void lcdcmd(unsigned char command) // Send LCD Commands
{
    PORTD = command;
    rs = 0;
    en = 1;
    __delay_ms(1);
    en = 0;
}

void lcddata(unsigned char data) // Write ASCII data to LCD
{
    PORTD = data;
    rs = 1;
    en = 1;
    __delay_ms(1);
    en = 0;
}

void lcdinit(void) // LCD initialization
{
    lcdcmd(0x01);
    __delay_ms(80);
    lcdcmd(0x38);
    __delay_ms(10);
    lcdcmd(0x0C);
    __delay_ms(10);
    lcdcmd(0x06);
    __delay_ms(10);
    lcdcmd(0x80);
}

int key_detect(void)
{
    lcdcmd(0xC0);

    while (1)
    {
        // scan row1
        R1 = 0;
        R2 = 1;
        R3 = 1;
        R4 = 1;

        if (C1 == 0)
        {
            lcdcmd(0x80);
            lcddata('1');
            return 1;
        }
        if (C2 == 0)
        {
            lcdcmd(0x80);
            lcddata('2');
            return 2;
        }
        if (C3 == 0)
        {
            lcdcmd(0x80);
            lcddata('3');
            return 3;
        }

        // scan row2
        R1 = 1;
        R2 = 0;
        R3 = 1;
        R4 = 1;

        if (C1 == 0)
        {
            lcdcmd(0x80);
            lcddata('4');
            return 4;
        }
        if (C2 == 0)
        {
            lcdcmd(0x80);
            lcddata('5');
            return 5;
        }
        if (C3 == 0)
        {
            lcdcmd(0x80);
            lcddata('6');
            return 6;
        }
        
        // scan row3
        R1 = 1;
        R2 = 1;
        R3 = 0;
        R4 = 1;

        if (C1 == 0)
        {
            lcdcmd(0x80);
            lcddata('7');
            return 7;
        }
        if (C2 == 0)
        {
            lcdcmd(0x80);
            lcddata('8');
            return 8;
        }
        if (C3 == 0)
        {
            lcdcmd(0x80);
            lcddata('9');
            return 9;
        }
        
        // scan row4
        R1 = 1;
        R2 = 1;
        R3 = 1;
        R4 = 0;

        if (C1 == 0)
        {
            lcdcmd(0x80);
            lcddata('*');
            return -1;
        }
        if (C2 == 0)
        {
            lcdcmd(0x80);
            lcddata('0');
            return 0;
        }
        if (C3 == 0)
        {
            lcdcmd(0x80);
            lcddata('#');
            return -1;
        }
    }
    __delay_ms(500);
}


int pass_detect(int a, int b, int c, int d)
{
    int final_num = (a * 1000) + (b * 100) + (c * 10) + d;
    return final_num;
}

void main(void)
{

    OSCCON = 0xEF; // Clk Frequency = 4 MHz
    ADCON1 = 0X0F;
    TRISD = 0X00;
    TRISB = 0X0F;
    TRISC = 0X00;
    PORTD = 0X00;
    PORTC = 0X00;
    rw1 = 0;

    R1 = 0;
    R2 = 0;
    R3 = 0;
    R4 = 0;
    int a, b, c, d;
    lcdinit();
    lcd_string("WC To My REPO");
    __delay_ms(2000);
    while (1)
    {
        lcdcmd(0x00);
        lcdcmd(0x80);
        lcd_string("ENTER YOUR 4 DIGIT PASS");
        a = key_detect();
        __delay_ms(700);
        b = key_detect();
        __delay_ms(700);
        c = key_detect();
        __delay_ms(700);
        d = key_detect();
        __delay_ms(50);
        int pass = pass_detect(a, b, c, d);
        if (pass == 1234)
        {
            lcdcmd(0x01);
            lcdcmd(0x80);
            lcd_string("PASS IS CORRECT..");
            __delay_ms(2000);
        }
        else
        {
            lcdcmd(0x01);
            lcdcmd(0xC0);
            lcd_string("PASS IS INCORRECT..");
            __delay_ms(2000);
        }
    }
}