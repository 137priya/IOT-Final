#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"
#include "NUC1xx-LB_002\LCD_Driver.h"


int main (void)
{
int32_t number;
    char TEXT0[16]="SmplKeypad";

char TEXT1[16];
    UNLOCKREG();                // unlock register for programming
  DrvSYS_Open(48000000);// set System Clock to run at 48MHz 
                          // 12MHz crystal input, PLL output 48MHz
    LOCKREG();                    // lock register from programming

        
Initial_panel(); 
    clr_all_panel();    
        
    print_lcd(0,TEXT0); // print title
    
    while (1)                   // forever loop to keep flashing four LEDs one at a time
    {number=DrvGPIO_GetPortBits(E_GPA);
            
     sprintf(TEXT1,"%x",number); // print scankey input to string              
    print_lcd(1,TEXT1); 
if(number==0xfffe)
    print_lcd(2,"A0");    
else if(number==0xfffd)
    print_lcd(2,"A1");
else if(number==0xfffb)
    print_lcd(2,"A2");
else if(number==0xfff7)
    print_lcd(2,"A3");
    }

}
