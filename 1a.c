#include <stdio.h>																											 
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "DrvPWM.h"
#include "DrvADC.h"
#include "LCD_Driver.h"
#include "Driver\DrvGPIO.h"
 int32_t main (void)
{  char value[15];  
    			   
	float volt = 0;
	UNLOCKREG();
	DrvSYS_Open(12000000);
	LOCKREG();
	//InitPWM(6);//inbuilt
	Initial_panel();  // initialize LCD pannel
  clr_all_panel();  // clear LCD panel 
  print_lcd(0,"variable reistor");
	DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP , 0x40,INTERNAL_HCLK , 1); 	//0x40 FOR CHANNEL 6
	while(1)
   {
    DrvADC_StartConvert();   // start A/D conversion
    //while(DrvADC_IsConversionDone()==FALSE);
     PWMA->CMR0=ADC->ADDR[6].RSLT<<4;
		 volt = ((float)ADC->ADDR[6].RSLT/4095.0  )*5;
    sprintf(value,"%fV",volt);  //ADC CHANNEL 6
		print_lcd(1, value);
    }
	}
