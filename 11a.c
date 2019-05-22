#include <stdio.h>                                                                                                             
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "DrvPWM.h"
#include "DrvADC.h"
#include "LCD_Driver.h"

 int32_t main (void)
{ 
    //char value[15]; 
    int16_t x=0xffff;
    UNLOCKREG();
	DrvSYS_Open(48000000);
   // SYSCLK->PWRCON.XTL12M_EN = 1;     //Enable 12Mhz and set HCLK->12Mhz
   // SYSCLK->CLKSEL0.HCLK_S = 0;
    LOCKREG();
    InitPWM();
    Initial_panel();  // initialize LCD pannel
  clr_all_panel();  // clear LCD panel 
  print_lcd(0,"variable reistor");
  
while(1)
   {
   PWMA->CMR0=x;
         x = x - 1;
    DrvSYS_Delay(500);
         //sprintf(value,"%d",ADC->ADDR[0].RSLT);
        // print_lcd(1,"value");
    }
    }
