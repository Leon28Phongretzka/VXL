Ceasar_Cipher_Decrypt:                                  // Call the function
        push    {r11, lr}                               // put the string on the stack
        mov     r11, sp                                 // r11 is the stack pointer
        sub     sp, sp, #16                             // move the stack pointer down 16 bytes
        str     r0, [r11, #-4]                          // store the string in the stack
        mov     r0, #0                                  // set the key to 0
        str     r0, [sp, #8]                            // store the key in the stack
        b       .LBB0_1                                 // jump to the loop 1

.LBB0_1:                                                // loop 1 - it means "for(int i=0; i<26;)"
        ldr     r0, [sp, #8]                            // load the key ( index i ) from the stack
        cmp     r0, #25                                 // compare the key to 25
        bgt     .LBB0_16                                // if the key is greater than 25, jump to the end
        b       .LBB0_2                                 // jump to the loop 2 

.LBB0_2:                                                // loop 2 - it prints the key
        ldr     r1, [sp, #8]                            // load the key from the stack ( r1 = i )
        ldr     r0, .LCPI0_0                            // load the string "Key %d: " into r0
        bl      printf                                  // call the printf function to printf "Key %d: "
        mov     r0, #0                                  // set the index to 0
        str     r0, [sp, #4]                            // store the index in the stack
        b       .LBB0_3                                 // jump to the loop 3

.LBB0_3:                                                // loop 3 - it means "for(int j=0; j<strlen(text);)""
        ldr     r0, [sp, #4]                            // load the index j from the stack
        str     r0, [sp]                                // store the index in the stack
        ldr     r0, [r11, #-4]                          // load the string from the stack
        bl      strlen                                  // call the strlen ( string_length ) function to get the length of the string - with this problem this is 2048
        mov     r1, r0                                  // move the length of the string into r1
        ldr     r0, [sp]                                // load the index j from the stack
        cmp     r0, r1                                  // compare the index j to the length of the string
        bhs     .LBB0_14                                // if the index j is greater than or equal to the length of the string, jump to the end
        b       .LBB0_4                                 // jump to the loop 4

.LBB0_4:                                                // loop 4 - it means "if(text[j] >= 'A')"
        ldr     r0, [r11, #-4]                          // load the string from the stack
        ldr     r1, [sp, #4]                            // load the index from the stack
        ldrb    r0, [r0, r1]                            // load each character from the string at the index
        cmp     r0, #65                                 // compare the character to 'A'
        blt     .LBB0_7                                 // if the character is less than 'A', jump to the loop 7
        b       .LBB0_5                                 // jump to the loop 5

.LBB0_5:                                                // loop 5 - it means "if(text[j] <= 'Z')"
        ldr     r0, [r11, #-4]                          // load the string from the stack
        ldr     r1, [sp, #4]                            // load the index from the stack
        ldrb    r0, [r0, r1]                            // load each character from the string at the index
        cmp     r0, #90                                 // compare the character to 'Z'
        bgt     .LBB0_7                                 // if the character is greater than 'Z', jump to the loop 7
        b       .LBB0_6                                 // jump to the loop 6

.LBB0_6:                                                // loop 6 - it means "text[j] = (text[j] - 'A') - key + 26) % 26 + 'A'"
        ldr     r1, [sp, #4]                            // load the index from the stack to r1
        ldrb    r0, [r0, r1]                            // load each character from the string at the index to r0
        ldr     r1, [sp, #8]                            // load the key from the stack to r1
        sub     r0, r0, r1                              // subtract the key from the character 
        sub     r0, r0, #39                             // subtract 39 = subtract 'A' and plus 26 and now r0 is value after the original character minus the key and minus 'A'
        ldr     r3, .LCPI0_3                            // load LCPI0_3 into r3 with the value 0x4ec4ec4f
        // 6 next instruction use to mod the previous result with 26; r0 is "text[j] - 'A' + 26 - key" and r3 is 0x4ec4ec4f
        smull   r1, r2, r0, r3                          // (r1:r2) = r0 * r3 => r1 is the high 32 bits of the result and r2 is the low 32 bits of the result
        asr     r1, r2, #3                              // r1 = r2 >> 3
        add     r2, r1, r2, lsr #31                     // r2 = r1 + (r2 >> 31)
        mov     r3, #26                                 // r3 = 26
        mul     r1, r2, r3                              // r1 = r2 * r3 
        sub     r0, r0, r1                              // r0 = r0 - r1 
        // end of mod and now r0 is the value after the original character minus the key and minus 'A', i.e. r0 = ( char - key - 'A' + 26 )  mod 26
        add     r1, r0, #65                             // r1 = r0 + 65 = r0 + 'A'
        ldr     r0, .LCPI0_2                            // load LCPI0_2 into r0 with the value 0x4ec4ec4f
        bl      printf                                  // call the printf function to printf "%c"
        b       .LBB0_12                                // jump to the loop 12

.LBB0_7:                                                // loop 7 - it means "if(text[j] >= 'a')"
        ldr     r0, [r11, #-4]                          // load the string from the stack
        ldr     r1, [sp, #4]                            // load the index from the stack
        ldrb    r0, [r0, r1]                            // load each character from the string at the index
        cmp     r0, #97                                 // compare the character to 'a'
        blt     .LBB0_10                                // if the character is less than 'a', jump to the loop 10
        b       .LBB0_8                                 // jump to the loop 8
.LBB0_8:                                                // loop 8 - it means "if(text[j] <= 'z')"
        ldr     r0, [r11, #-4]                          // load the string from the stack
        ldr     r1, [sp, #4]                            // load the index from the stack
        ldrb    r0, [r0, r1]                            // load each character from the string at the index
        cmp     r0, #122                                // compare the character to 'z'
        bgt     .LBB0_10                                // if the character is greater than 'z', jump to the loop 10
        b       .LBB0_9                                 // jump to the loop 9

.LBB0_9:                                                // loop 9 - it means "text[j] = ((text[j] - 'a') - key) % 26 + 'a'"
        ldr     r0, [r11, #-4]                          // load the string from the stack
        ldr     r1, [sp, #4]                            // load the index from the stack
        ldrb    r0, [r0, r1]                            // load each character from the string at the index
        ldr     r1, [sp, #8]                            // load the key from the stack
        sub     r0, r0, r1                              // subtract the key from the character
        sub     r0, r0, #71                             // the result of r0 = "char" - 'a' + 26 - key
        ldr     r3, .LCPI0_3                            // load LCPI0_3 into r3 with the value 0x4ec4ec4f
        smull   r1, r2, r0, r3                          // (r1:r2) = r0 * r3 => r1 is the high 32 bits of the result and r2 is the low 32 bits of the result
        asr     r1, r2, #3                              // r1 = r2 >> 3
        add     r2, r1, r2, lsr #31                     // r2 = r1 + (r2 >> 31)
        mov     r3, #26                                 // r3 = 26
        mul     r1, r2, r3                              // r1 = r2 * r3
        sub     r0, r0, r1                              // r0 = r0 - r1
        add     r1, r0, #97                             // r1 = r0 + 97 = r0 + 'a'
        ldr     r0, .LCPI0_2                            // load LCPI0_2 into r0 - i.e. "%c" - define to print char
        bl      printf                                  // call the printf function to printf "%c"
        b       .LBB0_11                                // jump to the loop 11

.LBB0_10:                                               // loop 10 - it means if the characters that are not letters, print them as they are ( immediately )
        ldr     r0, [r11, #-4]                          // load the string from the stack
        ldr     r1, [sp, #4]                            // load the index from the stack
        ldrb    r1, [r0, r1]                            // load each character from the string at the index
        ldr     r0, .LCPI0_2                            // load LCPI0_2 into r0 - i.e. "%c" - define to print char
        bl      printf                                  // call the printf function to printf "%c"
        b       .LBB0_11                                // jump to the loop 11

.LBB0_11:                                               // loop 11 - if char are lower letters or not letters, print the result after decrypt and jump to the loop 12
        b       .LBB0_12                                // jump to the loop 12

.LBB0_12:                                               // loop 12 - if char are upper letters, print the result after decrypt and jump to the loop 13
        b       .LBB0_13                                // jump to the loop 13

.LBB0_13:                                               // loop 13 - it means increase the index j and jump to the loop 3 to continue search in the string
        ldr     r0, [sp, #4]                            // load the index from the stack
        add     r0, r0, #1                              // increment the index
        str     r0, [sp, #4]                            // store the index in the stack
        b       .LBB0_3                                 // jump to the loop 3

.LBB0_14:                                               // loop 14 - this loop print "\n" in order to end the line of each string after decrypt it with key k
        ldr     r0, .LCPI0_1                            // load LCPI0_1 into r0 - i.e. r0 = "\n"
        bl      printf                                  // call the printf function to printf "\n"
        b       .LBB0_15                                // jump to the loop 15

.LBB0_15:                                               // loop 15 - i++ - increase the index i and jump to the loop 1 to continue search in the array of strings
        ldr     r0, [sp, #8]                            // load the key from the stack
        add     r0, r0, #1                              // increment the key
        str     r0, [sp, #8]                            // store the key in the stack
        b       .LBB0_1                                 // jump to the loop 1
        
.LBB0_16:                                               // loop 16 - it means "if(key >= 26)" - if the key is greater than 26, end the program
        mov     sp, r11                                 // move the stack pointer to the r11
        pop     {r11, lr}                               // pop the r11 and the lr from the stack - end the function
        bx      lr                                      // return from the function
.LCPI0_0:
        .long   .L.str
.LCPI0_1:
        .long   .L.str.2
.LCPI0_2:
        .long   .L.str.1
.LCPI0_3:
        .long   1321528399                      @ 0x4ec4ec4f
main:
        push    {r4, r5, r11, lr}                       // push the r4, r5, r11 and the lr to the stack
        add     r11, sp, #8                             // move the stack pointer to the r11
        sub     sp, sp, #8                              // decrease the stack pointer by 8 bytes
        sub     sp, sp, #2048                           // decrease the stack pointer by 2048 bytes
        ldr     r0, .LCPI1_0                            // load LCPI1_0 into r0 - i.e. r0 = "Enter the key: "
        add     r1, sp, #7                              // move the stack pointer to the r1
        str     r1, [sp]                                // store the r1 in the stack
        bl      scanf                                   // call the scanf function to scanf "Enter the key: "
        ldr     r0, [sp]                                // load the key from the stack
        bl      Ceasar_Cipher_Decrypt                   // call the Ceasar_Cipher_Decrypt function to decrypt the strings with the key
        mov     r0, #0                                  // r0 = 0
        sub     sp, r11, #8                             // move the stack pointer to the r11
        pop     {r4, r5, r11, lr}                       // pop the r4, r5, r11 and the lr from the stack - end the function
        bx      lr                                      // return from the function
.LCPI1_0:
        .long   .L.str.3
.L.str:
        .asciz  "Key %d: "

.L.str.1:
        .asciz  "%c"

.L.str.2:
        .asciz  "\n"

.L.str.3:
        .asciz  "%s"