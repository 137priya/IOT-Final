PRESERVE8 ; Indicate the code here preserve  
; 8 byte stack alignment         
		THUMB     ; Indicate THUMB code is used       
		AREA    |.text|, CODE, READONLY
               
    EXPORT __main             
; Start of CODE area 
__main 
     ldr r1, =0x50004000  ; Base Address of C Port,Register PMD


     ldr r2, =0x08   ;  Dout Register 0x50004088 of C port
     ldr r3, =0x01   ;  For setting mode in PMD Register as output
     lsls  r4, r3, #24 ;  Setting shifting mode for setting 15th bit of C Port //24
     
     str r4, [r1]   ;  mode value loaded into mode register which is memory mapped to 0x 50004080
     ldr r4, =0xEFFF   ; Dout of C Port is set for Clearing 15th Bit
     adds r1, r1,r2  ;increment by address of Port C by two Words ,now the address is at 0x50004088
     str r4, [r1]    ; now your storing the r4-Dout value to the 0x50004088 ,for lighting the LED which is 
    ldr r1, =0x50004080  ; Base Address of C Port,Register PMD
    ldr r2, =0x08   ;  Dout Register 0x50004088 of C port
    ldr r3, =0x01   ;  For setting mode in PMD Register as output
    lsls  r4, r3, #24 ;  Setting shifting mode for setting 15th bit of C Port //24
    str r4, [r1]   ;  mode value loaded into mode register which is memory mapped to 0x 50004080
    ldr r4, =0xEFFF   ; Dout of C Port is set for Clearing 15th Bit
    adds r1, r1,r2  ;increment by address of Port C by two Words ,now the address is at 0x50004088
    str r4, [r1]
stop  b   stop               ;which is connected to C 15.
       end
