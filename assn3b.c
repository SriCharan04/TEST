#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int size;
int n;
float lamb;
int t_data_odd[size][3];
int t_data_even[size][3];
void user_input()
{
	printf("%s","Give the size of the dimension to be used in each side: ");
	scanf("%i", &size);

    printf("%s","Give the number of turns of the simulation to be run: ");
	scanf("%i", &n);

    printf("%s","Give a value of lambda (diffusive constant): ");
	scanf("%f", &lamb);
}


int main(int argc, char** argv)
{
    srand(time(NULL));
    user_input;
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(sqrt((i-44.5)*(i-44.5)+(j-44.5)*(j-44.5)) < 25.00)
            {
                t_data_even[i][j] = t_data_odd[i][j] = 100;
                
            }

            else
            {
                t_data_even[i][j] = t_data_odd[i][j] = 0;
            }
            t_data_even[j][0]= t_data_odd[j][0];
            t_data_even[j][1]= t_data_odd[j][1];
            
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int k = 1; k <= size - 1; k++)
        {
            for (int j = 1; j <= size - 1;j++)
            {
                if (j % 2 == 0)
                {
                    t_data_odd[j][k] -= 4 * t_data_odd[j][k];
                    t_data_odd[j][k] += lamb * (t_data_odd[j+1][k] + t_data_odd[j-1][k]+ t_data_odd[j][k+1] + t_data_odd[j][k-1]);
                }

                else if (j % 2 == 1)
                {
                    t_data_even[j][k] -= 4 * t_data_even[j][k];
                    t_data_even[j][k] += lamb * (t_data_even[j+1][k] + t_data_even[j-1][k]+ t_data_even[j][k+1] + t_data_even[j][k-1]);
                };
            }

            for (int i = 0; i < floor((size - 3)/2); i++) 
            {
                t_data_odd[0][i] = t_data_odd[1][i];
                t_data_even[0][i+1] = t_data_even[1][i+1];
            }
            if (size % 2 == 1)
            {
                t_data_odd[0][size-2] = t_data_odd[1][size-2];
            };

            for (int j = 0; j < size; j++) 
            {
                t_data_odd[j][0] = t_data_odd[j][1];
            
                if (size % 2 == 1)
                {
                    t_data_even[j][size-1] = t_data_odd[j][size];
                }

                else
                {
                    t_data_odd[j][size-1] = t_data_even[j][size];
                }
            }
        }   
    }
}
