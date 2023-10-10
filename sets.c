#include<math.h>
#include<stdio.h>



int fractal_set(float a, float b)
{
    float   x;
    float   y;
    float   m;
    int     p;

    x = a;
    y = b;
    m = sqrt(x*x + y*y);
    p = 0;
    while(m <= 2 && p <= 300)
    {
        a = a*a - b*b;
        b = 2*a*b;
        a += x;
        b += y;
        m = sqrt(a*a + b*b);
        printf("%f\n",m);
        p++;
    }
    if(p < 300)
        return(0);
    return(1);
}



int main()
{
    float a;
    float b;

    a = 1;
    b = 0;
    printf("%i\n",fractal_set(a,b));
    return(0);
}