void Ceasar_Cipher_Decrypt()
{
    // Ceasar Cipher Decryption with key from 0 to 25
    char text[2049];
    for(int i=0; i<26; i++)
    {
        for(int j=0; j<2048; j++)
        {
            if(text[j] >= 'A' && text[j] <= 'Z')
            {
                text[j] = ((text[j] - i - 39) % 26) + 65;
            }
            if(text[j] >= 'a' && text[j] <= 'z')
            {
                text[j] = ((text[j] - i - 39) % 26) + 97;
            }
        }
    }
}
