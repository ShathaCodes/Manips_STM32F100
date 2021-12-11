#include "stm32f10x.h"
#include "Pin_Mode_Names.h"

#ifndef __STM32_WRAPPER_GPIO_H
#define __STM32_WRAPPER_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* =======================================*/
/* 1 : Functions For PinAsInput Class --- */
/*----------------------------------------*/
	
void gpio_init_in_def(PinName pin);	
	
void gpio_init_in(PinName pin, PinInMode mode);

static void _gpio_init_in(PinName pin, PinInMode mode );

int gpio_read (PinName thepin);	
	
static int get_gpio_in_mode (PinInMode mode);	
/*==========================================*/

	
/*=============================================*/
/* --- 2 : Functions For xxPinAsOutput Class --*/
/*---------------------------------------------*/
void mycgpio_init_out_def(PinName pin);
	
void mycgpio_init_out (PinName pin, PinOutMode mode);
	
void mycgpio_init_out_ex (PinName pin, PinOutMode mode, PinSpeed speed);
	
static void myc_gpio_init_out(PinName pin, PinOutMode mode, PinSpeed speed);

void mycgpio_write(PinName pin, int value);

int mycgpio_read_out(PinName pin);

static int mycget_gpio_out_mode (PinOutMode mode);	
static int mycget_gpio_out_speed (PinSpeed speed);



/* --- 3 : Common Functions ---- */

/*  Get the GPIOx From PinName  */
static GPIO_TypeDef* mycget_gpio_port (PinName pin);
	


#ifdef __cplusplus
}
#endif


#endif //__STM32_WRAPPER_GPIO_H
