#include <stdio.h>
void f(const int *xPtr); // prototype
int main(void)
{
    int x = 5;
    int y; // define y
    
    const int * const ptr = &x;
    *ptr = 7;
    ptr = &y;
    f(&y); // f attempts illegal modification
}

// xPtr cannot be used to modify the
// value of the variable to which it points
void f(const int *xPtr)
{
    *xPtr = 100; // error: cannot modify a const object
}

