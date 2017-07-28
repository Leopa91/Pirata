/*
 * read_serial2.h
 *
 *  Created on: 17 jul. 2017
 *      Author: Admin
 */

#ifndef READ_SERIAL2_H_
#define READ_SERIAL2_H_


void UART2IntHandler(void);
uint32_t tamaño_serial2(uint8_t vector_input[]);
void llenar_envio2(uint8_t vector_input[], uint8_t bloque, uint8_t tipo);
void read_serial2(uint8_t vector_input[]);
void Borrar_data2(void);




#endif /* READ_SERIAL2_H_ */
