/*
 * traffic_light.cpp
 *
 *  Created on: 22 Nov 2014
 *      Author: Apipol
 */
#include "traffic_light.hpp"

TrafficLight::TrafficLight(RGB_LED& led, Segment7& seg, uint8_t green_time):
		led(led), seg(seg), green_t(green_time)
{
	red();
	counter = 0;
	seg.display(counter);
}

uint8_t TrafficLight::decrement()
{
	seg.display(counter);
	counter--;
	return timeLeft();
}

void TrafficLight::red()
{
	color = RED;
	led.red();
	seg.display(counter);
}

void TrafficLight::yellow()
{
	color = YELLOW;
	setCounter(YELLOW_T);
	led.yellow();
	seg.display(counter);
}

void TrafficLight::green()
{
	color = GREEN;
	setCounter(green_t);
	led.green();
	seg.display(counter);
}
