/*
 * Serial.h
 *
 *  Created on: 18 jul. 2017
 *      Author: Admin
 */

#ifndef SERIAL_H_
#define SERIAL_H_

static char POSICION_1 = 'A';
static char POSICION_2 = 'B';

#define BAUD_MAX            9600
#define BAUD_TAG            9600
#define BAUD_RFID           2400
#define BAUD_QR             9600
#define BAUD_TAR_MAG        9600

#define Tiempo_espera       1000


#define SEL1                POSICION_1
#define SEL2                POSICION_2

static uint8_t dato;
static char dato_entrada[256];
static uint16_t input_entrada;
static char data_mux[10];
static uint16_t input_mux;
static uint8_t bandera_entrada = 0;
static uint8_t bandera_entrada_mux = 0;
static char dato_entrada[256];


void UARTSend(const uint8_t *pui8Buffer);
void UART1Send(const uint8_t *pui8Buffer);
void UART2Send(const uint8_t *pui8Buffer);


#endif /* SERIAL_H_ */
