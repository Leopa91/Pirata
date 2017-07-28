/*
 * Ibutton.c
 *
 *  Created on: 22 jun. 2017
 *      Author: Admin
 */
#include "Ibutton.h"
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
#include "Ibutton.h"

void Delay(int delay)
{
    SysCtlDelay((SysCtlClockGet() / (3000000 ))*delay);
}

int Ibutton1_reset(void)
{

    ROM_GPIOPinTypeGPIOOutput(puert, ONE_WIRE_PIN); // Poner el PIN en salida

    GPIOPinWrite(puert, ONE_WIRE_PIN, 0);       // Ponemos el pin en 0

    Delay(700);


    ROM_GPIOPinTypeGPIOInput(puert, ONE_WIRE_PIN); // CAmbiamos el PIN a entrada

    Delay(50);

    if( 0 == GPIOPinRead(puert, ONE_WIRE_PIN)) // Lectura del puerto para determinar la presencia
    {
        Delay(relay_reset_rx);
        return 1;
    }
    else
    {
        Delay(relay_reset_rx);
        return 0;
    }

}

void Ibutton1_write(uint8_t data)
{

    int count;

    for(count = 0 ; count < 8 ; ++count)
    {
        if(data & 0x01)
        {
            ROM_GPIOPinTypeGPIOOutput(puert, ONE_WIRE_PIN); // Poner el PIN en salida

            GPIOPinWrite(puert, ONE_WIRE_PIN, 0);       // Ponemos el pin en 0

            Delay(6);

            ROM_GPIOPinWrite(puert, ONE_WIRE_PIN, 1);
            GPIOPinTypeGPIOInput(puert, ONE_WIRE_PIN); // CAmbiamos el PIN a entrada

            Delay(90);
        }
        else
        {

            ROM_GPIOPinTypeGPIOOutput(puert, ONE_WIRE_PIN); // Poner el PIN en salida

            GPIOPinWrite(puert, ONE_WIRE_PIN, 0);       // Ponemos el pin en 0

            Delay(60);


            ROM_GPIOPinTypeGPIOInput(puert, ONE_WIRE_PIN); // CAmbiamos el PIN a entrada

            Delay(30);
        }

        data = data >> 1;
    }

}

int Ibutton1_read()
{
    int count, data, dato, i;

    data = 0x00;
    dato = 0x00;


    for(count = 0 ; count < 8 ; ++count)
    {

        ROM_GPIOPinTypeGPIOOutput(puert, ONE_WIRE_PIN); // Poner el PIN en salida

        GPIOPinWrite(puert, ONE_WIRE_PIN, 0);       // Ponemos el pin en 0

        Delay(6);


        ROM_GPIOPinTypeGPIOInput(puert, ONE_WIRE_PIN); // CAmbiamos el PIN a entrada


        Delay(10);

        if( 0 == GPIOPinRead(puert, ONE_WIRE_PIN))
        {

            if (count != 7)
            {
                data = data << 1;
            }
        }
        else
        {
            data = data | 1;
            if (count != 7)
            {
                data = data << 1;
            }

        }

        Delay(100);

    }

    for(count = 0 ; count < 8 ; ++count)
    {
        dato = dato << 1;
        dato = dato | ((data >> count) & 1);

    }

return dato;
}

int Ibutton2_reset(void)
{

    ROM_GPIOPinTypeGPIOOutput(puert, ONE_WIRE_PIN2); // Poner el PIN en salida

    GPIOPinWrite(puert, ONE_WIRE_PIN2, 0);       // Ponemos el pin en 0

    Delay(700);


    ROM_GPIOPinTypeGPIOInput(puert, ONE_WIRE_PIN2); // CAmbiamos el PIN a entrada

    Delay(50);

    if( 0 == GPIOPinRead(puert, ONE_WIRE_PIN2)) // Lectura del puerto para determinar la presencia
    {
        Delay(relay_reset_rx);
        return 1;
    }
    else
    {
        Delay(relay_reset_rx);
        return 0;
    }

}

void Ibutton2_write(uint8_t data)
{

    int count;

    for(count = 0 ; count < 8 ; ++count)
    {
        if(data & 0x01)
        {
            ROM_GPIOPinTypeGPIOOutput(puert, ONE_WIRE_PIN2); // Poner el PIN en salida

            GPIOPinWrite(puert, ONE_WIRE_PIN2, 0);       // Ponemos el pin en 0

            Delay(6);

            ROM_GPIOPinWrite(puert, ONE_WIRE_PIN2, 1);
            GPIOPinTypeGPIOInput(puert, ONE_WIRE_PIN2); // CAmbiamos el PIN a entrada

            Delay(90);
        }
        else
        {

            ROM_GPIOPinTypeGPIOOutput(puert, ONE_WIRE_PIN2); // Poner el PIN en salida

            GPIOPinWrite(puert, ONE_WIRE_PIN2, 0);       // Ponemos el pin en 0

            Delay(60);


            ROM_GPIOPinTypeGPIOInput(puert, ONE_WIRE_PIN2); // CAmbiamos el PIN a entrada

            Delay(30);
        }

        data = data >> 1;
    }

}

int Ibutton2_read()
{
    int count, data, dato, i;

    data = 0x00;
    dato = 0x00;


    for(count = 0 ; count < 8 ; ++count)
    {

        ROM_GPIOPinTypeGPIOOutput(puert, ONE_WIRE_PIN2); // Poner el PIN en salida

        GPIOPinWrite(puert, ONE_WIRE_PIN2, 0);       // Ponemos el pin en 0

        Delay(6);


        ROM_GPIOPinTypeGPIOInput(puert, ONE_WIRE_PIN2); // CAmbiamos el PIN a entrada


        Delay(10);

        if( 0 == GPIOPinRead(puert, ONE_WIRE_PIN2))
        {

            if (count != 7)
            {
                data = data << 1;
            }
        }
        else
        {
            data = data | 1;
            if (count != 7)
            {
                data = data << 1;
            }

        }

        Delay(100);

    }

    for(count = 0 ; count < 8 ; ++count)
    {
        dato = dato << 1;
        dato = dato | ((data >> count) & 1);

    }

return dato;
}
