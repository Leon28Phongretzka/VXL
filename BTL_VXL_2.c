#include<stdio.h>
#include<math.h>
int main()
{
    char text[100];
    int key;
    gets(text);
    scanf("%d", &key);
    // Ceasar Cipher Encryption
    for(int i = 0; text[i] != '\0'; ++i){
        char ch = text[i];
        if(ch >= 'a' && ch <= 'z'){
            ch = ch + key;
            if(ch > 'z'){
                ch = ch - 'z' + 'a' - 1;
            }
            text[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }
            text[i] = ch;
        }
    }
    printf("%s", text);
    return 0;
}