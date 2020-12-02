/*
 * intersection.hpp
 *
 *  Created on: 21 Nov 2014
 *      Author: Apipol
 */

#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include "../traffic_light/traffic_light.hpp"
#include "../util/timer.h"
#include "board.h"

class DFA
{
private:
	int currentStateIdx;
	int size;
	TrafficLight* start;
	TrafficLight** states;
	TrafficLight* (*table)[2]; // 2d array of TrafficLight pointer

	TrafficLight* prev;

	int indexOf(TrafficLight& t);
public:
	DFA(TrafficLight& beginState, TrafficLight* states[], const int howManyStates, TrafficLight* (*transitionTable)[2]);
	TrafficLight& currentState() {return *states[currentStateIdx];}
	TrafficLight& transit(int input);
	TrafficLight& startState() { return *start; }
	TrafficLight& previousState() { return *prev; }

	int totalState() {return size; }
	TrafficLight** state() { return states; }
};

class Intersection
{
private:
	DFA& transition;
	LPC_TIMER_T* clock;
	TrafficLight** light;

	void initQueueTime();

public:
	Intersection(DFA& transit, LPC_TIMER_T* lpc_timer);
	void tick();
	void blink();

	//void unused();
	void automatic();
	void manual(uint8_t lightID);
};

#endif /* INTERSECTION_HPP_ */
