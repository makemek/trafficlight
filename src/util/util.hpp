/*
 * util.hpp
 *
 *  Created on: 21 Nov 2014
 *      Author: Apipol
 */

#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <stdint.h>
#include "pinIO.h"

class RGB_LED
{
private:
	uint8_t color;
	IO r, g, b;

	void out(uint8_t red, uint8_t green, uint8_t blue);
public:
	RGB_LED(IO red_pin, IO green_pin, IO blue_pin);

	void red() { setColor(1,0,0);}
	void yellow() { setColor(1, 1, 0); }
	void green() { setColor(0, 1, 0); }

	void setColor(uint8_t r, uint8_t g, uint8_t b);
	void off() { out(0,0,0); }
	void on();
};

class Segment7
{
private:
	IO p[4];
public:
	/*
	 * bit [0:4] = pin
	 * bit 4 = port
	 */
	Segment7(IO bit0_pin, IO bit1_pin, IO bit2_pin, IO bit3_pin);
	void display(uint8_t number);

};



#endif /* UTIL_HPP_ */
