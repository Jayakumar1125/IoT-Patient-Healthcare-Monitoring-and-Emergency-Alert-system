#include <LPC21xx.H>
#include"header.h"
//LCD data
void lcd_data(unsigned char data)
{
unsigned int temp;
IOCLR1|=0XFE<<16;
temp=(data&0xF0)<<16;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1|=0XFE<<16;
temp=(data&0x0F)<<20;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}
//LCD cmd
void lcd_cmd(unsigned char cmd)
{
unsigned int temp;
IOCLR1|=0XFE<<16;
temp=(cmd&0xF0)<<16;
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1=0XFE<<16;
temp=(cmd&0x0F)<<20;
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}
//LCD Init
void lcd_init()
{
    PINSEL2 = 0x00000000; 
    PINSEL2 |= 0x00000001;
    IODIR1  |= 0xFE<<16;
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0e);
    lcd_cmd(0x01);
}
//LCD String
void lcd_string(char *ptr)
{
while(*ptr!='\0')
{
lcd_data(*ptr);
ptr++;
}
}
//LCD String
void lcd_integer(int num)
{
int a[10],i;
if(num==0)
{
lcd_data('0');
}
if(num<0)
{
num=-num;
lcd_data('-');
}
i=0;
while(num>0)
{
a[i]=(num%10+48);
num=num/10;
i++;
}
for(i=i-1;i>=0;i--)
{
lcd_data(a[i]);
}
}
//LCD Float
void lcd_float(float f)
{
int num;
if(f<0)
{
lcd_data('-');
f=-f;
}
if(f==0)
{
lcd_string("0.0");
return;
}
num=(int)f;
lcd_integer(num);
lcd_data('.');
num = (int)((f - (int)f) * 100);
lcd_integer(num);
}
