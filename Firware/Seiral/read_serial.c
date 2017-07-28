/*
 * read_serial.c
 *
 *  Created on: 12 jul. 2017
 *      Author: Admin
 */


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include <string.h>
#include "input_mux.h"
#include "read_serial.h"
#include <stdio.h>
#include "Ibutton.h"
#include "read_serial2.h"


//*****************************************************************************
//
// The UART interrupt serial.
//
//*****************************************************************************


uint8_t tiempo;
static uint8_t puntero_clave;
static uint8_t bandera_clave;
static uint8_t clave[10];


void UART1IntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = ROM_UARTIntStatus(UART1_BASE, true);
    ROM_UARTIntClear(UART1_BASE, ui32Status);
    ROM_IntDisable(INT_UART1);


    uint16_t i = 0;
    uint16_t z = 0;


    for(z=0; z<4; z++)
    {
        while(ROM_UARTCharsAvail(UART1_BASE))
        {

            dato_entrada_basura[i] = ROM_UARTCharGet(UART1_BASE);
            //ROM_UARTCharPut(UART2_BASE, ROM_UARTCharGet(UART1_BASE));
            i++;


            SysCtlDelay(((SysCtlClockGet())/(1000*3)*1)*tiempo);

            z=0;
            //SysCtlDelay(((SysCtlClockGet())/(1000*3)*1)*1);

        }

    SysCtlDelay(((SysCtlClockGet())/(1000*6)*1)*1);
    }



    if(bandera_clave == 0)
    {

        if(bandera_entrada_serial == 1)
        {

            for(i=0; i < 500; i++)
            {
                dato_entrada_serial[i] = dato_entrada_basura[i];
            }

            bandera_entrada_serial = 0;
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
        }

        else
        {
            for(i=0; i < 500; i++)
            {
                dato_entrada_basura[i] = '\0';

            }

        }
    }

    else if(bandera_clave == 1)
   {
        clave[puntero_clave] = dato_entrada_basura[i];
        if (clave[puntero_clave] == 0x0D) bandera_clave = 0;
        else if (clave[puntero_clave] == 0x0A)
            {
                if(puntero_clave != 0) puntero_clave--;
            }
        else puntero_clave++;

   }
    ROM_IntMasterEnable();
    ROM_IntEnable(INT_UART1);
}


//******************************************************************
//TAMAÑO DE LA TRAMA SERIAL QUE ENTRA POR EL PUERTO DE LOS SENSORES
//******************************************************************
uint32_t tamaño_serial(uint8_t vector_input[])
{
    size_t i = 0;
    uint32_t z = 0;

    for(i=499; i > 0; i--)
    {
        z++;
        if( vector_input[i] != '\0') break;

    }

    z = 500 - z;

    return z;
}
//******************************************************************


