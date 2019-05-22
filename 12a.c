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
    UNLOCKREG();               
  DrvSYS_Open(48000000);
                          
    LOCKREG();                    


    Initial_panel(); 
    clr_all_panel();    
        
    print_lcd(0,TEXT0);
    
    while (1)                   
    {
        number=DrvGPIO_GetPortBits(E_GPA);
            
         sprintf(TEXT1,"%x",number);           
        print_lcd(1,TEXT1); 
        if(number==0xfffe)
            print_lcd(2,"A0 grounded");
        else if(number==0xffff)
            print_lcd(2,"not grounded");     // grounded ?
    }

}

