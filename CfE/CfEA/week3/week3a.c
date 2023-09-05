#include <stdio.h>
#include <math.h> /* has  sin(), abs(), and fabs() */
int main(void)
{
    double interval;
    int i;
    for (i = 0; i < 30; i++)
    {
        interval = i / 10.0;
        double abs_sin = sin(interval) > 0 ? sin(interval) : -sin(interval);
        printf("sin(% lf) = % lf \t", interval, abs_sin);
    }

    printf("\n++ +++++\n");
    return 0;
}
