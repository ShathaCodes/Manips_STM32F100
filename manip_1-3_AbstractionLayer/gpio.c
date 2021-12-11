#include <gpio.h>

//retourne l’état (0 ou 1) du Pin passé en paramètre
int GPIO_TestPin(GPIO_Typedef *GPIOx, uint16_t GPIO_PIN)
{
	uint8_t test = GPIOx->IDR & GPIO_PIN;
	if ( test == 0 )
		return 0;
	else 
		return 1;
}

void GPIO_SetPin(GPIO_Typedef *GPIOx, uint16_t GPIO_PIN)
{
	GPIOx->BSRR = GPIO_PIN ;
}

void GPIO_ResetPin (GPIO_Typedef *GPIOx, uint16_t GPIO_PIN)
{
	GPIOx->BRR = GPIO_PIN ;
}

void GPIO_Init(GPIO_Typedef* GPIOx, GPIO_Struct * GPIO_InitStruct){
	
	int pinpos=0;
	
	for (pinpos=0;pinpos<16;pinpos++){
		if ((GPIO_InitStruct->GPIO_PIN & (1<<pinpos))!=0){
			if (pinpos<=7){
				GPIOx->CRL &= ~(0xF<<(4*pinpos));
				GPIOx->CRL |= GPIO_InitStruct->GPIO_Mode <<(4*pinpos);
			}
			else{
				GPIOx->CRH &= ~(0xF<<(4*(pinpos-8)));
				GPIOx->CRH |= GPIO_InitStruct->GPIO_Mode <<(4*(pinpos-8));
			}						
		}
	}
}