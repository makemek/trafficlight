/*
 * rgb_led.cpp
 *
 *  Created on: 22 Nov 2014
 *      Author: Apipol
 */

#include "util.hpp"
#include "board.h"

RGB_LED::RGB_LED(IO r, IO g, IO b):
	r(r), g(g), b(b)
{
	Chip_GPIO_SetDir(LPC_GPIO, r.port, r.pin, 1);
	Chip_GPIO_SetDir(LPC_GPIO, g.port, g.pin, 1);
	Chip_GPIO_SetDir(LPC_GPIO, b.port, b.pin, 1);

	Chip_IOCON_PinMuxSet(LPC_IOCON, r.port, r.pin, IOCON_FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON, g.port, g.pin, IOCON_FUNC0);
	Chip_IOCON_PinMuxSet(LPC_IOCON, b.port, b.pin, IOCON_FUNC0);
}

void RGB_LED::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
	color = red << 2 | green << 1 | blue;
	out(red, green, blue);
}

void RGB_LED::out(uint8_t red, uint8_t green, uint8_t blue)
{
	Chip_GPIO_SetPinState(LPC_GPIO, r.port, r.pin, red);
	Chip_GPIO_SetPinState(LPC_GPIO, g.port, g.pin, green);
	Chip_GPIO_SetPinState(LPC_GPIO, b.port, b.pin, blue);
}

void RGB_LED::on()
{
	setColor(color >> 2 & 1, color >> 1 & 1, color & 1);
}
