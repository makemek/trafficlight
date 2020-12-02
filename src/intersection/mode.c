#include "../util/pinIO.h"
#include "mode.h"
#include "board.h"

volatile uint8_t mode;
volatile uint8_t override_light;

void LIGHT0_HANDLER(void)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, LIGHT0_PORT, 1 << LIGHT0_PIN);
	if(mode == AUTO)
		return;
	Board_LED_Toggle(0);
	override_light = 0;
}

void LIGHT1_HANDLER(void)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, LIGHT1_PORT, 1 << LIGHT1_PIN);
	if(mode == AUTO)
		return;

	Board_LED_Toggle(0);
	override_light = 1;
}

void LIGHT2_HANDLER(void)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, LIGHT2_PORT, 1 << LIGHT2_PIN);
	if(mode == AUTO)
			return;
	override_light = 2;
	Board_LED_Toggle(0);
}

void MODE_HANDLER(void)
{
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, LIGHT0_PORT, 1 << LIGHT0_PIN);
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, LIGHT1_PORT, 1 << LIGHT1_PIN);
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, LIGHT2_PORT, 1 << LIGHT2_PIN);
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, MODE_PORT, 1 << MODE_PIN);
	mode = (mode + 1) % NUM_MODE;

	if(mode != AUTO)
		Chip_GPIO_SetPinOutLow(LPC_GPIO, OVERRIDE_PORT, OVERRIDE_PIN);
	else
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, OVERRIDE_PORT, OVERRIDE_PIN);
	Board_LED_Toggle(0);
}


void mode_init()
{
	uint8_t n;
	uint8_t port;
	uint8_t pin;

	IO intPin[] = { (IO){MODE_PORT,MODE_PIN}, (IO){LIGHT0_PORT,LIGHT0_PIN}, (IO){LIGHT1_PORT,LIGHT1_PIN}, (IO){LIGHT2_PORT,LIGHT2_PIN}};
	LPC_GPIOINT_PORT_T intPort;

	mode = AUTO;
	override_light = 0;

	Chip_GPIO_SetPinDIROutput(LPC_GPIO, OVERRIDE_PORT, OVERRIDE_PIN);

	for(n = 0; n < sizeof(intPin)/sizeof(IO); ++n)
	{
		port = intPin[n].port;
		pin = intPin[n].pin;
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);


		if(port == GPIOINT_PORT0)
			intPort = GPIOINT_PORT0;
		else
			intPort = GPIOINT_PORT2;

		Chip_GPIOINT_SetIntRising(LPC_GPIOINT, intPort, 1 << pin);
	}

	NVIC_ClearPendingIRQ(EINT0_IRQn);
	NVIC_ClearPendingIRQ(EINT1_IRQn);
	NVIC_ClearPendingIRQ(EINT2_IRQn);
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT2_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
}

