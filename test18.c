#include <stdio.h>
void displayBits(unsigned int value);

int main(void)
{
    unsigned int number1 = 65535;
    unsigned int mask = 1;
    displayBits(number1);
    displayBits(mask);
    puts("The result of combining the following with bitwise AND is");
    displayBits(number1 & mask);
    puts("\nThe result of combining the following with bitwise OR is");
    displayBits(number1 | mask);
}

void displayBits(unsigned int value)
{
    unsigned int displayMask = 1 << 31;
    printf("%10u = ", value);

    for (unsigned int c = 1; c <= 32; ++c)
    {
        int x = value & displayMask;
        putchar(x ? '1':'0');
        value <<= 1;

        if (c % 8 == 0)
        {
            putchar(' ');
        }
    }
    putchar('\n');
}
