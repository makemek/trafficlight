/*
 * traffic_light.hpp
 *
 *  Created on: 21 Nov 2014
 *      Author: Apipol
 */

#ifndef TRAFFIC_LIGHT_HPP_
#define TRAFFIC_LIGHT_HPP_

#include "../util/util.hpp"
#include <stdint.h>

#define RED 0
#define YELLOW 1
#define GREEN 2

class TrafficLight
{
	friend class Intersection;
private:
	RGB_LED led;
	Segment7 seg;

	uint8_t counter;
	uint8_t color;

	uint8_t green_t;
	static const uint8_t YELLOW_T = 2;

public:
	TrafficLight(RGB_LED& led, Segment7& seg, uint8_t green_time);

	uint8_t decrement();

	RGB_LED& getLight() { return led; }

	void setCounter(uint8_t time) { counter = time; }
	void setGreenTime(uint8_t time) {green_t = time; }

	uint8_t timeLeft() {return counter;}
	uint8_t getGreenTime() { return green_t; }
	uint8_t getYellowTime() { return YELLOW_T; }

	void red();
	void yellow();
	void green();

	/*
	 * 0 = red
	 * 1 = yellow
	 * 2 = green
	 */
	uint8_t state() {return color;}

	bool equals(TrafficLight& t) { return this == &t; }
	bool operator==(TrafficLight& t) { return equals(t); }
	bool operator!=(TrafficLight& t) { return !equals(t); }
};






#endif /* TRAFFIC_LIGHT_HPP_ */
