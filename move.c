#include"fractol.h"

char **move(int a, int b, char **s, cmplx trasl)
{
    char **move;
    int i;
    int j;

    a += trasl.a;
    b += trasl.b;
    while(i <= a * 2)
    {
        j = 0;
        while(j <= b * 2)
        {
            if(set(move[i][j]) == 1)
                move[i][j] = '1';
            if(set(move[i][j]) == 0)
                move[i][j] = '0';
            j++; 
        }
        i++;        
    }
    return(move);
}

char **zoom(int a, int b, char **next)
{

}

char **next(char **prev, cmplx trasl, int z)
{
    char **next;
    int     a;
    int     b;
    int     i;

    a = ft_strlen(prev[0]);
    b = size_y(prev);
    next = malloc(sizeof(char *) * (b + 1));
    next[b+1] = NULL;
    i = 0;
    while(next[i])
    {
        next[i] = malloc(sizeof(char) * (a + 1));
        next[i][a+1] = '\0';
        i++;
    }
    if(!(abs(trasl.a) == 0 && abs(trasl.b) == 0))
        next = move(a, b, prev, trasl);
    if(abs(z) > 0)
        next = zoom(a, b, next);
    return(next);
}



int main()
{
    return(0);
}
