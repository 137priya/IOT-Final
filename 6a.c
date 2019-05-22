#include <stdio.h>	
#include <string.h>																										 
#include "NUC1xx.h"
#include "LCD_Driver.h"
//static uint16_t TimerCounter=0;
static uint8_t Alarm_E=1;
//void Delay(int count);
void RTC_IRQHandler(void)
{
	uint32_t clock;
	char adc_value[15]="Clock:";
	/* tick */
	if(inpw(&RTC->RIIR)&0x2)
 	{
		clock=inpw(&RTC->TLR)&0xFFFFFF;
		sprintf(adc_value+6,"%02x",(clock>>16)&0xFF);
		sprintf(adc_value+9,"%02x",((clock)>>8)&0xFF);
		sprintf(adc_value+12,"%02x",clock&0xFF);
		adc_value[8]=':';
		adc_value[11]=':';
		Show_Word(0,13,' ');
		print_lcd(0, adc_value);
		outpw(&RTC->RIIR,2);
	}
	/* alarm */
	if(inpw(&RTC->RIIR)&0x1) 
	{
		print_lcd(1, "Alarm!!!!");
		GPIOC->DOUT&=0xefff;
		Alarm_E=0;
		outpw(&RTC->RIIR,1);
	}
}
int32_t main (void)
{
	UNLOCKREG();
	DrvSYS_Open(48000000);
//	SYSCLK->PWRCON.XTL32K_EN = 1;//Enable 32Khz for RTC clock source
//	SYSCLK->PWRCON.XTL12M_EN = 1;
//	SYSCLK->CLKSEL0.HCLK_S = 0;
	LOCKREG();

	Initial_panel();  //call initial pannel function
	clr_all_panel();
	                        
	//InitTIMER0();
	InitRTC();
	//InitWDT();
	START_RTC();

	/* Step 3. Initiate Time and Calendar  setting */
	RTC->TSSR.HR24_HR12     =1;//Set 24hour mode
	//Set time and calendar for loading register, Calendar„³ 09/1/19, Time„³ 13:20:00
	set_CLR(0,9,0,1,1,9);
	set_TLR(1,3,2,0,0,0);

	/* Step 4. Set alarm interrupt */
	//Set time and calendar for alarm register , Calendar„³ 09/1/19, Time„³ 13:30:00
	set_CAR(0,9,0,1,1,9);
	set_TAR(1,3,2,0,1,0);		
	//Enable alarm interrupt
	RTC->RIER.AIER = 1;
	RTC->RIER.TIER = 1;
	NVIC_EnableIRQ(RTC_IRQn);
		 	
	/* Synch field transmission & Request Identifier Field transmission*/
	while(Alarm_E)
	{
		UNLOCKREG();
		WDT->WTCR.WTR =1;//Write 1 to clear for safety
		LOCKREG();	
	}
	while(1)
	{
		__NOP();
	}
}
