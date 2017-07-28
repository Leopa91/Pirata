//*****************************************************************************
//
//    SERIAL
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



//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// Variables globales
//
//*****************************************************************************

extern uint8_t tiempo;

//*****************************************************************************
//
// Envio de datos al mux
//
//*****************************************************************************

void UARTSend(const uint8_t *pui8Buffer)
{

    while(*pui8Buffer )
    {

        ROM_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);

    }
}

void UART1Send(const uint8_t *pui8Buffer)
{

    while(*pui8Buffer )
    {

        ROM_UARTCharPutNonBlocking(UART1_BASE, *pui8Buffer++);

    }
}

void UART2Send(const uint8_t *pui8Buffer)
{

    while(*pui8Buffer )
    {

        ROM_UARTCharPutNonBlocking(UART2_BASE, *pui8Buffer++);

    }
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void UARTIntHandler(void)
{
    uint32_t ui32Status;
    uint8_t dato_entrada_basura[20];
    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART0_BASE, true);
    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART0_BASE, ui32Status);

    uint16_t i = 0;

    //
    // Loop while there are characters in the receive FIFO.
    //

     while(ROM_UARTCharsAvail(UART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        // ROM_UARTCharPut(UART0_BASE,ROM_UARTCharGet(UART0_BASE));
        dato_entrada_basura[i] = ROM_UARTCharGet(UART0_BASE);
        i++;
        SysCtlDelay((SysCtlClockGet())/(1000*3));
    }

     if(bandera_entrada_mux == 0)
     {
         for(i=0; i<20; i++)
         {
             dato_entrada[i] = dato_entrada_basura[i];
             if(dato_entrada[i] == '#')
             {
                 bandera_entrada_mux = 1;
                 break;
             }
         }

     }
     else
     {
         for(i=0; i<20; i++)
          {
              dato_entrada_basura[i] = '\0';
          }
     }


}



void UART2IntHandler(void)
{
    uint32_t ui32Status;
    uint8_t dato_entrada_basura[20];
    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART2_BASE, true);
    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART2_BASE, ui32Status);

    uint16_t i = 0;

    //
    // Loop while there are characters in the receive FIFO.
    //

     while(ROM_UARTCharsAvail(UART2_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //


         dato_entrada_basura[i] = ROM_UARTCharGet(UART2_BASE);

         i++;
         SysCtlDelay((SysCtlClockGet())/(1000*3));

    }

     if(bandera_entrada_mux == 0)
     {
         for(i=0; i<20; i++)
         {
             dato_entrada[i] = dato_entrada_basura[i];
             if(dato_entrada[i] == '#')
             {
                 bandera_entrada_mux = 1;

                 break;
             }
         }

     }
     else
     {
         for(i=0; i<20; i++)
          {
              dato_entrada_basura[i] = '\0';
          }
     }



     SysCtlDelay((SysCtlClockGet())/(1000*3));

}





int main(void)
{

    //*******************************************************************************************
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //*******************************************************************************************
    ROM_FPUEnable();
    ROM_FPULazyStackingEnable();
    //*******************************************************************************************


    //*******************************************************************************************
    // Set the clocking to run directly from the crystal.
    //*******************************************************************************************
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);
    //*******************************************************************************************


    //***************************************************
    // Enable the peripherals used by this example.
    //****************************************************
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= GPIO_PIN_7;

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);



    //******************************
    // Enable processor interrupts.
    //******************************
    ROM_IntMasterEnable();
    //******************************


    //******************************
    // Set GPIO A0 and A1 as UART pins.
    // Set GPIO B0 and B1 as UART pins.
    // Set GPIO D6 and D7 as UART pins.
    // Set GPIO C6 and C7 as UART pins.
    //******************************
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    ROM_GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    GPIOPinConfigure(GPIO_PC6_U3RX);
    GPIOPinConfigure(GPIO_PC7_U3TX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    //***********************************************************************


    //**********************************************************************
    // Configure the UART for 115,200, 8-N-1 operation.
    //**********************************************************************
    ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 9600,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 9600,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                            UART_CONFIG_PAR_NONE));

    ROM_UARTConfigSetExpClk(UART2_BASE, ROM_SysCtlClockGet(), 9600,
                              (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                               UART_CONFIG_PAR_NONE));

    ROM_UARTConfigSetExpClk(UART3_BASE, ROM_SysCtlClockGet(), 9600,
                              (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                               UART_CONFIG_PAR_NONE));
    //*****************************************************************************


    //*****************************************************************************
    // Enable the UART interrupt.
    //*****************************************************************************
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    ROM_IntEnable(INT_UART1);
    ROM_UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

    ROM_IntEnable(INT_UART2);
    ROM_UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);

    ROM_IntEnable(INT_UART3);
    ROM_UARTIntEnable(UART3_BASE, UART_INT_RX | UART_INT_RT);
    //*****************************************************************************


    //*****************************************************************************
    // Enable the GPIO port.
    //*****************************************************************************
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //****************************************************


    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4,  0X00);



    //****************************************************
    // PINES DE SELEC A
    //****************************************************
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3);
    //****************************************************

    //****************************************************
    // PINES DE SELEC B
    //****************************************************
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);
    //****************************************************

    //
    // AUX1
    //
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_5);
    //****************************************************

    //
    // ONE_WIRE_1 Y ONE_WIR2_2
    //
    ROM_GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2);
    ROM_GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_3);
    //****************************************************


    //
    // TRIG_1 Y TRIG_2
    //
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
    //****************************************************

    //
    // REST_1 Y REST_2
    //
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_4);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5);
    //****************************************************

    //
    // PINES EN 1
    //****************************************************
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3);

    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);

    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);

    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);

    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);

    //****************************************************




    while(1)
    {


        if(bandera_entrada_mux == 1)
        {

            if((dato_entrada[7] & 0X0f) == 1)
            {

                datos_mux1(dato_entrada);
            }

            if((dato_entrada[7] & 0X0f) == 2)
            {
                datos_mux2(dato_entrada);
            }

            bandera_entrada_mux = 0;
            SysCtlDelay((SysCtlClockGet())/(1000*3));

        }


        SysCtlDelay((SysCtlClockGet())/(1000*3));


       // ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_reset());

           // Ibutton1_write(0x33);
           // ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_read());
        //ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_read());
        //ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_read());
        // ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_read());
        // ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_read());
        // ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_read());
        // ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_read());
        // ROM_UARTCharPutNonBlocking(UART0_BASE,Ibutton1_read());







    }
}
