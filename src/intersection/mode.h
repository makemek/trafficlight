/*
 * mode.h
 *
 *  Created on: 27 Nov 2014
 *      Author: Apipol
 */

#ifdef __cplusplus
extern "C"
{
#endif


#ifndef MODE_H_
#define MODE_H_

#define LIGHT0_HANDLER EINT0_IRQHandler
#define LIGHT0_PORT GPIOINT_PORT2
#define LIGHT0_PIN 10

#define LIGHT1_HANDLER EINT1_IRQHandler
#define LIGHT1_PORT GPIOINT_PORT2
#define LIGHT1_PIN 13

#define LIGHT2_HANDLER EINT2_IRQHandler
#define LIGHT2_PORT GPIOINT_PORT2
#define LIGHT2_PIN 12

#define MODE_HANDLER EINT3_IRQHandler
#define MODE_PORT GPIOINT_PORT2
#define MODE_PIN 11

#define OVERRIDE_PORT 0
#define OVERRIDE_PIN 28

enum MODE {AUTO, MANUAL, NUM_MODE};
extern volatile uint8_t mode;
extern volatile uint8_t override_light;

/*
 * initialize GPIO interrupt pin
 *
 */
void mode_init();

#endif /* MODE_H_ */

#ifdef __cplusplus
}
#endif
