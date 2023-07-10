#include <stdio.h>
#include <string.h>
int main(void)
{
    //char string1[100] = "BBBBBBBBBBBBBB"; // initialize string1
    //printf("string1 = %s\n", string1);
    //printf("string1 after memset = %s\n", (char *) memset(string1, 'b', 20));
    printf("\nError Msg. for 2 is %s",strerror(3));
}