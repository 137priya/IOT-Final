#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"

void Init_LED() // Initialize GPIO pins
{
    DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT);
    DrvGPIO_Open(E_GPC, 13, E_IO_OUTPUT);
    DrvGPIO_Open(E_GPC, 14, E_IO_OUTPUT);
    DrvGPIO_Open(E_GPC, 15, E_IO_OUTPUT);
               
    DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT);
    DrvGPIO_Open(E_GPA, 13, E_IO_OUTPUT);
    DrvGPIO_Open(E_GPA, 14, E_IO_OUTPUT);
    DrvGPIO_Open(E_GPA, 15, E_IO_OUTPUT);
               
}

int main (void)
{
    UNLOCKREG();                // unlock register for programming
  DrvSYS_Open(48000000);// set System Clock to run at 48MHz 
                          // 12MHz crystal input, PLL output 48MHz
    LOCKREG();                    // lock register from programming

  Init_LED();        // Initialize LEDs (four on-board LEDs below LCD panel)    

    while (1)                   // forever loop to keep flashing four LEDs one at a time
    {
        DrvGPIO_SetPortBits(E_GPC,0x7000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPC,0xb000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPC,0xd000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPC,0xe000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPC,0xf000);
        DrvSYS_Delay(100000);    
        
        DrvGPIO_SetPortBits(E_GPA,0x0000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPA,0x7000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPA,0xb000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPA,0xd000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPA,0xf000);
        DrvSYS_Delay(100000);
    
    }    
}
