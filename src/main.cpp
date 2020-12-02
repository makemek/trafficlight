///*
//===============================================================================
// Name        : main.c
// Author      : $(author)
// Version     :
// Copyright   : $(copyright)
// Description : main definition
//===============================================================================
//*/
//
#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "util/timer.h"
#include "traffic_light/traffic_light.hpp"
#include "intersection/intersection.hpp"
#include "util/util.hpp"
#include "intersection/mode.h"

void allPinGPIO()
{
	for(int n = 0; n < 11; ++n)
		LPC_IOCON->PINSEL[n] = 0;

	for(int n = 0; n < 10; ++n)
		LPC_IOCON->PINMODE[n] = 0;

	for(int n = 0; n < 5; ++n)
		LPC_IOCON->PINMODE_OD[n] = 0;
}

void testLED(RGB_LED led[], uint8_t led_amt)
{
	for(uint8_t n = 0; n < led_amt; ++n)
	{
		led[n].red();
		led[n].green();

		led[n].off();
		led[n].on();
	}
}

void testSegment7(Segment7 seg[], uint8_t seg_amt)
{
	for(uint8_t n = 0; n < seg_amt; ++n)
		for(uint8_t numDis = 0; n < 10; ++numDis)
			seg[n].display(numDis);
}

volatile uint8_t mode;
volatile uint8_t override_light;

int main(void) {
    SystemCoreClockUpdate();
    Board_Init();

    allPinGPIO();

	RGB_LED t1_led = RGB_LED( (io){0, 0}, (io){0, 1}, (io){0, 18});
	RGB_LED t2_led = RGB_LED( (io){0, 24}, (io){2, 7}, (io){0, 25});
	RGB_LED t3_led = RGB_LED( (io){0, 21}, (io){0, 22}, (io){0, 27});

	Segment7 t1_seg = Segment7( (io){0, 9}, (io){0, 8}, (io){0, 7}, (io){0, 6});
	Segment7 t2_seg = Segment7( (io){0, 17}, (io){0, 15}, (io){0, 16}, (io){0, 23});
	Segment7 t3_seg = Segment7( (io){1, 30}, (io){1, 31}, (io){0, 2}, (io){0, 3});

	TrafficLight a = TrafficLight(t1_led, t1_seg, 3);
	TrafficLight b = TrafficLight(t2_led, t2_seg, 2);
	TrafficLight c = TrafficLight(t3_led, t3_seg, 2);

	TrafficLight* table[][2] = {
		{ &b, &a },
		{ &c, &b },
		{ &a, &c }
	};
	TrafficLight* states[] = {&a, &b, &c};

//	TrafficLight* table2[][2] = {
//			{ &b, &a },
//			{ &a, &b },
//		};
//	TrafficLight* states2[] = {&a, &b};

	DFA stateMachine1 = DFA(a, states, sizeof(states)/sizeof(TrafficLight*), table);
	//DFA stateMachine2 = DFA(a, states2, sizeof(states2)/sizeof(TrafficLight*), table2);

	//mode_init();
	Intersection in = Intersection(stateMachine1, LPC_TIMER0);

	while(1)
	{
		switch(mode)
		{
		case AUTO:
			in.automatic();
			break;
		case MANUAL:
			in.manual(override_light);
			break;
		}

		__WFI();
	}

    return 0 ;
}
