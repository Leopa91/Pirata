//*****************************************************************************
//
//    RECIBE INFORMACION DEL MUX
//
//
// Copyright (c) 2012-2016 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.3.156 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "Serial.h"
#include "Ibutton.h"
#include <string.h>
#include "input_mux.h"
#include "read_serial.h"
#include "read_serial2.h"

uint8_t tiempo;


//*****************************************************
// ENVIO DE LOS DATOS AL MUX
// SE NECESITA UN VECTOR Y EL TAMA�O DEL VECTOR
//*****************************************************
void Send_data(const uint8_t pui8Buffer[], uint8_t z)
{
    size_t i = 0;

    for(i=0; i < z; i++)
    {
      ROM_UARTCharPut(UART2_BASE, pui8Buffer[i]);

    }

    for(i=0; i < z; i++)
    {
        ROM_UARTCharPut(UART0_BASE, pui8Buffer[i]);

    }

}
//*****************************************************


//*****************************************************
//SE DETERMINA EL TAMA�O DEL VECTOR QUE SE VA A ENVIAR
//AL MUX, SOLO SE NECESITA QUE ENVIE EL VECTOR Y EL
//RETORNA LA CANTIDAD
//*****************************************************
int8_t tama�o_mux(uint8_t vector_input[])
{
    uint8_t i;
    uint8_t z = 0;

    for(i=141; i > 0; i--)
    {

        if( vector_input[i] == '#') break;
        z++;

    }

    z = 142 - z;

    return z;
}
//*****************************************************


//*****************************************************
//SE DETERMINA SI EL VECTOR LLEGO COMPLETO
//*****************************************************
uint8_t CR(uint8_t vector_input[], uint8_t len )
{
    size_t i;
    uint16_t C = 0;
    uint16_t aux = 0;


        for(i=0; i < len; i++)
        {
           aux = aux + vector_input[i];
        }

        C = ~aux;
        C = C & 0xff;

        return C;

}
//*****************************************************


