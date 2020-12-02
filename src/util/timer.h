/*
 * timer.hpp
 *
 *  Created on: 21 Nov 2014
 *      Author: Apipol
 */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef TIMER_H_
#define TIMER_H_

#include "board.h"
#include <stdint.h>

void timer_init(LPC_TIMER_T* lpc_timer, uint32_t mill);
void timer_start(LPC_TIMER_T* lpc_timer);
void timer_enable(LPC_TIMER_T* lpc_timer);
void timer_pause(LPC_TIMER_T* lpc_timer);
int corresMat(LPC_TIMER_T* lpc_timer);
IRQn_Type corresIRQn(LPC_TIMER_T* lpc_timer);


#endif /* TIMER_H_ */

#ifdef __cplusplus
}
#endif
