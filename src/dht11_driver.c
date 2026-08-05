#include <LPC21xx.H>
#include "header.h"
#define DHT11_PIN (1<<4)

void dht11_init(void)
{
    IO0DIR |= DHT11_PIN;
    IO0SET  = DHT11_PIN;   /* idle state = HIGH */
}

static void dht11_request(void)
{
    IO0DIR |= DHT11_PIN;
    IO0CLR  = DHT11_PIN;
    delay_ms(20);          /* MCU pulls low >=18ms per datasheet */
    IO0SET  = DHT11_PIN;
    delay_us(30);
    IO0DIR &= ~DHT11_PIN;  /* release bus, sensor takes over */
}

static unsigned char dht11_response(void)
{
    unsigned int count = 0;

    while(IO0PIN & DHT11_PIN)          /* wait for sensor to pull LOW (~80us) */
    {
        if(++count > 10000) return 0;
    }
    count = 0;
    while(!(IO0PIN & DHT11_PIN))       /* wait for sensor to release HIGH (~80us) */
    {
        if(++count > 10000) return 0;
    }
    count = 0;
    while(IO0PIN & DHT11_PIN)          /* wait for HIGH to end -> data starts */
    {
        if(++count > 10000) return 0;
    }
    return 1;
}

static unsigned char dht11_read_byte(void)
{
    unsigned char i, data = 0;
    unsigned int timeout;

    for(i = 0; i < 8; i++)
    {
        timeout = 0;
        while(!(IO0PIN & DHT11_PIN))       /* each bit starts with ~50us LOW */
        {
            if(++timeout > 20000) return data;
        }
        delay_us(40);                      /* sample partway into the HIGH pulse */
        if(IO0PIN & DHT11_PIN)
        {
            data |= (1 << (7 - i));
            timeout = 0;
            while(IO0PIN & DHT11_PIN)       /* wait out the long (70us) HIGH for a '1' */
            {
                if(++timeout > 20000) break;
            }
        }
    }
    return data;
}

unsigned char dht11_read(unsigned char *temp_int)
{
    unsigned char hum_i, hum_d, temp_i, temp_d, checksum;

    dht11_request();

    if(!dht11_response())
        return 0;

    hum_i     = dht11_read_byte();
    hum_d     = dht11_read_byte();
    temp_i    = dht11_read_byte();
    temp_d    = dht11_read_byte();
    checksum  = dht11_read_byte();

    if(checksum != (u8)(hum_i + hum_d + temp_i + temp_d))
        return 0;

    *temp_int = temp_i;
    return 1;
}
