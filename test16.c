#include <stdio.h>

int main(void)
{
    float p = -3.141516;
    char z[9];
    int width = -10;
    int precision = 3;
    scanf("%8[^aeiou]",&z);
    printf("\n%s",z);
}