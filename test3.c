#include <stdio.h>
#include <ctype.h>
int main()
{
    void ConvertUpperCase(char *);
    void PrintChars(const char *);

    char string[] = "CharacTers And 66";
    printf("String before Converting: %s",string);
    ConvertUpperCase(string);
    PrintChars(string);
    puts("");
}

void ConvertUpperCase(char *SPtr)
{
    while (*SPtr != '\0')
    {
        *SPtr = toupper(*SPtr);
        ++SPtr;
    }
}

void PrintChars(const char *SPtr)
{
    for (;*SPtr != '\0';++SPtr)
    {
        printf("%c", *SPtr);
    }
}
