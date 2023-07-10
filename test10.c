#include <stdio.h>
#define SIZE 10

int main(void)
{
    int c;
    int i = -1;
    char sentence[SIZE];
    puts("Enter a line of text");
    while((i < SIZE-1)&&((c = getchar()) != '\n'))
    {
        *(sentence+(++i)) = c;
    }
    *(sentence+i)='\0';

    printf("The entered string is\n%s",sentence);
}