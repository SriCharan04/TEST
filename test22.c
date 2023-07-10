#include <stdio.h>

struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
};

int main(void)
{
    FILE *Ptr;

    if((Ptr = fopen("accounts.dat","rb+")) == NULL)
    {
        printf("%s","File could not be opened");
    }

    else 
    {
        printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name","First Name", "Balance");
        // read all records from file (until eof)
        while (!feof(Ptr)) 
        {
            // create clientData with default information
            struct clientData client = {0, "", "", 0.0};
            int result = fread(&client, sizeof(struct clientData), 1, Ptr);
            // display record
            if (result != 0 && client.acctNum != 0) 
            {
                printf("%-6d%-16s%-11s%10.2f\n",
                client.acctNum, client.lastName,
                client.firstName, client.balance);
            }
        }
    fclose(Ptr); // fclose closes the file
    }
}
