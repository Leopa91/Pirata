/*
 * input_mux.h
 *
 *  Created on: 11 jul. 2017
 *      Author: Admin
 */

#ifndef INPUT_MUX_H_
#define INPUT_MUX_H_

int8_t data_envio[20];

void Send_data(const uint8_t pui8Buffer[], uint8_t z);
int8_t tamaño_mux(uint8_t vector_input[]);
uint8_t CR(uint8_t vector_input[], uint8_t len );
void datos_mux(uint8_t vector_input[]);
void datos_mux2(uint8_t vector_input[]);
void fin_comu(uint8_t pos);
void envio_error(uint8_t vector_input[],uint8_t error);



#endif /* INPUT_MUX_H_ */
