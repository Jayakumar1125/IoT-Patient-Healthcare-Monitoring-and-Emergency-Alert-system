#include <LPC21xx.H>
#include "header.h"
#include "max30102.h"
#include "filter.h"
#include "heartrate.h"
#include "spo2.h"
int main(){
uart0_init(9600);
uart1_init(9600);

while(1)
{
    uart1_tx('A');
    delay_ms(1000);
}
}