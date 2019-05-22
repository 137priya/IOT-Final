#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvADC.h"
void EINT1Callback() {
DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT);
    DrvGPIO_Open(E_GPA, 13, E_IO_OUTPUT);
    DrvGPIO_Open(E_GPA, 14, E_IO_OUTPUT);
    //DrvGPIO_Open(E_GPA, 15, E_IO_OUTPUT);
    //DrvGPIO_SetPortBits(E_GPA,0x0000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPA,0x7000);
    //    DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPA,0xb000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPA,0xd000);
        DrvSYS_Delay(100000);
        DrvGPIO_SetPortBits(E_GPA,0xf000);
        //DrvSYS_Delay(100000);
}
int main (void)
{                       
    UNLOCKREG(); 
    DrvSYS_Open(48000000); 
    LOCKREG();
DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE,E_MODE_EDGE,EINT1Callback);
    while(1) {
    }
}
