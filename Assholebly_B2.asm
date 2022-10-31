Ceasar_Cipher_Encrypt:
        push    {r11, lr}
        mov     r11, sp
        sub     sp, sp, #16
        str     r0, [r11, #-4]
        mov     r0, #0
        str     r0, [sp, #8]
        b       .LBB0_1
.LBB0_1:                                @ =>This Loop Header: Depth=1
        ldr     r0, [sp, #8]
        cmp     r0, #25
        bgt     .LBB0_16
        b       .LBB0_2
.LBB0_2:                                @   in Loop: Header=BB0_1 Depth=1
        mov     r0, #0
        str     r0, [sp, #4]
        b       .LBB0_3
.LBB0_3:                                @   Parent Loop BB0_1 Depth=1
        ldr     r0, [sp, #4]
        str     r0, [sp]                        @ 4-byte Spill
        ldr     r0, [r11, #-4]
        bl      strlen
        mov     r1, r0
        ldr     r0, [sp]                        @ 4-byte Reload
        cmp     r0, r1
        bhs     .LBB0_14
        b       .LBB0_4
.LBB0_4:                                @   in Loop: Header=BB0_3 Depth=2
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        cmp     r0, #65
        blt     .LBB0_7
        b       .LBB0_5
.LBB0_5:                                @   in Loop: Header=BB0_3 Depth=2
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        cmp     r0, #90
        bgt     .LBB0_7
        b       .LBB0_6
.LBB0_6:                                @   in Loop: Header=BB0_3 Depth=2
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        ldr     r1, [sp, #8]
        add     r0, r0, r1
        sub     r0, r0, #65
        ldr     r3, .LCPI0_2
        smull   r1, r2, r0, r3
        asr     r1, r2, #3
        add     r2, r1, r2, lsr #31
        mov     r3, #26
        mul     r1, r2, r3
        sub     r0, r0, r1
        add     r1, r0, #65
        ldr     r0, .LCPI0_1
        bl      printf
        b       .LBB0_12
.LBB0_7:                                @   in Loop: Header=BB0_3 Depth=2
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        cmp     r0, #97
        blt     .LBB0_10
        b       .LBB0_8
.LBB0_8:                                @   in Loop: Header=BB0_3 Depth=2
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        cmp     r0, #122
        bgt     .LBB0_10
        b       .LBB0_9
.LBB0_9:                                @   in Loop: Header=BB0_3 Depth=2
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r0, [r0, r1]
        ldr     r1, [sp, #8]
        add     r0, r0, r1
        sub     r0, r0, #97
        ldr     r3, .LCPI0_2
        smull   r1, r2, r0, r3
        asr     r1, r2, #3
        add     r2, r1, r2, lsr #31
        mov     r3, #26
        mul     r1, r2, r3
        sub     r0, r0, r1
        add     r1, r0, #97
        ldr     r0, .LCPI0_1
        bl      printf
        b       .LBB0_11
.LBB0_10:                               @   in Loop: Header=BB0_3 Depth=2
        ldr     r0, [r11, #-4]
        ldr     r1, [sp, #4]
        ldrb    r1, [r0, r1]
        ldr     r0, .LCPI0_1
        bl      printf
        b       .LBB0_11
.LBB0_11:                               @   in Loop: Header=BB0_3 Depth=2
        b       .LBB0_12
.LBB0_12:                               @   in Loop: Header=BB0_3 Depth=2
        b       .LBB0_13
.LBB0_13:                               @   in Loop: Header=BB0_3 Depth=2
        ldr     r0, [sp, #4]
        add     r0, r0, #1
        str     r0, [sp, #4]
        b       .LBB0_3
.LBB0_14:                               @   in Loop: Header=BB0_1 Depth=1
        ldr     r0, .LCPI0_0
        bl      printf
        b       .LBB0_15
.LBB0_15:                               @   in Loop: Header=BB0_1 Depth=1
        ldr     r0, [sp, #8]
        add     r0, r0, #1
        str     r0, [sp, #8]
        b       .LBB0_1
.LBB0_16:
        mov     sp, r11
        pop     {r11, lr}
        bx      lr
.LCPI0_0:
        .long   .L.str.1
.LCPI0_1:
        .long   .L.str
.LCPI0_2:
        .long   1321528399                      @ 0x4ec4ec4f
.L.str:
        .asciz  "%c"

.L.str.1:
        .asciz  "\n"