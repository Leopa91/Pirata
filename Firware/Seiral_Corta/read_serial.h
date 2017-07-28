/*
 * read_serial.h
 *
 *  Created on: 12 jul. 2017
 *      Author: Admin
 */

#ifndef READ_SERIAL_H_
#define READ_SERIAL_H_

void UARTIntHandler1(void);
uint32_t tamaño_serial(uint8_t vector_input[]);
void llenar_envio(uint8_t vector_input[], uint8_t bloque, uint8_t tipo);
void read_serial(uint8_t vector_input[]);
void Borrar_data(void);

static uint8_t dato_entrada_serial[500];
static uint8_t dato_entrada_basura[500];
static uint8_t bandera_entrada_serial;
static uint8_t bandera_entrada_completa;
static uint8_t bloque_mux;
static uint8_t dato_salida_serial[141];
static uint8_t dato_salida_bloque1[141];
static uint8_t dato_salida_bloque2[141];
static uint8_t dato_salida_bloque3[141];

#endif /* READ_SERIAL_H_ */
