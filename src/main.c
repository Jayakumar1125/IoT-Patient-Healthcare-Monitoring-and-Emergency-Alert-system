#include <LPC21xx.H>
#include "header.h"
#include "max30102.h"
#include "filter.h"
#include "heartrate.h"
#include "spo2.h"

MAX30102_Data sensor;

s16 ir_filtered;

#define TEMP_LIMIT 38
#define HR_LOW     60
#define HR_HIGH    120
#define SPO2_LIMIT 95

#define GREEN_LED 17
#define RED_LED   18
#define BUZZER    21

int temp = 0;
u16 hr = 0;
u8 spo2 = 0;

int main(void)
{
	char data[100];
    unsigned char t_int;
    unsigned char dht_ok;

    u16 startup_count = 0;
    u16 sensor_count  = 0;
    u16 wifi_count    = 0;

    /* UART */
    uart0_init(9600);
    uart1_init(9600);

	uart1_intr();
//	esp01_init();
//	delay_ms(2000);
	//esp01_wifi();
    /* LCD */
    lcd_init();

    /* GPIO */
    gpio_init();

    /* Welcome Screen */
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    uart0_tx_string("PATIENT HEALTH");
    lcd_cmd(0xC0);
    uart0_tx_string("MONITORING\r\n");
    delay_ms(1500);

    /* Sensors */
   lcd_cmd(0x01);
uart0_tx_string("DHT\r\n");
delay_ms(1000);

dht11_init();

lcd_cmd(0x01);
lcd_string("I2C");
delay_ms(1000);

i2c_init();

lcd_cmd(0x01);
uart0_tx_string("MAX\r\n");
delay_ms(1000);

MAX30102_Init();

lcd_cmd(0x01);
lcd_string("FILTER");
delay_ms(1000);

Filter_Init();

lcd_cmd(0x01);
lcd_string("HR");
delay_ms(1000);

HeartRate_Init();

lcd_cmd(0x01);
lcd_string("SPO2");
delay_ms(1000);

SpO2_Init();

lcd_cmd(0x01);
lcd_string("ESP INIT");
uart0_tx_string("esp init\r\n");
delay_ms(1000);

esp01_init();

lcd_cmd(0x01);
lcd_string("ESP WIFI");
uart0_tx_string("esp wifi\r\n");
delay_ms(1000);
esp01_wifi();

lcd_cmd(0x01);
lcd_string("DONE");
	uart0_tx_string("donewifi\r\n");
delay_ms(1000);


    while(1)
    {
        /************ MAX30102 ************/
        MAX30102_ReadFIFO(&sensor);

        ir_filtered = DC_Remove(sensor.ir);
       ir_filtered = Moving_Average(ir_filtered);

       HeartRate_Process(ir_filtered);
       SpO2_Process(sensor.red, sensor.ir);

        hr   = Get_BPM();
        spo2 = Get_SpO2();

        sensor_count++;

        /************ Every 1 Second ************/
        if(sensor_count >= 100)
        {
            sensor_count = 0;

            /* Read Temperature */
            dht_ok = dht11_read(&t_int);

            if(dht_ok)
                temp = t_int;

            /* Update LCD */
            lcd_display(temp, hr, spo2);
			sprintf(data,"temp:%d\r\nheart rate:%d\r\nspo2:%d\r\n",temp,hr,spo2);
			uart0_tx_string(data);

			//esp01_server();
			//esp01_send_data(temp,hr,spo2);

            /* Ignore alarms for first 10 seconds */
            if(startup_count < 10)
            {
                startup_count++;
            }
            else
            {
                check_condition(temp, hr, spo2);
            }
        }

        /************ Every 20 Seconds ************/
wifi_count++;

if(wifi_count >= 2000)      // 2000 × 10 ms = 20 seconds
{
    wifi_count = 0;

    //esp01_server();
    esp01_send_data(temp, hr, spo2);
}
        delay_ms(10);
    }
}
//GPIO Init Function
void gpio_init(void)
{
    IODIR0 |= (1<<GREEN_LED)|(1<<RED_LED)|(1<<BUZZER);
    IOSET0  = (1<<GREEN_LED)|(1<<RED_LED);
    IOCLR0  = (1<<BUZZER);
}

//LCD Display Function
void lcd_display(int t,u32 hr,u8 sp)
{
  //  lcd_cmd(0x01);
    lcd_cmd(0x80);
    lcd_string("T:");
    lcd_integer(t);
	  lcd_string("c");
    lcd_string(" Hr:");
    lcd_integer(hr);
    lcd_cmd(0xC0);
    lcd_string("Spo2:");
    lcd_integer(sp);
    lcd_data('%');
		
}

void check_condition(int t, u32 hr, u8 sp)
{
    if( (t > TEMP_LIMIT) ||
        (hr != 0 && (hr < HR_LOW || hr > HR_HIGH)) ||
        (sp != 0 && sp < SPO2_LIMIT) )
    {
        IOSET0 = (1<<GREEN_LED);
        IOCLR0 = (1<<RED_LED);

        IOSET0 = (1<<BUZZER);
        delay_ms(50);
        IOCLR0 = (1<<BUZZER);

        lcd_cmd(0x01);

        lcd_cmd(0x80);

        if(t > TEMP_LIMIT)
            lcd_string("TEMP ");

        if(hr != 0 && (hr < HR_LOW || hr > HR_HIGH))
            lcd_string("PULSE ");

        if(sp != 0 && sp < SPO2_LIMIT)
            lcd_string("SPO2 ");

        lcd_cmd(0xC0);
        lcd_string("ALERT");
    }
    else
    {
        IOCLR0 = (1<<GREEN_LED);
        IOSET0 = (1<<RED_LED);
        IOCLR0 = (1<<BUZZER);
    }
}

