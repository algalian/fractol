#include"fractol.h"

vector trasl(vector v)
{
    int i;
    int j;

    i = 0;
    while(v.next[0][i])
    {
        if(set(v.next[0][i]) == 1)
            v.next[0][i] = '1';
        if(set(v.next[0][i]) == 0)
            v.next[0][i] = '0';
        i++;
    }
    j = 1;
    while(v.prev[j - 1][i])
    {
        i = 0;
        while(v.prev[j][i])
        {
            v.next[j][i] = v.prev[j][i];
            i++;
        }
        j++;
    }
    ft_bzero(v.prev[j], WIDTH);
    return(v);
}

vector zoom(vector v)
{


    
}

vector  parse_move(vector  v)
{
    int     i;

    v.next = malloc(sizeof(char *) * (HEIGHT + 1));
    v.next[HEIGHT + 1] = NULL;
    i = 0;
    while(v.next[i])
    {
        v.next[i] = malloc(sizeof(char) * (WIDTH + 1));
        v.next[i][WIDTH + 1] = '\0';
        i++;
    }
    if(!(abs(v.a) == 0 && abs(v.b) == 0))
        v = trasl(v);
    if(abs(v.z) > 0)
        v = zoom(v);
    return(v);
}



int main()
{
    return(0);
}
