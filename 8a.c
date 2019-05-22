#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"
// External Interrupt Handler (INT button to trigger GPB15)
void EINT1Callback(void) 
{    
UNLOCKREG();                
      DrvSYS_Open(48000000);                      
    LOCKREG();                    
    DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT);
    DrvGPIO_SetPortBits(E_GPA,0x0000);
    DrvSYS_Delay(100000);
    DrvGPIO_SetPortBits(E_GPA,0xf000);
    DrvSYS_Delay(100000);    
}
void EINT0Callback(void)
{
UNLOCKREG();                
      DrvSYS_Open(48000000);                      
    LOCKREG();                    
    DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT);
    DrvGPIO_SetPortBits(E_GPC,0x0000);
    DrvSYS_Delay(100000);
    DrvGPIO_SetPortBits(E_GPC,0xf000);
    DrvSYS_Delay(100000);    
}
int main (void)
{
    UNLOCKREG();
    DrvSYS_SetOscCtrl(E_SYS_XTL12M, 1); 
    DrvSYS_Delay(5000);                 
    DrvSYS_SelectHCLKSource(0);        
    LOCKREG();
 
    DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT); 
    DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT); 
   
  DrvGPIO_Open(E_GPA, 12, E_IO_INPUT);                             
  DrvGPIO_Open(E_GPC, 12, E_IO_INPUT); 
                            
  DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT1Callback); 
  DrvGPIO_EnableEINT0(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT0Callback); 

  while(1)
    {
  }
}
