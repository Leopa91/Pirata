/*
 * Ibutton.h
 *
 *  Created on: 22 jun. 2017
 *      Author: Admin
 */

#ifndef IBUTTON_H_
#define IBUTTON_H_

#include <stdint.h>

#define ONE_WIRE_PIN    GPIO_PIN_2
#define ONE_WIRE_PIN2   GPIO_PIN_3
#define relay_ini       6
#define relay_data      15
#define relay_all       60
#define relay_write     (relay_all - relay_ini)
#define relay_read      (relay_all - (relay_ini + relay_data))
#define relay_fin       10
#define relay_reset_tx  500
#define relay_reset_rx  200
#define puert           GPIO_PORTA_BASE



void Delay(int delay);
int Ibutton1_reset(void);
void Ibutton1_write(uint8_t data);
int Ibutton1_read(void);


int Ibutton2_reset(void);
void Ibutton2_write(uint8_t data);
int Ibutton2_read(void);


#endif /* IBUTTON_H_ */
