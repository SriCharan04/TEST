#include <stdio.h>
#define SIZE 10

void reverse(const char * const SPtr);
int main(void)
{
    char sentence[SIZE];

    puts("Enter a line of text");
    fgets(sentence,SIZE,stdin);

    puts("\nThe string printed in reverse is:");
    reverse(sentence);
}

void reverse(const char * const SPtr)
{
    if (SPtr[0] == '\0')
    {
        return;
    }
    
    else
    {
        reverse(SPtr+1);
        putchar(SPtr[0]);
    }
}