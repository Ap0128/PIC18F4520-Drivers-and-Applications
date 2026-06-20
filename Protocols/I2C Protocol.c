// I2C Interface with PCF8575 and LCD

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

#define _XTAL_FREQ 4000000

// Function Prototypes
void lcd_string(unsigned char *S);
void lcdinit(void);
void lcdcmd(unsigned char data);
void lcddata(unsigned char data);
void I2C_Init(const unsigned long c);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_RepeatedStart(void);
void I2C_Stop(void);
void I2C_Write(unsigned d);
unsigned short I2C_Read(void);

// PCF8575 Connections
// LCD Data  -> P0 Port of PCF8575
// LCD RS    -> P11 Port Pin of PCF8575
// LCD EN    -> P10 Port Pin of PCF8575
// Slave Address: 0x40 (Write), 0x41 (Read)

void I2C_Init(const unsigned long c)
{
    SSPCON1 = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ / (4 * c)) - 1;
    TRISCbits.TRISC3 = 1;    // SCL
    TRISCbits.TRISC4 = 1;    // SDA
}

void I2C_Wait(void)
{
    while ((SSPSTATbits.R == 1) | (SSPCON2 & 0x0C));
}

void I2C_Start(void)
{
    I2C_Wait();
    SSPCON2bits.SEN = 1;
}

void I2C_RepeatedStart(void)
{
    I2C_Wait();
    SSPCON2bits.RSEN = 1;
}

void I2C_Stop(void)
{
    I2C_Wait();
    SSPCON2bits.PEN = 1;
}

void I2C_Write(unsigned d)
{
    I2C_Wait();
    SSPBUF = d;
}

unsigned short I2C_Read(void)
{
    unsigned short temp;

    I2C_Wait();
    SSPCON2bits.RCEN = 1;
    I2C_Wait();

    temp = SSPBUF;

    I2C_Wait();
    SSPCON2bits.ACKEN = 1;

    return temp;
}

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
    I2C_Start();
    I2C_Write(0x40);
    I2C_Write(data);
    I2C_Write(0xF0);

    I2C_Write(data);
    I2C_Write(0xF1);

    I2C_Write(data);
    I2C_Write(0xF0);

    I2C_Stop();
}

// Send data to LCD
void lcddata(unsigned char data)
{
    I2C_Start();
    I2C_Write(0x40);
    I2C_Write(data);
    I2C_Write(0xF2);

    I2C_Write(data);
    I2C_Write(0xF3);

    I2C_Write(data);
    I2C_Write(0xF2);

    I2C_Stop();
}

// Initialize LCD
void lcdinit(void)
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

void main(void)
{
    OSCCON = 0xEF;     // 4 MHz Internal Oscillator

    TRISC = 0x00;
    TRISD = 0x00;

    TRISCbits.TRISC3 = 1;    // SCL
    TRISCbits.TRISC4 = 1;    // SDA

    __delay_ms(50);

    I2C_Init(100000);

    lcdinit();
    lcd_string("Welcome to REPO");

    while (1)
    {

    }
}