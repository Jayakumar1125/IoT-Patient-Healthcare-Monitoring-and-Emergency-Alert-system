typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef short int s16;

//DELAY
void delay_ms(unsigned int ms);
void delay_sec(unsigned int sec);
void delay_us(unsigned int us);

//LCD
void lcd_init(void);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(char *ptr);
void lcd_integer(int num);
void lcd_float(float f);

//UART
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_tx_string(char *ptr);
extern void uart0_integer(int num);
void uart0_float(float f);
u8 uart0_rx(void);
u8 uart0_rx_ready(void);

//ESP-01 (runs on UART0 - see esp01_driver.c header comment)
u8 esp01_send_cmd(char *cmd, char *expected, u32 timeout_loops);
u8 esp01_connect_wifi(char *ssid, char *pass);
u8 esp01_send_thingspeak(char *api_key, int t, u32 hr, u8 sp);

//I2C
extern void i2c_init(void);
extern void i2c_send(u8 sa,u8 mr,u8 data);
extern u8 i2c_read(u8 sa,u8 mr);
extern void i2c_read_buf(u8 sa,u8 mr,u8 *buf,u8 len);

//DHT11
void dht11_init(void);
unsigned char dht11_read(unsigned char *temp_int);

//MAX30100
u8 max30100_init(void);
void max30100_read(u32 *hr, u8 *spo2);

//App logic
void lcd_display(int t,u32 hr,u8 sp);
void check_condition(int t,u32 hr,u8 sp);
void gpio_init(void);

//ESP
extern void esp01_cmd(char *cmd);
extern void esp01_init(void);
extern void esp01_wifi(void);
extern void esp01_server(void);
extern int wifi_check(void);
//extern void esp01_send_data(float temp,int hr,int spo2);
extern void esp01_send_data(int, int, int);


//UART0
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_tx_string(char *ptr);
extern unsigned char uart0_rx(void);
extern void uart0_binary(unsigned int num);
extern void uart0_rx_string(char *ptr,int len);
extern void uart0_integer(int num);
extern void uart0_float(float f);
//extern void uart0_intr(void);
extern void timer0_config(void);
extern void config_eint0(void);


//UART1
extern void uart1_init(unsigned int baud);
extern void uart1_tx(unsigned char data);
extern void uart1_tx_string(char *ptr);
extern unsigned char uart1_rx(void);
extern void uart1_binary(unsigned int num);
extern void uart1_rx_string(char *ptr,int len);
extern void uart1_integer(int num);
extern void uart1_float(float f);
extern void uart1_intr_init(void);
extern void uart1_intr(void);
//extern void timer0_config(void);
//extern void config_eint0(void);

#include<string.h>
#include<stdio.h>
