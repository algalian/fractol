#include<complex.h>
#include<math.h>
#include<stdio.h>

int fractal_set(float a, float b)
{
    float  x;
    float  y;
    float  m;
    int     p;

    x = a;
    y = b;
    m = sqrtf(a*a + b*b);
    if(m > 2)
        return(0);
    p = 0;
    while(p <= 1000)
    {
        a = ((a*a) - (b*b)) + x;
        b = (2*a*b) + y;
        m = hypot(a,b);
        if(m > 2)
            return(0);
        p++;
    }
    return(1);
}

int is_in_mandelbrot(float complex c)
{
    float complex z;
    int i;
    
    i = 0;
    z = 0;
    while ( i < 1000) 
    {
        z = z * z + c;
        if (cabs(z) > 2) 
            return(0);
        i++;
    }
    return (1); 
}

int main()
{
    double a;
    double b;
    double complex c;
    int i;

    a = 1;
    b = -1;
    c = a + b*I;
   is_in_mandelbrot(c);
   fractal_set(a,b);

}





