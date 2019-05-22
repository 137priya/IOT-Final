#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvADC.h"
void EINT1Callback() {
DrvGPIO_ClrBit(E_GPB,11); // GPB11 = 0 to turn on Buzzer
    DrvSYS_Delay(100000);        // Delay 
    DrvGPIO_SetBit(E_GPB,11); // GPB11 = 1 to turn off Buzzer    
    DrvSYS_Delay(100000);
}
int main (void)
{                       
    UNLOCKREG();               // unlock register for programming
      DrvSYS_Open(48000000);     // set System Clock to run at 48MHz
    LOCKREG();                   // lock register from programming
    DrvGPIO_Open(E_GPB, 11, E_IO_OUTPUT);   
DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE,E_MODE_EDGE,EINT1Callback);
while(1) {
    }
}
