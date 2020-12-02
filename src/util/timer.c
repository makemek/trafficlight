/*
 * timer.cpp
 *
 *  Created on: 26 Nov 2014
 *      Author: Apipol
 */
#include "timer.h"

int corresMat(LPC_TIMER_T* lpc_timer)
{
	if(lpc_timer == LPC_TIMER0)
		return 0;
	else if(lpc_timer == LPC_TIMER1)
		return 1;
	else if(lpc_timer == LPC_TIMER2)
		return 2;
	else if(lpc_timer == LPC_TIMER3)
		return 3;

	return -1;
}

IRQn_Type corresIRQn(LPC_TIMER_T* lpc_timer)
{
	if(lpc_timer == LPC_TIMER0)
		return TIMER0_IRQn;
	else if(lpc_timer == LPC_TIMER1)
		return TIMER1_IRQn;
	else if(lpc_timer == LPC_TIMER2)
		return TIMER2_IRQn;
	else if(lpc_timer == LPC_TIMER3)
		return TIMER3_IRQn;


	else
		return TIMER0_IRQn;
}

void timer_init(LPC_TIMER_T* lpc_timer, uint32_t mill)
{
	uint8_t mat_timer = corresMat(lpc_timer);
    uint32_t timerFreq, prescaledivisor = 8;
    uint32_t ticksPerSec, tickPerMs;

    Chip_TIMER_Init(lpc_timer);
    timerFreq = Chip_Clock_GetSystemClockRate();

    ticksPerSec = timerFreq/prescaledivisor/4;
    tickPerMs = ticksPerSec/1000;

    Chip_TIMER_Reset(lpc_timer);
	Chip_TIMER_MatchEnableInt(lpc_timer, mat_timer);
	Chip_TIMER_SetMatch(lpc_timer, mat_timer, mill * tickPerMs);
	Chip_TIMER_PrescaleSet(lpc_timer, prescaledivisor - 1);
	Chip_TIMER_ResetOnMatchEnable(lpc_timer, mat_timer);
}

void timer_start(LPC_TIMER_T* lpc_timer)
{
	/* Enable timer interrupt */
	IRQn_Type irq = corresIRQn(lpc_timer);
	NVIC_ClearPendingIRQ(irq);
	NVIC_EnableIRQ(irq);

	Chip_TIMER_Enable(lpc_timer);
}

void timer_enable(LPC_TIMER_T* lpc_timer)
{
	Chip_TIMER_Enable(lpc_timer);
}

void timer_pause(LPC_TIMER_T* lpc_timer)
{
	Chip_TIMER_Disable(lpc_timer);
}

void TIMER0_IRQHandler(void)
{
	int match_timer = corresMat(LPC_TIMER0);
	if (Chip_TIMER_MatchPending(LPC_TIMER0, match_timer)) {
		Chip_TIMER_ClearMatch(LPC_TIMER0, match_timer);
	}
}