//******************************************************************
//AQUI ES DONDE SE ETIQUETA EL SERIAL PARA ENVIARLO AL MUX
//******************************************************************
void llenar_envio(uint8_t vector_input[], uint8_t bloque, uint8_t tipo)
{

    uint32_t tamaño_vector;

    bloque_mux = bloque;

    if(bloque == 1)
    {
        size_t i;
        size_t z = 9;

        dato_salida_bloque1[0] = 'A';
        dato_salida_bloque1[1] = 'T';
        dato_salida_bloque1[2] = '+';
        dato_salida_bloque1[3] = bloque;
        dato_salida_bloque1[4] = ';';
        dato_salida_bloque1[5] = tamaño_serial(dato_entrada_serial);
        dato_salida_bloque1[6] = ';';
        dato_salida_bloque1[7] = 1;
        dato_salida_bloque1[8] = ';';

        if(tipo == 1)
        {
            tamaño_vector = tamaño_serial(dato_entrada_serial);
            for(i=0; i < tamaño_vector; i++)
            {
                dato_salida_bloque1[z] = dato_entrada_serial[i];
                z++;
            }
        }

        else
        {
            tamaño_vector = 8;
            for(i=0; i < tamaño_vector; i++)
            {
                dato_salida_bloque1[z] = vector_input[i];
                z++;
            }
        }

        dato_salida_bloque1[z] = ';';
        z++;
        dato_salida_bloque1[z] = '#';
        z++;
        dato_salida_bloque1[z] = '\0';

        for(i=z; i <141; i++)
        {
            dato_salida_bloque1[z] = '\0';
        }

    }

    else if(bloque == 2 )
   {
        size_t i;
        size_t z = 9;

        dato_salida_bloque1[0] = 'A';
        dato_salida_bloque1[1] = 'T';
        dato_salida_bloque1[2] = '+';
        dato_salida_bloque1[3] = bloque - 1;
        dato_salida_bloque1[4] = ';';
        dato_salida_bloque1[5] = 3;
        dato_salida_bloque1[6] = ';';
        dato_salida_bloque1[7] = 1;
        dato_salida_bloque1[8] = ';';

        for(i=0; i < 128; i++)
        {
            dato_salida_bloque1[z] = dato_entrada_serial[i];
            z++;
        }

        dato_salida_bloque1[z] = ';';
        z++;
        dato_salida_bloque1[z] = '#';


        z = 9;

        dato_salida_bloque2[0] = 'A';
        dato_salida_bloque2[1] = 'T';
        dato_salida_bloque2[2] = '+';
        dato_salida_bloque2[3] = bloque;
        dato_salida_bloque2[4] = ';';
        dato_salida_bloque2[5] = tamaño_serial(dato_entrada_serial) - 3;
        dato_salida_bloque2[6] = ';';
        dato_salida_bloque2[7] = 1;
        dato_salida_bloque2[8] = ';';

        for(i=128; i < tamaño_serial(dato_entrada_serial) ; i++)
        {
            dato_salida_bloque2[z] = dato_entrada_serial[i];
            z++;
        }

        dato_salida_bloque2[z] = ';';
        z++;
        dato_salida_bloque2[z] = '#';
        z++;
        dato_salida_bloque2[z] = '\0';

   }

    else if(bloque == 3)
   {
        size_t i;
        size_t z = 9;

        dato_salida_bloque1[0] = 'A';
        dato_salida_bloque1[1] = 'T';
        dato_salida_bloque1[2] = '+';
        dato_salida_bloque1[3] = bloque - 2;
        dato_salida_bloque1[4] = ';';
        dato_salida_bloque1[5] = 3;
        dato_salida_bloque1[6] = ';';
        dato_salida_bloque1[7] = 1;
        dato_salida_bloque1[8] = ';';

        for(i=0; i < 128; i++)
        {
            dato_salida_bloque1[z] = dato_entrada_serial[i];
            z++;
        }

        dato_salida_bloque1[z] = ';';
        z++;
        dato_salida_bloque1[z] = '#';
        z++;
        dato_salida_bloque1[z] = '\0';


        z = 9;

        dato_salida_bloque2[0] = 'A';
        dato_salida_bloque2[1] = 'T';
        dato_salida_bloque2[2] = '+';
        dato_salida_bloque2[3] = bloque -1;
        dato_salida_bloque2[4] = ';';
        dato_salida_bloque2[5] = 3;
        dato_salida_bloque2[6] = ';';
        dato_salida_bloque2[7] = 1;
        dato_salida_bloque2[8] = ';';

        for(i=128; i < 256 ; i++)
        {
            dato_salida_bloque2[z] = dato_entrada_serial[i];
            z++;
        }

        dato_salida_bloque2[z] = ';';
        z++;
        dato_salida_bloque2[z] = '#';
        z++;
        dato_salida_bloque2[z] = '\0';

        z = 9;

        dato_salida_bloque3[0] = 'A';
        dato_salida_bloque3[1] = 'T';
        dato_salida_bloque3[2] = '+';
        dato_salida_bloque3[3] = bloque;
        dato_salida_bloque3[4] = ';';
        dato_salida_bloque3[5] = tamaño_serial(dato_entrada_serial) - 6;
        dato_salida_bloque3[6] = ';';
        dato_salida_bloque3[7] = 1;
        dato_salida_bloque3[8] = ';';

        for(i=256; i < tamaño_serial(dato_entrada_serial) ; i++)
        {
            dato_salida_bloque3[z] = dato_entrada_serial[i];
            z++;
        }

        dato_salida_bloque3[z] = ';';
        z++;
        dato_salida_bloque3[z] = '#';
        z++;
        dato_salida_bloque3[z] = '\0';

   }
}
//******************************************************************


