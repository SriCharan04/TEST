#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    const char *string = "-51222% are admitted"; // initialize string
    char *stringPtr; // create char pointer
    //double d = strtod(string, &stringPtr);
    unsigned long d = strtoul(string,&stringPtr,6);
    printf("The string \"%s\" is converted to the\n", string);
    printf("double value %.2ld and the string \"%s\"\n", d, stringPtr);
}