#include <LPC21xx.h>

void uart1_init(unsigned int baud)
{
    unsigned int pclk;
    unsigned int result;

    if(VPBDIV==0x00)
        pclk=15000000;
    else if(VPBDIV==0x01)
        pclk=60000000;
    else
        pclk=30000000;

    result=pclk/(16*baud);

    /* P0.8 = TXD1
       P0.9 = RXD1 */

    PINSEL0 &= ~(0xF<<16);
    PINSEL0 |=  (0x5<<16);

    U1LCR=0x83;

    U1DLL=result&0xFF;
    U1DLM=(result>>8)&0xFF;

    U1LCR=0x03;

    U1FCR=0x07;      // Enable FIFO
}


#define THRE ((U1LSR>>5)&1)
void uart1_tx(unsigned char data)
{
U1THR=data;
while(THRE==0);
}


#define RDR (U1LSR&1)
unsigned char uart1_rx(void)
{
while(RDR==0);
return U1RBR;
}


void uart1_tx_string(char *ptr)
{
while(*ptr!=0)
{
uart1_tx(*ptr);
ptr++;
}
}


void uart1_binary(unsigned int num)
{
int pos;
for(pos=7;pos>=0;pos--)
uart1_tx((num>>pos&1)+48);
}


void uart1_rx_string(char *ptr,int len)
{
int i;
for(i=0;i<len;i++)
{
while(RDR==0);
ptr[i]=U1RBR;
if(ptr[i]=='\r')
continue;
if(ptr[i]=='\n')
break;
}
ptr[i]='\0';
}


void uart1_integer(int num)
{
    int a[10];
    int i=0;

    if(num==0)
    {
        uart1_tx('0');
        return;
    }

    if(num<0)
    {
        uart1_tx('-');
        num=-num;
    }

    while(num>0)
    {
        a[i]=num%10;
        num/=10;
        i++;
    }

    while(i>0)
    {
        i--;
        uart1_tx(a[i]+'0');
    }
}


void uart1_float(float f)
{
int num;
if(f==0)
{
uart1_tx_string("0.0");
return;
}
if(f<0)
{
uart1_tx('-');
f=-f;
}
num=f;
uart1_integer(num);
uart1_tx('.');
num=(f-num)*100;
uart1_integer(num);
}