//*****************************************************
//AQUI ENTRA LOS DATOS DE LA PRIMERA POSICION ENVIADO
//POR EL MUX
//*****************************************************
void datos_mux1(uint8_t vector_input[])
{


    uint8_t tes_cr = 0;
    uint8_t tes_error = 0;
    size_t i;
    uint8_t vector_ibutto[8];
    uint8_t dato_salida_serial2[25];



    if(vector_input[3] == 'C')
    {

       if(vector_input[9] == CR(vector_input,9))
       {
           tes_cr = 1;
       }

       else
       {
           tes_cr = 0;
       }
    }

    else if(vector_input[3] == 'O')
    {
        if(vector_input[11] == CR(vector_input,11))
       {
            tes_cr = 1;
       }

       else
       {
           tes_cr = 0;
       }
   }

    if(!tes_cr == 1)
    {
        if(vector_input[3] == 'C')                                      // INICIO LA LECTURA SERIAL
        {
            switch(vector_input[4] & 0x0f)
            {
                case 1:  //Ibutton
                {
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3,GPIO_PIN_3);



                    tes_error = Ibutton1_reset();
                    if(tes_error == 0)
                    {
                        envio_error(vector_input,1);

                        break;
                    }

                    Ibutton1_write(0x33);

                    for(i=0; i<8; i++)
                    {
                        vector_ibutto[i] = Ibutton1_read();
                    }

                    llenar_envio(vector_ibutto,1,0);

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
                    dato_salida_serial2[10] = 3;
                    dato_salida_serial2[11] = ';';
                    dato_salida_serial2[12] = 0;
                    dato_salida_serial2[13] = 8;
                    dato_salida_serial2[14] = ';';
                    dato_salida_serial2[15] = 1;
                    dato_salida_serial2[16] = ';';
                    dato_salida_serial2[17] = CR(dato_salida_serial2,17);
                    dato_salida_serial2[18] = ';';
                    dato_salida_serial2[19] = '#';

                    Send_data(dato_salida_serial2,20);

                }
                break;

                case 2:   //TAG
                {
                    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), BAUD_TAG, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
                    tiempo = 1;
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3,0X00);

                    read_serial(vector_input);
                }
                break;

                case 3:  //RFID
                {

                    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), BAUD_RFID,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
                    tiempo = 9;
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,0X00);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3,GPIO_PIN_3);

                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0X00);
                    read_serial(vector_input);
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
                }
                break;

                case 4:   //QR
                {

                    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), BAUD_QR,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
                    tiempo = 1;
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,0X00);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3,GPIO_PIN_3);

                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0X00);
                    read_serial(vector_input);
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);

                }
                break;

                case 5:   //BANDA MAGNETICA
                {

                    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), BAUD_TAR_MAG,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
                    tiempo = 1;
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,0X00);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3,GPIO_PIN_3);
                    read_serial(vector_input);
                }
                break;

                case 6:   //BANDA MAGNETICA
                {

                    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), BAUD_TAR_MAG,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
                    tiempo = 8;
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3,0X00);
                    clave_serial(vector_input);
                }
                break;

            }
        }

        else if(vector_input[3] == 'O')                                         // ENVIO DE BLOQUES
        {
            switch(vector_input[4] & 0x0f)
            {
                case 1:  //Transacion exitosa y siguiente numero
                {
                    envio_mux(vector_input, (vector_input[12] & 0x0f));
                }
                break;

                case 2:  //Repetir bloque
                {
                    envio_mux(vector_input, ((vector_input[12] & 0x0f)-1));
                }
                break;

                case 3:  //Error de cantidad
                {

                }
                break;

                case 4:  //Error bloque
                {

                }
                break;

                case 5:  //Error CR
                {

                }
                break;

                case 6:  //FIN DE COMUNICACION EXITOSA
                {
                    fin_comu(1);
                    Borrar_data();
                }
                break;

                case 7:  //REINICIO
                {
                    Borrar_data();
                    read_serial(vector_input);
                }
                break;
            }


        }
    }

    else
    {
        envio_error(vector_input,4);
    }

}
//*****************************************************


