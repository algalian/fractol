#include"fractol.h"

int size_y(char **s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return(i);
}