/* ***************************************************************************/
/* WRAPPER LAYER : ADAPT OO Pin REPRESENTATION (mbed) TO ST Firmware Libraray*/
/* OO Representation : PA_0 = 0x01, PA_1=0x01, ...., PA_15=0x0F              */
/*                   : PB_0 = 0x11, PB_1=0x11, ...., PB_15=0x1F              */
/*																																           */
/* OO --> ST Firmware  : PA_0 --> GPIOA, GPIO_Pin_0 							           */
/*											 PB_12 --> GPIOB, GPIO_Pin_12							           */
/* Emir DAMERGI  -  INSAT 2020                                               */

/* ***************************************************************************/

#include "stm32_wrapper_gpio.h"

/*================================================*/
/*     Part 1: Functions For PinAsInput Class     */
/*================================================*/


/*=== Functions Called by The PinAsInput Constructors ===*/

/*Constructor Without Mode = Default = Floating*/
void gpio_init_in_def(PinName pin) 
{
    gpio_init_in (pin, InDefault);
}

/*Constructor With Mode */
void gpio_init_in (PinName pin, PinInMode mode)
{
    _gpio_init_in(pin, mode);
}


/*=== Function To get gpio mode for ST FW lib === */
static int get_gpio_in_mode (PinInMode mode)
{	
	switch (mode){
		case 0: return GPIO_Mode_IN_FLOATING;
		case 1: return GPIO_Mode_IPU;
		case 2: return GPIO_Mode_IPD;
		default: return GPIO_Mode_IN_FLOATING; 
		}
}

/*=== Function To read Pin Value from IDR ====== */
	int gpio_read(PinName pin)
{
	int pinID = (pin & 0x0F);
	return ( (mycget_gpio_port(pin)->IDR) & (1<<pinID)) ;
}

/*--------------------------------------------------------------*/
/*   INITIALLIZATION FUNCTION for PinAsInput Objects :          */          
/*      - Translates OO Pin Represetation (Px_i) to ST FWL      */
/*      - And Calls ST FWLibrary Functions                      */
/*--------------------------------------------------------------*/
static void _gpio_init_in(PinName pin, PinInMode mode)
{

		//get the gpioID from PinName (0 for GPIOA, 1 for GPIOB, ...) 	
	int gpioID = (pin & 0xF0) >> 4; 
	
	RCC_APB2PeriphClockCmd( 1<<(gpioID+2) , ENABLE);	
	
	  //convert gpioID to GPIOx
	GPIO_TypeDef* GPIOx = mycget_gpio_port(pin);


		//Fills GPIO Structure and Calls GPIO_Init (ST FW Lib)
	GPIO_InitTypeDef GPIO_InitStruct; 

	GPIO_InitStruct.GPIO_Pin = 1<<(pin & 0x0F);
	
	GPIO_InitStruct.GPIO_Mode = (GPIOMode_TypeDef)get_gpio_in_mode(mode);

	GPIO_Init( GPIOx,  &GPIO_InitStruct);		
	}

/*=========== End PinAsInput Class Functions =============*/


	
/*-------------------------------------------------*/
	/* Common Function : To get GPIOx From PinName Value */
/*_________________________________________________*/
	
static GPIO_TypeDef* mycget_gpio_port (PinName pin)
{
	int gpioID = (pin & 0xF0) >> 4; 
		
	GPIO_TypeDef* GPIOx;
	
	switch (gpioID){
		case 0x00: GPIOx=GPIOA; break;
		case 0x01: GPIOx=GPIOB; break;
		case 0x02: GPIOx=GPIOC; break;
		case 0x03: GPIOx=GPIOD; break;
		default: break;
		}
	return GPIOx;
}



/*=================================================*/
/*     Part 2: Functions For PinAsOutput Class      */
/*=================================================*/


/*== Functions Called by The PinAsOutput Constructors==*/

/* Without Mode/Speed = Default = OutputPP, 2Mhz*/
void mycgpio_init_out_def(PinName pin)
{
    mycgpio_init_out (pin, OutDefault);
}


/* With Mode , Default Speed = 2 Mhz  */
void mycgpio_init_out (PinName pin, PinOutMode mode)
{
    mycgpio_init_out_ex (pin, mode, SpeedDefault);
}

/*  With Mode and Speed */
void mycgpio_init_out_ex (PinName pin, PinOutMode mode, PinSpeed speed)
{
    myc_gpio_init_out(pin, mode, speed);
}



/*==== Function To read Pin Value from ODR ===*/
/*--------------------------------------------*/
	int mycgpio_read_out(PinName pin)
{
	int pinID = (pin & 0x0F);
	return ( (mycget_gpio_port(pin)->ODR) & (1<<pinID)) ;
}



/*==== Function To read Pin Value from IDR === */
/*--------------------------------------------*/
	void mycgpio_write(PinName pin, int value)
{
	GPIO_TypeDef* GPIOx = mycget_gpio_port(pin);
	if (!value)
  {
    GPIOx->BRR = 1<<(pin & 0x0F);
  }
  else
  {
    GPIOx->BSRR=1<<(pin & 0x0F);
  }
}


/*==== Function To get the ST FW Library mode from OO mode  === */
/*-------------------------------------------------------------*/
static int mycget_gpio_out_mode (PinOutMode mode)
{	
	switch (mode){
		case 0: return GPIO_Mode_Out_PP;
		case 1: return GPIO_Mode_Out_OD;
		case 2: return GPIO_Mode_AF_PP;
		case 3: return GPIO_Mode_AF_OD;
		default: return GPIO_Mode_Out_PP; 
		}
}

/*==== Function To get the ST FW Library speed from OO mode  === */
/*-------------------------------------------------------------*/
static int mycget_gpio_out_speed (PinSpeed speed)
{	
	switch (speed){
		case 0: return GPIO_Speed_2MHz;
		case 1: return GPIO_Speed_10MHz;
		case 2: return GPIO_Speed_50MHz;
		default: return GPIO_Speed_2MHz; 
		}
}


/*===============================================================*/
/*           INITIALLIZATION FUNCTION for PinAsoutput Objects :                          */
/*      - Translates OO Pin Represetation (Px_i) to ST FWL       */
/*      - And Calls ST FWLibrary Functions                       */
/*================================================================*/
static void myc_gpio_init_out(PinName pin, PinOutMode mode, PinSpeed speed)
{

	//get the gpioID from PinName (0 for GPIOA, 1 for GPIOB, ...) 	
	int gpioID = (pin & 0xF0) >> 4; 
	
	RCC_APB2PeriphClockCmd( 1<<(gpioID+2) , ENABLE);	
	
	  //convert gpioID to GPIOx
	GPIO_TypeDef* GPIOx = mycget_gpio_port(pin);


		//Fills GPIO Structure and Calls GPIO_Init (ST FW Lib)
	GPIO_InitTypeDef GPIO_InitStruct; 

	GPIO_InitStruct.GPIO_Pin = 1<<(pin & 0x0F);
	
	GPIO_InitStruct.GPIO_Mode = (GPIOMode_TypeDef)mycget_gpio_out_mode(mode);
	
	GPIO_InitStruct.GPIO_Speed = mycget_gpio_out_speed(speed);

	GPIO_Init( GPIOx,  &GPIO_InitStruct);		

}
