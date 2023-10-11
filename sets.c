#include<complex.h>
#include<math.h>
#include<stdio.h>

int fractal_set(double a, double b)
{
    double  x;
    double  y;
    double  m;
    int     p;
    FILE    *file;

    fopen("somerule.txt","w");
    x = a;
    y = b;
    m = 0;
    p = 0;
    while(fabs(m) <= 2 && p <= 1000)
    {
        a = ((a*a) - (b*b)) + x;
        b = (2*a*b) + y;
        m = sqrt(a*a + b*b);
        fprintf(file,"some rule a:%f b: %f m: %f\n",a,b,m);
        p++;
    }
    fclose(file);
    if(p < 1000)
        return(0);
    return(1);
}

int is_in_mandelbrot(double complex c)
{
    double complex z;
    FILE    *file;
    fopen("mandelbrot.txt","w");
    
    z = 0;
    for (int i = 0; i < 1000; i++) 
    {
        z = z * z + c;
        fprintf(file,"Mandelbrot a:%f b:%f m:%f\n", creal(z),cimag(z),cabs(z));
        if (cabs(z) > 2) 
        {
            fclose(file);
            return 0;  
        }
    }
    fclose(file);
    return 1; 
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





