#include <stdio.h>
#include <math.h>

// A program that asks the user to input a X between 0 and 1 and assumes it is in radians
// And prints the subsequent sin using the function provided in Math.h
// remember to compile with -lm option
int main(void)
{
    double angleInRadians;
    printf("Enter angle in Radians (between 0 and 1):");
    scanf("%lf", &angleInRadians);
    double result = sin(angleInRadians);
    printf("Sin(%lf) is: %lf \n\n", angleInRadians, result);
    return 0;
}
