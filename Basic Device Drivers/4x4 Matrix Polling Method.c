/* Developed By - 
                Anirudh Patil 
*/

#include <p18F4520.h>
#include <string.h>

// Configuration Bits
#pragma config OSC = INTIO67
#pragma config FCMEN = OFF
#pragma config IESO = OFF

#pragma config PWRT = OFF
#pragma config BOREN = OFF
#pragma config BORV = 3

#pragma config WDT = OFF
#pragma config WDTPS = 32768

#pragma config CCP2MX = PORTC
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = OFF

#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config XINST = OFF

#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF

#pragma config CPB = OFF
#pragma config CPD = OFF

#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF

#pragma config WRTC = OFF
#pragma config WRTB = OFF
#pragma config WRTD = OFF

#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF

#pragma config EBTRB = OFF

#define _XTAL_FREQ 4000000

// Keypad Pins
#define ROW1 LATBbits.LATB4
#define ROW2 LATBbits.LATB5
#define ROW3 LATBbits.LATB6
#define ROW4 LATBbits.LATB7

#define COL1 PORTBbits.RB3
#define COL2 PORTBbits.RB2
#define COL3 PORTBbits.RB1
#define COL4 PORTBbits.RB0

// LCD Pins
#define RS LATCbits.LATC1
#define EN LATCbits.LATC2
#define DATA_PORT LATD

// Function Prototypes
void initKeypad(void);
void initLCD(void);
void lcd_cmd(unsigned char command);
void lcd_data(unsigned char data);
void displayCharLCD(char c);
char readKeypad(void);
void MSDelay(unsigned int ms);

const char mydata[] = "Key Pressed:";

void main(void) {
    char key;
    unsigned char z = 0;

    // LCD initialization commands
    for (z = 0; z < 4; z++) {
        lcd_cmd(lcd_cmd[z]);
        MSDelay(2);
    }

    // Initialize keypad and LCD
    initKeypad();
    initLCD();

    // Display first line
    lcd_cmd(0x80);
    MSDelay(2);

    for (z = 0; mydata[z] != '\0'; z++) {
        lcd_data(mydata[z]);
        MSDelay(5);
    }

    // Move cursor to second line
    lcd_cmd(0xC0);

    while (1) {
        key = readKeypad();

        if (key != '\0') {
            lcd_cmd(0x06);
            displayCharLCD(key);
            MSDelay(100);
        }
    }
}

// Initialize keypad
void initKeypad(void) {
    TRISB = 0x0F;
    LATB = 0xF0;
}

// Initialize LCD
void initLCD(void) {
    TRISD = 0x00;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;

    MSDelay(20);

    lcd_cmd(0x38);
    MSDelay(5);

    lcd_cmd(0x0C);
    MSDelay(5);

    lcd_cmd(0x01);
    MSDelay(5);

    lcd_cmd(0x06);
    MSDelay(5);
}

// Send command to LCD
void lcd_cmd(unsigned char command) {

    DATA_PORT = command;
    RS = 0;
    EN = 1;
    MSDelay(2);
    EN = 0;
    MSDelay(2);
}

// Send data to LCD
void lcd_data(unsigned char data) {

    DATA_PORT = data;
    RS = 1;
    EN = 1;
    MSDelay(2);
    EN = 0;
    MSDelay(2);
}

// Display one character
void displayCharLCD(char c) {
    lcd_data(c);
}

// Scan keypad
char readKeypad(void) {
    char key = '\0';

    // Row 1
    ROW1 = 0; ROW2 = 1; ROW3 = 1; ROW4 = 1;
    if (COL1 == 0) key = '1';
    if (COL2 == 0) key = '2';
    if (COL3 == 0) key = '3';
    if (COL4 == 0) key = 'A';
    MSDelay(2);

    // Row 2
    ROW1 = 1; ROW2 = 0; ROW3 = 1; ROW4 = 1;
    if (COL1 == 0) key = '4';
    if (COL2 == 0) key = '5';
    if (COL3 == 0) key = '6';
    if (COL4 == 0) key = 'B';
    MSDelay(2);

    // Row 3
    ROW1 = 1; ROW2 = 1; ROW3 = 0; ROW4 = 1;
    if (COL1 == 0) key = '7';
    if (COL2 == 0) key = '8';
    if (COL3 == 0) key = '9';
    if (COL4 == 0) key = 'C';
    MSDelay(2);

    // Row 4
    ROW1 = 1; ROW2 = 1; ROW3 = 1; ROW4 = 0;
    if (COL1 == 0) key = '*';
    if (COL2 == 0) key = '0';
    if (COL3 == 0) key = '#';
    if (COL4 == 0) key = 'D';
    MSDelay(2);

    // Reset rows
    ROW1 = 1;
    ROW2 = 1;
    ROW3 = 1;
    ROW4 = 1;

    return key;
}

// Millisecond delay
void MSDelay(unsigned int ms) {
    unsigned int i, j;

    for (i = 0; i < ms; i++)
        for (j = 0; j < 135; j++);
}