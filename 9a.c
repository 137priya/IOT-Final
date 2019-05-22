#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvUART.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"
#include "LCD_Driver.h"

volatile uint32_t irqA_counter = 0;
volatile uint32_t irqE_counter = 0;

void GPIOAB_INT_CallBack(uint32_t GPA_IntStatus, uint32_t GPB_IntStatus)
{
     if ((GPA_IntStatus>>15) & 0x01)
			 irqA_counter++;
     print_lcd(3,"GPA interrupt !!");
}

void GPIOCDE_INT_CallBack(uint32_t GPC_IntStatus, uint32_t GPD_IntStatus, uint32_t GPE_IntStatus)
{  
     if ((GPC_IntStatus>>15) & 0x01) irqE_counter++;
     print_lcd(3,"GPC interrupt !!");

                   

    DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT); 

      DrvGPIO_ClrBit(E_GPB,11); 
    DrvSYS_Delay(100000);        
    DrvGPIO_SetBit(E_GPB,11);     
    DrvSYS_Delay(100000);            
}

int32_t main()
{
    char TEXT[16];

      UNLOCKREG();               
      DrvSYS_Open(48000000);     
     LOCKREG();   

    DrvGPIO_Open(E_GPA,15,E_IO_INPUT);
    DrvGPIO_Open(E_GPC,15,E_IO_INPUT);
  DrvGPIO_EnableInt(E_GPA, 15, E_IO_RISING, E_MODE_EDGE);
  DrvGPIO_EnableInt(E_GPC, 15, E_IO_RISING, E_MODE_EDGE);
  DrvGPIO_SetDebounceTime(5, 1);
    DrvGPIO_EnableDebounce(E_GPA, 15);
    DrvGPIO_EnableDebounce(E_GPC, 15);    
    
  DrvGPIO_SetIntCallback(GPIOAB_INT_CallBack, GPIOCDE_INT_CallBack);

  Initial_panel();
    clr_all_panel();
                    
    print_lcd(0,"Smpl_GPIO_Intr");
    
    while(1)
    {
        sprintf(TEXT,"IRQ_A: %d",irqA_counter);
        print_lcd(1, TEXT);
        sprintf(TEXT,"IRQ_E: %d",irqE_counter);
        print_lcd(2, TEXT);
    }
}
