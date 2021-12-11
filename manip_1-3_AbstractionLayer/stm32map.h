#include <stdint.h>



//GPIO BASE ADDRESSES REGISTERS
#define   GPIOA_BASE	  (0x40010800)
#define   GPIOB_BASE	  (0x40010C00)
#define   GPIOC_BASE	  (0x40011000)


//Define GPIO_Typedef strcuture containing The GPIO Registers

typedef struct {
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
} GPIO_Typedef;


//define Pointers to GPIO Strcutures 
	
#define GPIOA  ((GPIO_Typedef*) GPIOA_BASE)
#define GPIOB  ((GPIO_Typedef*) GPIOB_BASE)
#define GPIOC  ((GPIO_Typedef*) GPIOC_BASE)
