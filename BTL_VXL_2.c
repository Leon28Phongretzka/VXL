#include<stdio.h>
#include<math.h>
#include<string.h>
void Ceasar_Cipher_Encrypt(char *text)
{
    // Ceasar Cipher Encryption with key from 0 to 25
    for(int i=0; i<26; i++)
    {
        printf("Key %d: ", i);
        for(int j=0; j<strlen(text); j++)
        {
            if(text[j] >= 'A' && text[j] <= 'Z')
            {
                printf("%c", (text[j] - 'A' + i) % 26 + 'A');
            }
            else if(text[j] >= 'a' && text[j] <= 'z')
            {
                printf("%c", (text[j] - 'a' + i) % 26 + 'a');
            }
            else
            {
                printf("%c", text[j]);
            }
        }
        printf("\n");
    }
}
int main()
{
    char text[2049]; scanf("%s",text);
    // Ceasar Cipher Encryption with key from 0 to 25
    Ceasar_Cipher_Encrypt(text);
    
}