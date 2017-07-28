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
#include "Serial.h"
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

static uint8_t dato_salida_bloque12[141];


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


    size_t i;
    size_t z = 9;

    dato_salida_bloque12[0] = 'A';
    dato_salida_bloque12[1] = 'T';
    dato_salida_bloque12[2] = '+';
    dato_salida_bloque12[3] = '2';
    dato_salida_bloque12[4] = ';';
    dato_salida_bloque12[5] = '1';
    dato_salida_bloque12[6] = ';';

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
    dato_salida_bloque12[z] = CR(dato_salida_bloque12, z);
    z++;
    dato_salida_bloque12[z] = ';';
    z++;
    dato_salida_bloque12[z] = '#';
    z++;
    dato_salida_bloque12[z] = '\0';
    z++;

    for(i=z; i <500; i++)
    {
        dato_salida_bloque12[z] = '\0';
    }

    Send_data(dato_salida_bloque12,tamaño_mux(dato_salida_bloque12));

}

void read_serial2(uint8_t vector_input[])
{

    uint32_t i;

    if(bandera_entrada_completa2 == 0)
    {

        bandera_entrada_serial2 = 1;



        for(i=0; i < Tiempo_espera ; i++)
        {
            SysCtlDelay((SysCtlClockGet())/(1000*3));
            if(bandera_entrada_serial2 == 0) break;
        }


        if(bandera_entrada_serial2 == 0)
        {

            bandera_entrada_completa2 = 1;
            llenar_envio2(vector_input,bloque_mux2,1);

        }

        else
       {

           dato_salida_bloque12[0] = 'A';
           dato_salida_bloque12[1] = 'T';
           dato_salida_bloque12[2] = '+';
           dato_salida_bloque12[3] = '2';
           dato_salida_bloque12[4] = ';';
           dato_salida_bloque12[5] = '2';
           dato_salida_bloque12[6] = ';';
           dato_salida_bloque12[7] = CR(dato_salida_bloque12, 7);
           dato_salida_bloque12[8] = ';';
           dato_salida_bloque12[9] = '#';

           Send_data(dato_salida_bloque12,tamaño_mux(dato_salida_bloque12));
       }

        Borrar_data2();


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


    bandera_entrada_completa2 = 0;

}



