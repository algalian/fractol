#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# define WIDTH  800
# define HEIGHT 800

typedef struct complex
{
    float     a;
    float     b;
}	cmplx;

typedef struct vector
{
    char   **next;
    char   **prev;
    int    a;
    int    b;
    int    z;
    cmplx  c;
} vector;
int size_y(char **s);


#endif