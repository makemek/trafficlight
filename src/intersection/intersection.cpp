/*
 * intersection.cpp
 *
 *  Created on: 22 Nov 2014
 *      Author: Apipol
 */
#include "intersection.hpp"
#include "mode.h"

Intersection::Intersection(DFA& transit, LPC_TIMER_T* lpc_timer):
	transition(transit), clock(lpc_timer)
{
	light = transit.state();
	initQueueTime();

	timer_init(clock, 1000);
	timer_start(clock);
}

void Intersection::tick()
{
	for(int n = 0; n < transition.totalState(); ++n) {
		TrafficLight* t = light[n];

		if(t->timeLeft() == 0)
		{
			TrafficLight* prev;
			switch(t->state()) {
			case RED: t->green(); break;
			case YELLOW:
				t->red();
				prev = &transition.previousState();
				t->setCounter(prev->timeLeft() + prev->getGreenTime() + prev->getYellowTime());
				transition.transit(0);
				break;
			case GREEN: t->yellow(); break;
			}
		}

	}

	for (int n = 0; n < transition.totalState(); ++n)
		light[n]->decrement();
}

void Intersection::initQueueTime()
{
	TrafficLight* t = &transition.currentState();
	TrafficLight* cur = t;
	TrafficLight* next;

	uint8_t acc = 0;

	while ((next = &transition.transit(RED)) != t)
	{
		acc += cur->getGreenTime() + cur->getYellowTime();
		next->setCounter(acc);
		cur = next;
	}
}

void Intersection::automatic()
{
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, OVERRIDE_PORT, OVERRIDE_PIN);
	timer_enable(clock);
	tick();
}

void Intersection::manual(uint8_t lightID)
{
	Chip_GPIO_SetPinOutLow(LPC_GPIO, OVERRIDE_PORT, OVERRIDE_PIN);
	timer_pause(clock);
	for(int n = 0; n < transition.totalState(); ++n)
	{
		light[n]->seg.display(0);
		light[n]->led.red();
	}

	light[lightID]->led.green();
}

//void Intersection::unused()
//{
//	timer_pause(clock);
//}
