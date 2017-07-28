/*
 * read_serial2.c
 *
 *  Created on: 17 jul. 2017
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
#include "read_serial2.h"
#include <stdio.h>
#include "Ibutton.h"


//*****************************************************************************
//
// The UART interrupt serial.
//
//*****************************************************************************

static uint8_t dato_entrada_serial2[500];
static uint8_t dato_entrada_basura2[500];
static uint8_t bandera_entrada_serial2;
static uint8_t bandera_entrada_completa2;
static uint8_t bloque_mux2;
static uint8_t dato_salida_serial2[141];
static uint8_t dato_salida_bloque12[141];
static uint8_t dato_salida_bloque22[141];
static uint8_t dato_salida_bloque32[141];
uint8_t tiempo;



void UART3IntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = ROM_UARTIntStatus(UART3_BASE, true);

    ROM_UARTIntClear(UART3_BASE, ui32Status);

    uint16_t i = 0;

    while(ROM_UARTCharsAvail(UART3_BASE))
    {

        dato_entrada_basura2[i] = ROM_UARTCharGet(UART3_BASE);
        i++;
        SysCtlDelay(((SysCtlClockGet())/(1000*3)*1)*tiempo);

    }

    if(bandera_entrada_serial2 == 1)
    {

        for(i=0; i < 500; i++)
        {
            dato_entrada_serial2[i] = dato_entrada_basura2[i];


        }

        bandera_entrada_serial2 = 0;

        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
    }

    else
    {
      for(i=0; i < 500; i++)
      {
          dato_entrada_basura2[i] = '\0';

      }

   }

}



uint32_t tamaño_serial2(uint8_t vector_input[])
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

void llenar_envio2(uint8_t vector_input[], uint8_t bloque, uint8_t tipo)
{

    uint32_t tamaño_vector;

    bloque_mux2 = bloque;

    if(bloque == 1)
    {
        size_t i;
        size_t z = 9;

        dato_salida_bloque12[0] = 'A';
        dato_salida_bloque12[1] = 'T';
        dato_salida_bloque12[2] = '+';
        dato_salida_bloque12[3] = bloque;
        dato_salida_bloque12[4] = ';';
        dato_salida_bloque12[5] = 8;
        dato_salida_bloque12[6] = ';';
        dato_salida_bloque12[7] = 1;
        dato_salida_bloque12[8] = ';';

        if(tipo == 1)
        {
            tamaño_vector = tamaño_serial2(dato_entrada_serial2);
            for(i=0; i < tamaño_vector; i++)
            {
                dato_salida_bloque12[z] = dato_entrada_serial2[i];
                z++;
            }
        }

        else
        {
            tamaño_vector = 8;
            for(i=0; i < tamaño_vector; i++)
            {
                dato_salida_bloque12[z] = vector_input[i];
                z++;
            }
        }



        dato_salida_bloque12[z] = ';';
        z++;
        dato_salida_bloque12[z] = '#';
        z++;
        dato_salida_bloque12[z] = '\0';

        for(i=z; i <141; i++)
        {
            dato_salida_bloque12[z] = '\0';
        }

    }

    else if(bloque == 2 && vector_input[7] == '2')
   {
        size_t i;
        size_t z = 9;

        dato_salida_bloque12[0] = 'A';
        dato_salida_bloque12[1] = 'T';
        dato_salida_bloque12[2] = '+';
        dato_salida_bloque12[3] = bloque - 1;
        dato_salida_bloque12[4] = ';';
        dato_salida_bloque12[5] = 3;
        dato_salida_bloque12[6] = ';';
        dato_salida_bloque12[7] = 1;
        dato_salida_bloque12[8] = ';';

        for(i=0; i < 128; i++)
        {
            dato_salida_bloque12[z] = dato_entrada_serial2[i];
            z++;
        }

        dato_salida_bloque12[z] = ';';
        z++;
        dato_salida_bloque12[z] = '#';


        z = 9;

        dato_salida_bloque22[0] = 'A';
        dato_salida_bloque22[1] = 'T';
        dato_salida_bloque22[2] = '+';
        dato_salida_bloque22[3] = bloque;
        dato_salida_bloque22[4] = ';';
        dato_salida_bloque22[5] = tamaño_serial2(dato_entrada_serial2) - 3;
        dato_salida_bloque22[6] = ';';
        dato_salida_bloque22[7] = 1;
        dato_salida_bloque22[8] = ';';

        for(i=128; i < tamaño_serial2(dato_entrada_serial2) ; i++)
        {
            dato_salida_bloque22[z] = dato_entrada_serial2[i];
            z++;
        }

        dato_salida_bloque22[z] = ';';
        z++;
        dato_salida_bloque22[z] = '#';
        z++;
        dato_salida_bloque22[z] = '\0';

   }

    else if(bloque == 3 && vector_input[7] == '2')
   {
        size_t i;
        size_t z = 9;

        dato_salida_bloque12[0] = 'A';
        dato_salida_bloque12[1] = 'T';
        dato_salida_bloque12[2] = '+';
        dato_salida_bloque12[3] = bloque - 2;
        dato_salida_bloque12[4] = ';';
        dato_salida_bloque12[5] = 3;
        dato_salida_bloque12[6] = ';';
        dato_salida_bloque12[7] = 1;
        dato_salida_bloque12[8] = ';';

        for(i=0; i < 128; i++)
        {
            dato_salida_bloque12[z] = dato_entrada_serial2[i];
            z++;
        }

        dato_salida_bloque12[z] = ';';
        z++;
        dato_salida_bloque12[z] = '#';
        z++;
        dato_salida_bloque12[z] = '\0';


        z = 9;

        dato_salida_bloque22[0] = 'A';
        dato_salida_bloque22[1] = 'T';
        dato_salida_bloque22[2] = '+';
        dato_salida_bloque22[3] = bloque -1;
        dato_salida_bloque22[4] = ';';
        dato_salida_bloque22[5] = 3;
        dato_salida_bloque22[6] = ';';
        dato_salida_bloque22[7] = 1;
        dato_salida_bloque22[8] = ';';

        for(i=128; i < 256 ; i++)
        {
            dato_salida_bloque22[z] = dato_entrada_serial2[i];
            z++;
        }

        dato_salida_bloque22[z] = ';';
        z++;
        dato_salida_bloque22[z] = '#';
        z++;
        dato_salida_bloque22[z] = '\0';

        z = 9;

        dato_salida_bloque32[0] = 'A';
        dato_salida_bloque32[1] = 'T';
        dato_salida_bloque32[2] = '+';
        dato_salida_bloque32[3] = bloque;
        dato_salida_bloque32[4] = ';';
        dato_salida_bloque32[5] = tamaño_serial2(dato_entrada_serial2) - 6;
        dato_salida_bloque32[6] = ';';
        dato_salida_bloque32[7] = 1;
        dato_salida_bloque32[8] = ';';

        for(i=256; i < tamaño_serial2(dato_entrada_serial2) ; i++)
        {
            dato_salida_bloque32[z] = dato_entrada_serial2[i];
            z++;
        }

        dato_salida_bloque32[z] = ';';
        z++;
        dato_salida_bloque32[z] = '#';
        z++;
        dato_salida_bloque32[z] = '\0';

   }
}

void read_serial2(uint8_t vector_input[])
{

    uint32_t i;




    if(bandera_entrada_completa2 == 0)
    {

        bandera_entrada_serial2 = 1;
        uint32_t tamaño = 0;
        uint8_t err = 1;

        for(i=0; i < 10000 ; i++)
        {
            SysCtlDelay((SysCtlClockGet())/(1000*3));

            if(bandera_entrada_serial2 == 0)
            {

                bandera_entrada_completa2 = 1;
                tamaño = tamaño_serial2(dato_entrada_serial2);

                if(tamaño <= 128)
                {
                    bloque_mux2 = 1;
                    err = 3;
                }
                else if (tamaño <= 256)
                {
                    bloque_mux2 = 2;
                    err = 3;
                }
                else if (tamaño <= 384)
                {
                    bloque_mux2 = 3;
                    err = 3;
                }
                else
                {
                    err = 2;
                }

                llenar_envio2(vector_input,bloque_mux2,1);


                break;
            }

        }

        dato_salida_serial2[0] = 'A';
        dato_salida_serial2[1] = 'T';
        dato_salida_serial2[2] = '+';
        dato_salida_serial2[3] = 'R';
        dato_salida_serial2[4] = vector_input[4];
        dato_salida_serial2[5] = ';';
        dato_salida_serial2[6] = 'P';
        dato_salida_serial2[7] = vector_input[7];
        dato_salida_serial2[8] = ';';
        dato_salida_serial2[9] = 'E';
        dato_salida_serial2[10] = err;
        dato_salida_serial2[11] = ';';
        dato_salida_serial2[12] = (tamaño >> 8) & 0x00ff;
        dato_salida_serial2[13] = tamaño & 0x00ff;
        dato_salida_serial2[14] = ';';
        dato_salida_serial2[15] = bloque_mux2;
        dato_salida_serial2[16] = ';';
        dato_salida_serial2[17] = CR(dato_salida_serial2,17);
        dato_salida_serial2[18] = ';';
        dato_salida_serial2[19] = '#';

        Send_data(dato_salida_serial2,20);
    }
    else
    {

        dato_salida_serial2[0] = 'A';
        dato_salida_serial2[1] = 'T';
        dato_salida_serial2[2] = '+';
        dato_salida_serial2[3] = 'R';
        dato_salida_serial2[4] = vector_input[4];
        dato_salida_serial2[5] = ';';
        dato_salida_serial2[6] = 'P';
        dato_salida_serial2[7] = vector_input[7];
        dato_salida_serial2[8] = ';';
        dato_salida_serial2[9] = 'E';
        dato_salida_serial2[10] = 5;
        dato_salida_serial2[11] = ';';
        dato_salida_serial2[12] = 0;
        dato_salida_serial2[13] = 0;
        dato_salida_serial2[14] = ';';
        dato_salida_serial2[15] = bloque_mux2;
        dato_salida_serial2[16] = ';';
        dato_salida_serial2[17] = CR(dato_salida_serial2,17);
        dato_salida_serial2[18] = ';';
        dato_salida_serial2[19] = '#';

        Send_data(dato_salida_serial2,20);

    }
}

void envio_mux2(uint8_t vector_input[], uint8_t nume_bloque)
{
    switch(nume_bloque)
    {
       case 0:  //BLOQUE_1
       {
           if(nume_bloque == bloque_mux2 )
           {
               fin_comu(2);
               Borrar_data2();
           }
           else
           {
               Send_data(dato_salida_bloque12, tamaño_mux(dato_salida_bloque12));
           }
       }
       break;

       case 1:  //BLOQUE_2
       {
           if(nume_bloque == bloque_mux2 )
          {
              fin_comu(2);
              Borrar_data2();
          }
          else
          {
              Send_data(dato_salida_bloque22,tamaño_mux(dato_salida_bloque22));
          }
       }
       break;

       case 2:  //BLOQUE_3
       {
           if(nume_bloque == bloque_mux2 )
           {
               fin_comu(2);
               Borrar_data2();
           }
           else
           {
               Send_data(dato_salida_bloque32, tamaño_mux(dato_salida_bloque32));
           }
       }

       break;
    }
}

void Borrar_data2(void)
{
    uint16_t i;

    for(i=0; i<500; i++)
    {
        dato_entrada_serial2[i] = '\0';
    }

    for(i=0; i<500; i++)
    {
        dato_entrada_basura2[i] = '\0';
    }

    for(i=0; i<141; i++)
    {
        dato_salida_bloque12[i] = '\0';
    }

    for(i=0; i<141; i++)
    {
        dato_salida_bloque22[i] = '\0';
    }

    for(i=0; i<141; i++)
    {
        dato_salida_bloque32[i] = '\0';
    }

    for(i=0; i<141; i++)
    {
        dato_salida_serial2[i] = '\0';
    }

    bandera_entrada_completa2 = 0;

}



