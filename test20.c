#include <stdio.h>

int main(void)
{
    FILE *fPtr;

    if ((fPtr = fopen("strings.txt","w")) == NULL)
    {
        printf("%s","File could not be opened");
    }

    else
    {
        puts("Enter the account, name, and balance.");
        puts("Enter EOF to end input.");
        printf("%s","?");

        unsigned int account;
        char name[30];
        double balance;

        scanf("%d%29s%lf",&account,name,&balance);
        while(!(feof(stdin)))
        {
            fprintf(fPtr,"%d %s %.2f\n",account,name,balance);
            printf("%s","?");
            scanf("%d%29s%lf",&account,name,&balance);
        }

    fclose(fPtr);    
    }
}