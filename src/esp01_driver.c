#include<lpc21xx.h>
#include"header.h"
volatile u8 s[512];
volatile u16 i=0;
volatile u8 f=0;

void uart1_rx_handler(void) __irq
{
    while(U1LSR & 0x01)
    {
        s[i++] = U1RBR;

        if(i>=511)
            i=0;
    }

    s[i]=0;

    f=1;

    VICVectAddr=0;
}

void uart1_intr(void)
{
 VICIntSelect=0;
 VICVectCntl0=7|(1<<5);
 VICVectAddr0=(u32)uart1_rx_handler;
 VICIntEnable=(1<<7);
 U1IER=1;
 U1FCR=0x01;
}



void esp01_init()
{
 uart0_tx_string("Ready\r\n");
 uart1_tx_string("AT\r\n");
 while(f==0);
 delay_ms(2000);
 uart0_tx_string((char *)s);	 //wifi is working or not
 i=0;
 f=0;
 //uart0_tx_string("Next\r\n");
 uart1_tx_string("ATE0\r\n");
 while(f==0);
 delay_ms(2000);
 uart0_tx_string((char *)s);	 //wifi is working or not
 i=0;
 f=0;


 esp01_cmd("AT+GMR");
 while(f==0);
 delay_ms(2000);
 uart0_tx_string((char *)s);	 //wifi is working or not
 i=0;
 f=0;

// esp01_cmd("AT+RST");	  //reset wifi
// while(f==0);
// delay_ms(2000);
// uart0_tx_string((char *)s);	 
// i=0;
// f=0;

 

 esp01_cmd("AT+CWMODE=1");			//setting to client mode
 while(f==0);
 delay_ms(2000);
 uart0_tx_string((char *)s);	 //wifi is working or not
 i=0;
 f=0; 	
}



void esp01_cmd(char *cmd)
{
uart1_tx_string(cmd);		   //sending to wifi module
uart1_tx_string("\r\n");
}  


//int wifi_check(void)
//{
//esp01_cmd("AT+CWJAP?");
//memset(s,0,sizeof(s));
//uart0_rx_string(s,100);
//if(strstr(s,"+CWJAP"))
//	return 1;
//return 0;
//}



void esp01_wifi(void)
{

//uart1_tx_string("AT+CWLAP\r\n");
//
//while(f==0);
//delay_ms(2000);
//uart0_tx_string((char *)s);	 
//i=0;
//f=0;

uart1_tx_string("AT+CWJAP=\"realme\",\"98765421\"\r\n");		   //wifi connection

while(f==0);
delay_ms(2000);
uart0_tx_string((char *)s);	 
i=0;
f=0;


esp01_cmd("AT+CIFSR");			//wifi is working or not
 while(f==0);
 delay_ms(2000);
 uart0_tx_string((char *)s);	 
 i=0;
 f=0;

// uart0_tx_string("AT+CWJAP?");
// while(f==0);
// delay_ms(2000);
// uart0_tx_string((char *)s);	 
// i=0;
// f=0;

}


/*
void esp01_server(void)
{
esp01_cmd("AT+CIPMUX=0");
while(f==0);
delay_ms(2000);
uart0_tx_string((char *)s);	 //wifi is working or not
i=0;
f=0;
//delay_ms(2000);
uart1_tx_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");	 //connecting to thingspeak
while(f==0);
delay_ms(2000);
uart0_tx_string((char *)s);	 //wifi is working or not
i=0;
f=0;
  
} */
 /*
 void esp01_server(void)
{
    esp01_cmd("AT+CIPMUX=0");

    delay_ms(1000);
    uart0_tx_string((char *)s);

    i=0;
    f=0;

    uart1_tx_string("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");

    delay_ms(5000);

    uart0_tx_string((char *)s);

    i=0;
    f=0;
}  */


void esp01_send_data(int temp,int hr, int spo2)
{
    char http[200];
    char cmd[30];
	esp01_cmd("AT+CIPMUX=0");
while(f==0);
delay_ms(2000);
uart0_tx_string((char *)s);	 
i=0;
f=0;
//delay_ms(2000);
uart1_tx_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");	 //connecting to thingspeak
while(f==0);
delay_ms(2000);
uart0_tx_string((char *)s);	 
i=0;
f=0;

    sprintf(http,
    "GET /update?api_key=GPQHTW4FDZIUM0S5&field1=%d&field2=%d&field3=%d HTTP/1.1\r\n"
    "Host: api.thingspeak.com\r\n"
    "Connection: close\r\n\r\n",temp,hr,spo2);

    sprintf(cmd,"AT+CIPSEND=%d\r\n",strlen(http));

    uart1_tx_string(cmd);

    delay_ms(3000);

    uart0_tx_string((char *)s);

    i=0;
    f=0;

    uart1_tx_string(http);

    delay_ms(5000);

    uart0_tx_string((char *)s);
}


/*
void esp01_send_data()
{
char http[200];
char cmd[20];
sprintf(http,"GET /update?api_key=GPQHTW4FDZIUM0S5&field1=36.7&field2=96 HTTP/1.1\r\n""Host: api.thingspeak.com\r\n""Connection: close\r\n\r\n");
sprintf(cmd,"AT+CIPSEND=%d\r\n",strlen(http));

uart1_tx_string(cmd);
//while(f==0);
//delay_ms(2000);
//uart0_tx_string((char *)s);	 //wifi is working or not
//i=0;
//f=0;
delay_ms(1000);
uart1_tx_string(http);  //how many characters to send
while(f==0);
delay_ms(2000);
uart0_tx_string((char *)s);	 //wifi is working or not
i=0;
f=0;

}
 */
