#include <stdio.h>
#include <math.h> /* has  sin(), abs(), and fabs() */
int main(void)
{
    double interval;
    printf("Enter the interval value: \n");
    scanf("%lf", &interval);
    double x;
    printf("x \t\t sin(x) \t cos(x) \n");
    printf("-- \t\t ------ \t ------ \n");
    for (x = 0; x <= 1; x+=interval)
    {
        printf("%lf \t %lf \t %lf\n", x, sin(x), cos(x));
    }

    printf("-- \t\t ------ \t ------ \n");
    return 0;
}