//*****************************************************
//AQUI ENTRA LOS DATOS DE LA SEGUNDA POSICION ENVIADO
//POR EL MUX
//*****************************************************
void datos_mux2(uint8_t vector_input[])
{


    uint8_t tes_cr = 0;
    uint8_t tes_error;
    size_t i;
    uint8_t vector_ibutto[8];
    uint8_t dato_salida_serial2[25];



    if(vector_input[3] == 'C')
    {

       if(vector_input[9] == CR(vector_input,9))
       {
           tes_cr = 1;
       }

       else
       {
           tes_cr = 0;
       }
    }

    else if(vector_input[3] == 'O')
    {
        if(vector_input[11] == CR(vector_input,11))
       {
            tes_cr = 1;
       }

       else
       {
           tes_cr = 0;
       }
   }

    if(!tes_cr == 1)
    {
        if(vector_input[3] == 'C') // INICIO LA LECTURA SERIAL
        {
            switch(vector_input[4] & 0x0f)
            {
                case 1:  //Ibutton
                {

                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0X00);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);

                    tes_error = Ibutton2_reset();

                    if(tes_error == 0)
                    {
                        envio_error(vector_input,1);

                    }
                    else if(tes_error == 1)
                    {


                        Ibutton2_write(0x33);

                        for(i=0; i<8; i++)
                        {
                            vector_ibutto[i] = Ibutton2_read();
                        }

                        llenar_envio2(vector_ibutto,1,0);

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
                        dato_salida_serial2[10] = 3;
                        dato_salida_serial2[11] = ';';
                        dato_salida_serial2[12] = 0;
                        dato_salida_serial2[13] = 8;
                        dato_salida_serial2[14] = ';';
                        dato_salida_serial2[15] = 1;
                        dato_salida_serial2[16] = ';';
                        dato_salida_serial2[17] = CR(dato_salida_serial2,17);
                        dato_salida_serial2[18] = ';';
                        dato_salida_serial2[19] = '#';

                        Send_data(dato_salida_serial2,20);
                    }

                }
                break;

                case 2:   //TAG
                {

                    ROM_UARTConfigSetExpClk(UART3_BASE, ROM_SysCtlClockGet(), BAUD_TAG, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
                    tiempo = 1;
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0X00);

                    read_serial2(vector_input);
                }
                break;

                case 3:  //RFID
                {

                    ROM_UARTConfigSetExpClk(UART3_BASE, ROM_SysCtlClockGet(), BAUD_RFID,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
                    tiempo = 9;

                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0X00);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);

                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0X00);
                    read_serial2(vector_input);
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
                }
                break;

                case 4:   //QR
                {

                    ROM_UARTConfigSetExpClk(UART3_BASE, ROM_SysCtlClockGet(), BAUD_QR,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
                    tiempo = 1;

                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0X00);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);

                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0X00);
                    read_serial2(vector_input);
                    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
                }
                break;

                case 5:   //BANDA MAGNETICA
                {

                    ROM_UARTConfigSetExpClk(UART3_BASE, ROM_SysCtlClockGet(), BAUD_TAR_MAG,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
                    tiempo = 1;

                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0X00);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);
                    read_serial2(vector_input);
                }
                break;

            }
        }

        else if(vector_input[3] == 'O') // ENVIO DE BLOQUES
        {
            switch(vector_input[4] & 0x0f)
            {
                case 1:  //Transacion exitosa y siguiente numero
                {
                    envio_mux2(vector_input, (vector_input[12] & 0x0f));
                }
                break;

                case 2:  //Repetir bloque
                {
                    envio_mux2(vector_input, ((vector_input[12] & 0x0f)-1));
                }
                break;

                case 3:  //Error de cantidad
                {

                }
                break;

                case 4:  //Error bloque
                {

                }
                break;

                case 5:  //Error CR
                {

                }
                break;

                case 6:  //FIN DE COMUNICACION EXITOSA
                {
                    fin_comu(2);
                    Borrar_data2();
                }
                break;

                case 7:  //REINICIO
                {
                    Borrar_data2();
                    read_serial2(vector_input);
                }
                break;
            }


        }
    }

    else
    {
        envio_error(vector_input, 4);
    }

}
//*****************************************************


//*****************************************************
//ENVIO LA TRAMA DE FIN DE LA COMUNICACION AL MUX
//*****************************************************
void fin_comu(uint8_t pos)
{
    data_envio[0] = 'A';
    data_envio[1] = 'T';
    data_envio[2] = '+';
    data_envio[3] = 'F';
    data_envio[4] = pos;
    data_envio[5] = ';';
    data_envio[6] =  CR(data_envio,6);
    data_envio[7] = ';';
    data_envio[8] = '#';
    Send_data(data_envio,9);
}
//*****************************************************


//*****************************************************
//ENVIO LA TRAMA DE ERRORES AL MUX
//*****************************************************
void envio_error(uint8_t vector_input[],uint8_t error)
{
    data_envio[0] = 'A';
    data_envio[1] = 'T';
    data_envio[2] = '+';
    data_envio[3] = 'R';
    data_envio[4] = vector_input[4];
    data_envio[5] = ';';
    data_envio[6] = 'P';
    data_envio[7] = vector_input[7];
    data_envio[8] = ';';
    data_envio[9] = 'E';
    data_envio[10] = error;
    data_envio[11] = ';';
    data_envio[12] = 0x00;
    data_envio[13] = 0x00;
    data_envio[14] = ';';
    data_envio[15] = 0x00;
    data_envio[16] = ';';
    data_envio[17] =  CR(data_envio,17);
    data_envio[18] = ';';
    data_envio[19] = '#';

    Send_data(data_envio,20);
}
//*****************************************************

