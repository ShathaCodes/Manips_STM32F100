#include <stdint.h>

#define   Reg_Enable_RCC     (uint32_t*) 0x40021018  // adresse du registre APBxENR (pour activer les GPIOs utils�s)
#define   GPIOC_CRL		     (uint32_t*) 0x40011000 // adresse du registre (GPIO C)
#define   GPIOC_CRH		     (uint32_t*) 0x40011004  // adresse du registre (GPIO C)
#define   Reg_BSRR_Led	     (uint32_t*) 0x40011010 // adresses du registre permettant la mise � 1 des bits du GPIO C
#define   Reg_BRR_Led	     (uint32_t*) 0x40011014 // adresses du registre permettant la mise � 0 des bits du GPIO C



main()
{
 int i;
 
 // activer l'horloge du port C (reli� aux leds)
 *Reg_Enable_RCC |= 0x10;

 // Configurer les bits reli�s aux leds
 *GPIOC_CRH &= ~( (uint32_t)0xFF);
 *GPIOC_CRH |= 0x22;
 
 while (1)
  {
    // allumer les deux leds
 *Reg_BSRR_Led = 3<<8; //0x300 = 11 0000 0000
 
  for(i=0xFFFFF; i != 0; i--); // Delay
  
  // Eteindre les deux leds.
 *Reg_BRR_Led = 3<<8; //0x300
 
 for(i=0xFFFFF; i != 0; i--); // Delay
   }
}
