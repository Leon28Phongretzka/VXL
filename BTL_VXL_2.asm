
mov r0, #4000H              ;luu chuoi sau khi giai ma bat dau tu dia chi 4000H
mov r1, #0H                 ;dia chi cua phan tu dau tien trong chuoi ma hoa
mov r2, #0                  ;key giai ma
mov r3, #2048               ;so luong ky tu cua chuoi
mov r4, #25                 ;so key can giai ma

@ lay key hien tai ra de giai ma, giai ma xong tang key len 1
loop
    ldr r5, r2              ;lay key hien tai ra de giai ma, luu vao r5
    add r2, r2, #1          ;tang key len 1 de giai ma lan sau (key = key + 1)
    mov r6, r5              ;luu key vao r6
    cmp r5, r4              ;so sanh key voi so key can giai ma
    bge end                 ;neu key >= so key can giai ma thi ket thuc              
    b   lbb01               ;neu key < so key can giai ma thi nhay toi lbb01

@ giai ma dich vong tung ky tu tu ky tu dau tien toi ky tu thu 2048
lbb01
    ldr r7, [r1], #1        ;lay ky tu hien tai ra va sau do tang gia tri dia chi cua ky tu len 1
    mov r8, r7              ;luu ky tu hien tai vao r8
    cmp r8, #65             ;so sanh ky tu hien tai voi ky tu 'A'
    blt lbb02               ;neu ky tu hien tai < 'A' thi nhay toi lbb02
    cmp r8, #90             ;so sanh ky tu hien tai voi ky tu 'Z'
    bgt lbb02               ;neu ky tu hien tai > 'Z' thi nhay toi lbb02
    @ giai ma ky tu
    sub r8, r8, #65         ;tru ky tu hien tai voi ky tu 'A'
    sub r8, r8, r6          ;tru ky tu hien tai voi key hien tai, de giai ma ky tu
    cmp r8, #0              ;so sanh ky tu hien tai voi 0
    addlt r8, r8, #26       ;neu ky tu hien tai < 0 thi cong ky tu hien tai voi 26
    @ luu ky tu da giai ma vao chuoi
    add r8, r8, #65         ;cong ky tu hien tai voi ky tu 'A'
    str r8, [r0], #1        ;luu ky tu da giai ma vao chuoi va sau do tang gia tri dia chi cua ky tu da giai ma len 1
    @ kiem tra xem da giai ma het chuoi chua
    sub r3, r3, #1          ;tru so luong ky tu con lai trong chuoi ma hoa
    cmp r3, #0              ;so sanh so luong ky tu con lai voi 0
    bne lbb01               ;neu so luong ky tu con lai > 0 thi nhay toi loop

@ neu giai ma gap ky tu khong phai la ky tu 'A' den 'Z' thi nhay toi lbb02
lbb02
    @ neu ky tu khong phai la ky tu 'A' den 'Z' thi luu ky tu do vao chuoi
    str r7, [r0], #1        ;luu ky tu vao chuoi va sau do tang gia tri dia chi cua ky tu len 1
    @ kiem tra xem da giai ma het chuoi chua
    sub r3, r3, #1          ;tru so luong ky tu con lai trong chuoi ma hoa
    cmp r3, #0              ;so sanh so luong ky tu con lai voi 0
    bne lbb01               ;neu so luong ky tu con lai > 0 thi nhay toi loop

@ ket thuc
end
    b   end                 ;ket thuc
    END
```




    
    