//******************************************************************
//AQUI LLEGA LA ORDEN PARA EMPESAR A RECIBIR DATOS DEL SENSOR POR LA
//POSICION 1
//******************************************************************
void read_serial(uint8_t vector_input[])
{

    uint32_t i;


    if(bandera_entrada_completa == 0)       //DETERMINA SI ESTA DESOCUPADO PARA EMPESAR A RECIBIR INFORMACION DEL SENSOR
    {
        bandera_entrada_serial = 1;         //ACTIVA LA BANDERA PARA ALMACENAR LA INFORMACION ENTRANTE AL PUERTO SERIAL
        uint32_t tamaño = 0;
        uint8_t err = 1;

        for(i=0; i < 10000 ; i++)
        {
            SysCtlDelay((SysCtlClockGet())/(1000*3));
        }

            if(bandera_entrada_serial == 0)
            {

                bandera_entrada_completa = 1;
                tamaño = tamaño_serial(dato_entrada_serial);

                if(tamaño <= 128)
                {
                    bloque_mux = 1;
                    err = 3;
                }
                else if (tamaño <= 256)
                {
                    bloque_mux = 2;
                    err = 3;
                }
                else if (tamaño <= 384)
                {
                    bloque_mux = 3;
                    err = 3;
                }
                else
                {
                    err = 2;
                }

                llenar_envio(vector_input,bloque_mux,1);
                //bandera_entrada_completa = 0;

               // break;
            }



        dato_salida_serial[0] = 'A';
        dato_salida_serial[1] = 'T';
        dato_salida_serial[2] = '+';
        dato_salida_serial[3] = 'R';
        dato_salida_serial[4] = vector_input[4];
        dato_salida_serial[5] = ';';
        dato_salida_serial[6] = 'P';
        dato_salida_serial[7] = vector_input[7];
        dato_salida_serial[8] = ';';
        dato_salida_serial[9] = 'E';
        dato_salida_serial[10] = err;
        dato_salida_serial[11] = ';';
        dato_salida_serial[12] = (tamaño >> 8) & 0x00ff;
        dato_salida_serial[13] = tamaño & 0x00ff;
        dato_salida_serial[14] = ';';
        dato_salida_serial[15] = bloque_mux;
        dato_salida_serial[16] = ';';
        dato_salida_serial[17] = CR(dato_salida_serial,17);
        dato_salida_serial[18] = ';';
        dato_salida_serial[19] = '#';

        Send_data(dato_salida_serial,20);
    }
    else
    {

        dato_salida_serial[0] = 'A';
        dato_salida_serial[1] = 'T';
        dato_salida_serial[2] = '+';
        dato_salida_serial[3] = 'R';
        dato_salida_serial[4] = vector_input[4];
        dato_salida_serial[5] = ';';
        dato_salida_serial[6] = 'P';
        dato_salida_serial[7] = vector_input[7];
        dato_salida_serial[8] = ';';
        dato_salida_serial[9] = 'E';
        dato_salida_serial[10] = 5;
        dato_salida_serial[11] = ';';
        dato_salida_serial[12] = 0;
        dato_salida_serial[13] = 0;
        dato_salida_serial[14] = ';';
        dato_salida_serial[15] = bloque_mux;
        dato_salida_serial[16] = ';';
        dato_salida_serial[17] = CR(dato_salida_serial,17);
        dato_salida_serial[18] = ';';
        dato_salida_serial[19] = '#';

        Send_data(dato_salida_serial,20);

    }
}
//**************************************************************



//******************************************************************
//AQUI LLEGA LA ORDEN PARA EMPESAR A ENVIAR LOS BLOQUE
//******************************************************************
void envio_mux(uint8_t vector_input[], uint8_t nume_bloque)
{
    switch(nume_bloque)
    {
       case 0:  //BLOQUE_1
       {
           if(nume_bloque == bloque_mux )           //SI YA SE ENVIO LA CANTIDAD MAXIMA DE BLOQUE RESPONDA TRANSACION EXITOSA
           {
               fin_comu(1);
               Borrar_data();
           }
           else
           {
               Send_data(dato_salida_bloque1, tamaño_mux(dato_salida_bloque1)); // ENVIA EL PRIMER BLOQUE EMPAQUETADO
           }
       }
       break;

       case 1:  //BLOQUE_2
       {
           if(nume_bloque == bloque_mux )
          {
              fin_comu(1);
              Borrar_data();
          }
          else
          {
              Send_data(dato_salida_bloque2,tamaño_mux(dato_salida_bloque2));
          }
       }
       break;

       case 2:  //BLOQUE_3
       {
           if(nume_bloque == bloque_mux )
           {
               fin_comu(1);
               Borrar_data();
           }
           else
           {
               Send_data(dato_salida_bloque3, tamaño_mux(dato_salida_bloque3));
           }
       }

       break;
    }
}
//******************************************************************



//******************************************************************
//EN ESTA FUNCION SE BORRA LOS DATOS Y LAS BANDERA PARA ESTAR LISTO
//PARA LA SIGUENTE LECTURA DE LOS SENSORES
//******************************************************************
void Borrar_data(void)
{
    uint16_t i;

    for(i=0; i<500; i++)
    {
        dato_entrada_serial[i] = '\0';
    }

    for(i=0; i<500; i++)
    {
        dato_entrada_basura[i] = '\0';
    }

    for(i=0; i<141; i++)
    {

        dato_salida_bloque1[i] = '\0';
    }

    for(i=0; i<141; i++)
    {
        dato_salida_bloque2[i] = '\0';
    }

    for(i=0; i<141; i++)
    {
        dato_salida_bloque3[i] = '\0';
    }

    for(i=0; i<141; i++)
    {
        dato_salida_serial[i] = '\0';
    }

    bandera_entrada_completa = 0;

}

void clave_serial(uint8_t vector_input[])
{

    uint16_t i;
    uint16_t err;

    bandera_clave = 1;
    for(i=0; i<100000 ;i++)
    {
        SysCtlDelay((SysCtlClockGet())/(1000*3));
    }

    if(bandera_clave == 1) err=2;
    else err = 1;



}






