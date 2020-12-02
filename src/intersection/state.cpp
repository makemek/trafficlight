/*
 * state.cpp
 *
 *  Created on: 21 Nov 2014
 *      Author: Apipol
 */

#include "intersection.hpp"
#include <cassert>

DFA::DFA(TrafficLight& beg, TrafficLight* states[], const int n, TrafficLight* (*t)[2])
{
	size = n;
	this->states = states;
	start = &beg;
	currentStateIdx = indexOf(beg);
	prev = &currentState();
	assert(currentStateIdx != -1);
	table = t;
}

int DFA::indexOf(TrafficLight& t)
{
	for (int n = 0; n < size; ++n)
	{
		if (*states[n] == t)
			return n;
	}
	return -1;
}

TrafficLight& DFA::transit(int input)
{
	prev = &currentState();
	currentStateIdx = indexOf(*table[currentStateIdx][input]);
	assert(currentStateIdx != -1);
	return *states[currentStateIdx];
}
