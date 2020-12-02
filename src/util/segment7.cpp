/*
 * segment7.cpp
 *
 *  Created on: 22 Nov 2014
 *      Author: Apipol
 */

#include "util.hpp"
#include "board.h"



Segment7::Segment7(IO bit0_pin, IO bit1_pin, IO bit2_pin, IO bit3_pin)
{
	p[0] = bit0_pin;
	p[1] = bit1_pin;
	p[2] = bit2_pin;
	p[3] = bit3_pin;

	for(uint8_t n = 0; n < sizeof(p)/sizeof(IO); ++n) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, p[n].port, p[n].pin, IOCON_FUNC0);
		Chip_GPIO_SetDir(LPC_GPIO, p[n].port, p[n].pin, 1);
	}

	display(0);
}

void Segment7::display(uint8_t number)
{
	for(uint8_t n = 0; n < sizeof(p)/sizeof(IO); ++n)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, p[n].port, p[n].pin, number & 1);
		number >>= 1;
	}

}

