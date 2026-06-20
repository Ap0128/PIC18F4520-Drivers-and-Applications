#include<xc.h>


#pragma config OSC = INTIO67
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF       // Oscillator Switchover mode disabled
#pragma config PWRT = ON        // power up timer enabled
#pragma config BOREN= OFF   // Brown-out Reset enabled in hardware only (SBOREN is disabled) 
#pragma config WDT  = OFF       // WDT disabled
#pragma config MCLRE= OFF  
#pragma config LVP  = OFF 
#pragma config WRTD    = OFF 
#pragma config CPD = OFF
#pragma config DEBUG = OFF 
#pragma config CP0 = ON 
#pragma config CP1 = ON 
#pragma config CP2 = ON 
#pragma config CP3 = ON 
#pragma config CPB = ON 

#define _XTAL_FREQ 4000000
#define en PORTCbits.RC2
#define rs PORTCbits.RC1


unsigned char m1,m2,m3,m4,m5;


void lcd_string(unsigned char *S);
void lcdinit(void);
void lcdcmd(unsigned char data);
void lcddata(unsigned char data);
void I2C_Init(const unsigned long c);
void I2C_Wait(void);
void I2C_Start();
void I2C_RepeatedStart(void);
void I2C_Stop(void);
void I2C_Write(unsigned d);
unsigned short I2C_Read(void);
void modulo_division(unsigned int data16bit);

void I2C_Init(const unsigned long c)
{
  SSPCON1 = 0b00101000;
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  SSPSTAT = 0;
  TRISCbits.RC3 = 1	;	//INPUT DIR OF RC3
  TRISCbits.RC4 = 1	;	//INPUT DIR OF RC4
}

void I2C_Wait()
{
    while ((SSPSTATbits.R==1) | (SSPCON2 & 0x0C));  //R=1 transmission is in progress
}                                                                                  //SEN=1 Initiates Start Condition on SDA/SCL pins

void I2C_Start()
{
  I2C_Wait();
  SSPCON2bits.SEN=1;          //Initiates start condition
}

void I2C_RepeatedStart()
{
  I2C_Wait();
	SSPCON2bits.RSEN=1; //Initiates repeated start condition
 }

void I2C_Stop()
{
  I2C_Wait();
	SSPCON2bits.PEN=1;   //Stops I2C cycle.
}

void I2C_Write(unsigned d)
{
  I2C_Wait();
  SSPBUF = d;                //write data to SSPBUF
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

void DelayUs(unsigned int l)
{
int i;
for(i=0;i<l;i++);
}  

void lcd_string(unsigned char *S)
{
	while(*S)
    {
    	lcddata(*S);
		S++;
		}
}

void lcdcmd(unsigned char data)
{
	PORTD=data;
	rs=0;
	__delay_ms(1);
	en=1;
    __delay_ms(1);
	en=0;
}

void lcddata(unsigned char data)
{
	PORTD=data;
	rs=1;
	__delay_ms(1);
	en=1;
	__delay_ms(1);
	en=0;
}

void lcdinit(void)
{
	lcdcmd(0x01);
	__delay_ms(50);
	lcdcmd(0x38);
	__delay_ms(2);
	lcdcmd(0x0C);
	__delay_ms(2);
	lcdcmd(0x06);
	__delay_ms(2);
	lcdcmd(0x80);

}


void main(void)
{


unsigned int data,hfield,diff;

OSCCON=0XEF;
ADCON1=0X07;
TRISD=0x00;
TRISC=0x00;

lcdinit(); 
lcd_string("ATC WELCOMES YOU");
__delay_ms(1500);


    I2C_Init(100000);      //Initialize I2C Master with 100KHz clock
  
    I2C_Start();  
    I2C_Write(0x90);	//7 bit address + Write
	I2C_Write(0x01);    //points to config register
	I2C_Write(0xC2); // MSB byte write to Config register
	I2C_Write(0x43);   //LBS byte write to Config register
	I2C_Stop(); 

    I2C_Start();  
	//I2C_RepeatedStart();        //Start condition
    I2C_Write(0x90);	//7 bit address + Write
   	I2C_Write(0x00);
	I2C_Stop();

    lcdinit();
    
while(1)
  {
    I2C_Start();
	//I2C_RepeatedStart();         //Start condition
    I2C_Write(0x91);
	data= I2C_Read();
	data=data<< 8;
	data|= I2C_Read();
	I2C_Stop();
	
   
   

   if(data>=19760)
   {
   diff=data-19760;
   }
   else
   {
   diff=19760-data;
   }
   
    
   hfield=diff/13;
   
   if(hfield>=1000)
   {
       hfield=1000;
   }
   if(hfield<=100)
   {
       hfield=0;
   }
   
   lcdcmd(0x01);
   __delay_ms(20);
   lcdcmd(0x80);
   lcd_string("H Field=");
   
modulo_division(hfield);

if(m4!=0x30)
{
lcddata(m4);
}

if(m4==0x30 && m3==0X30)
{
}
else
{
lcddata(m3);
}
if(m4==0x30 && m3==0X30)
{
}
else
{
lcddata(m2);
}
lcddata(m1);

lcd_string(" GS");
lcdcmd(0xC0);
if(data>23000)
{
lcd_string("SOUTH POLE DETC");
}
else if (data<17500)
{
lcd_string("NORTH POLE DETC");
}
  
__delay_ms(2000);  
       
}

   
 }



void modulo_division(unsigned int data16bit)
{
unsigned int tmp,y1,y2;
m1=data16bit%10;
tmp=data16bit/10;
m2=tmp%10;
y1=tmp/10;
m3=(y1%10);
y2=(y1/10);
m4=y2%10;
m5=y2/10;

m1=m1+0x30;
m2=m2+0x30;
m3=m3+0x30;
m4=m4+0x30;
m5=m5+0x30;
}
