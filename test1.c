#include <stdio.h>

int main()
{
    int array[10] = {2,5,6,3,7,21,5,9,6,5};
    printf("%lu",sizeof(array));
    //traverse the array
    puts("Array before: ");
    for (int i = 0; i < 10; ++i)
    {
        printf("%4d",array[i]);
    }

    //Now bubble sorting the array
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (array[j] > array[i])
            {
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
    }

    //Traversing the sorted array
    puts("Array after: ");
    for (int i = 0; i < 10; ++i)
    {
        printf("%4d",array[i]);
    }
    
}