/* i2c_driver.c */


#include <LPC21xx.H>
#include "header.h"


#define SI ((I2CONSET>>3)&1)



void i2c_init(void)
{

    /*
       P0.2 -> SCL
       P0.3 -> SDA
    */

    PINSEL0 |= 0x50;



    /*
       100KHz I2C

       PCLK = 15MHz

    */

    I2SCLH = 75;
    I2SCLL = 75;



    /*
       Enable I2C

    */

    I2CONCLR = (1<<2);     // AA=0

    I2CONSET = (1<<6);     // I2EN=1

}





void i2c_send(u8 sa,u8 mr,u8 data)
{

    /* START */

    I2CONSET=(1<<5);

    I2CONCLR=(1<<3);

    while(SI==0);


    I2CONCLR=(1<<5);





    /* Slave address + Write */


    I2DAT=(sa<<1);


    I2CONCLR=(1<<3);

    while(SI==0);



    if(I2STAT!=0x18)
        goto exit;





    /* Register address */


    I2DAT=mr;


    I2CONCLR=(1<<3);

    while(SI==0);



    if(I2STAT!=0x28)
        goto exit;





    /* Data */


    I2DAT=data;


    I2CONCLR=(1<<3);

    while(SI==0);



    if(I2STAT!=0x28)
        goto exit;





exit:


    /* STOP */

    I2CONSET=(1<<4);

    I2CONCLR=(1<<3);

}








u8 i2c_read(u8 sa,u8 mr)
{

    u8 data=0;




    /* START */


    I2CONSET=(1<<5);

    I2CONCLR=(1<<3);


    while(SI==0);


    I2CONCLR=(1<<5);





    /* Slave address + Write */


    I2DAT=(sa<<1);


    I2CONCLR=(1<<3);


    while(SI==0);



    if(I2STAT!=0x18)
        goto exit;






    /* Register address */


    I2DAT=mr;


    I2CONCLR=(1<<3);


    while(SI==0);



    if(I2STAT!=0x28)
        goto exit;






    /* Repeated START */


    I2CONSET=(1<<5);

    I2CONCLR=(1<<3);


    while(SI==0);


    I2CONCLR=(1<<5);






    /* Slave address + Read */


    I2DAT=(sa<<1)|1;


    I2CONCLR=(1<<3);


    while(SI==0);



    if(I2STAT!=0x40)
        goto exit;







    /*
       Receive one byte

       NACK after byte

    */


    I2CONCLR=(1<<2);


    I2CONCLR=(1<<3);


    while(SI==0);



    if(I2STAT==0x58)
    {
        data=I2DAT;
    }





exit:


    /* STOP */

    I2CONSET=(1<<4);

    I2CONCLR=(1<<3);



    return data;

}









void i2c_read_buf(u8 sa,u8 mr,u8 *buf,u8 len)
{

    u8 i;




    /* START */

    I2CONSET=(1<<5);

    I2CONCLR=(1<<3);


    while(SI==0);


    I2CONCLR=(1<<5);







    /* Slave + Write */


    I2DAT=(sa<<1);


    I2CONCLR=(1<<3);


    while(SI==0);



    if(I2STAT!=0x18)
        goto exit;







    /* Register */


    I2DAT=mr;


    I2CONCLR=(1<<3);


    while(SI==0);



    if(I2STAT!=0x28)
        goto exit;







    /* Restart */


    I2CONSET=(1<<5);


    I2CONCLR=(1<<3);


    while(SI==0);


    I2CONCLR=(1<<5);







    /* Slave + Read */


    I2DAT=(sa<<1)|1;


    I2CONCLR=(1<<3);


    while(SI==0);



    if(I2STAT!=0x40)
        goto exit;








    /* Read bytes */


    for(i=0;i<len;i++)
    {


        if(i==(len-1))
        {
            /*
               Last byte
               send NACK

            */

            I2CONCLR=(1<<2);
        }

        else
        {

            /*
               More bytes
               send ACK

            */

            I2CONSET=(1<<2);

        }



        I2CONCLR=(1<<3);


        while(SI==0);



        buf[i]=I2DAT;

    }






exit:


    /* STOP */


    I2CONSET=(1<<4);

    I2CONCLR=(1<<3);

}