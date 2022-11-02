Ceasar_Cipher_Decrypt_Toupper:                  // Call Ceasar_Cipher_Decrypt_Toupper
        push    {r11, lr}                       // Put the string on the stack
        mov     r11, sp                         // Move the stack pointer to r11
        sub     sp, sp, #16
        str     r0, [r11, #-4]
        mov     r0, #0
        str     r0, [sp, #8]
        b       .LBB0_1
.LBB0_1:                                
        ldr     r0, [sp, #8]
        cmp     r0, #25
        bgt     .LBB0_14
        b       .LBB0_2
.LBB0_2:                                
        ldr     r1, [sp, #8]
        ldr     r0, .LCPI0_0
        bl      printf
        mov     r0, #0
        str     r0, [sp, #4]
        b       .LBB0_3
.LBB0_3:                                
        ldr     r0, [sp, #4]
        str     r0, [sp]                        
        ldr     r0, [r11, #-4]
        bl      strlen
        mov     r1, r0
        ldr     r0, [sp]                        
        cmp     r0, r1
        bhs     .LBB0_12
        b       .LBB0_4
.LBB0_4:                                
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        cmp     r0, #65
        blt     .LBB0_7
        b       .LBB0_5
.LBB0_5:                                
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        cmp     r0, #90
        bgt     .LBB0_7
        b       .LBB0_6
.LBB0_6:                                
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        ldr     r1, [sp, #8]
        sub     r0, r0, r1
        sub     r0, r0, #39
        ldr     r3, .LCPI0_3
        smull   r1, r2, r0, r3
        asr     r1, r2, #3
        add     r2, r1, r2, lsr #31
        mov     r3, #26
        mul     r1, r2, r3
        sub     r0, r0, r1
        add     r1, r0, #65
        ldr     r0, .LCPI0_2
        bl      printf
        b       .LBB0_10
.LBB0_7:                                
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        cmp     r0, #32
        bne     .LBB0_9
        b       .LBB0_8
.LBB0_8:                                
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r1, [r0, r1]
        ldr     r0, .LCPI0_2
        bl      printf
        b       .LBB0_9
.LBB0_9:                              
        b       .LBB0_10
.LBB0_10:                             
        b       .LBB0_11
.LBB0_11:                             
        ldr     r0, [sp, #4]
        add     r0, r0, #1
        str     r0, [sp, #4]
        b       .LBB0_3
.LBB0_12:                               
        ldr     r0, .LCPI0_1
        bl      printf
        b       .LBB0_13
.LBB0_13:                               
        ldr     r0, [sp, #8]
        add     r0, r0, #1
        str     r0, [sp, #8]
        b       .LBB0_1
.LBB0_14:
        mov     sp, r11
        pop     {r11, lr}
        bx      lr
.LCPI0_0:
        .long   .L.str
.LCPI0_1:
        .long   .L.str.2
.LCPI0_2:
        .long   .L.str.1
.LCPI0_3:
        .long   1321528399                      @ 0x4ec4ec4f
.L.str:
        .asciz  "Key %d: "

.L.str.1:
        .asciz  "%c"

.L.str.2:
        .asciz  "\n"-