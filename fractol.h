#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>

typedef struct complex
{
    float     x;
    float     y;
}	cmplx;

typedef struct vector
{
    char   **next;
    char   **prev;
    int    a;
    int    b;
    int    z;
    cmplx  t;
} vector;
int size_y(char **s);


#endif