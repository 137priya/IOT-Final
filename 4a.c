#include <stdio.h>																											 
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "DrvPWM.h"
#include "DrvADC.h"
#include "LCD_Driver.h" 
 int32_t main (void)
{    
	UNLOCKREG();
	LOCKREG();
	InitPWM();
	DrvADC_Open(ADC_SINGLE_END,ADC_SINGLE_OP , 0x80,INTERNAL_HCLK , 1); 	
	while(1)
   {
    DrvADC_StartConvert();   // start A/D conversion
    while(DrvADC_IsConversionDone()==FALSE);
     PWMA->CMR0=ADC->ADDR[7].RSLT<<4;	 
    }
}	
