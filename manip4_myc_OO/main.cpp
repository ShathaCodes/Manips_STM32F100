#include "stm32f10x.h"
#include "PinAsInput.h"
#include "PinAsOutput.h"

using namespace OOlayer;

	uint8_t EtatBouton;
		int i;	

	PinAsInput  MyButton (PA_0);


 //Class Instantiation: Clock and Pins config
	mycPinAsOutput mycGreenLed (PC_8);
	mycPinAsOutput mycBlueLed (PC_9);
	

int main ()
{	
	
	//Clock and Pins Config 
	//RCC->APB2ENR |=0x10;
	//GPIOC->CRH &= ~( 0xFF); 
	//GPIOC->CRH |=  0x22;
	
	
	//PC9 ON & PC8 OFF
	//GPIOC->BSRR=0x200;
	//GPIOC->BRR=0x100;
	
	
	//PC9 ON & PC8 OFF with OO repr
	mycGreenLed=1;
	mycBlueLed=0;
	

while (1)
	{		

		if (MyButton==1){
		
		//Invert PC8 and PC9 state ( ^: XOR)
		//GPIOC->ODR ^= 0x300; 			
		
		//Invert PC8 and PC9 using objects
		mycGreenLed = !mycGreenLed;
		mycBlueLed = !mycBlueLed;
		
		
		for (i=0xFFFFF; i>0; i--);
		}

	}
}
