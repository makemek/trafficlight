/*
 * pinIO.h
 *
 *  Created on: 27 Nov 2014
 *      Author: Apipol
 */

#ifdef __cplusplus
extern "C"
{
#endif


#ifndef PINIO_H_
#define PINIO_H_

#include <stdint.h>

typedef struct io
{
	uint8_t port;
	uint8_t pin;
} IO;


#endif /* PINIO_H_ */



#ifdef __cplusplus
}
#endif
