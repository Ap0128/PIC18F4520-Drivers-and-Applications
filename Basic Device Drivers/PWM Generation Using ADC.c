/* Developed By - 
                Anirudh Patil 
*/

#include<XC.h>
#include<string.h>
#include<stdio.h>

#pragma config OSC = INTIO67
#pragma config FCMEN = OFF       
#pragma config IESO = OFF       
#pragma config PWRT = ON        
#pragma config BOREN= OFF    
#pragma config WDT  = OFF      
#pragma config MCLRE= OFF  
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

#define _XTAL_FREQ 4000000

void atod(void);

void main(void)
{
    OSCCON=0XEF;
    
    ADCON0=0X01;
    ADCON1=0X0E;
    ADCON2=0X24;
    TRISAbits.TRISA0=1;
    
    TRISC=0X00;
    
     __delay_ms(1000);
    
     CCP1CON=0X1C;
     CCPR1L=0X1F;
     PR2=124;
     T2CON=0X03;
     TMR2ON=1;
     
     unsigned char data;
     
    
    while(1)
    {
        atod();
        
        CCPR1L = ADRESH;
        data = ADRESL;
        data = data >> 2;
        CCP1CON = data | CCP1CON;
        __delay_ms(1000);
        
    }
 }
void  atod(void)
{
    
    
    ADCON0bits.GO=1;
    
    while(ADCON0bits.GO==1);
    
}