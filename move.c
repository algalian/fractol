#include"fractol.h"

char **move(vector v)
{
    int i;
    int j;

    v.a += v.a;
    v.b += v.b;
    i = 0;
    while(i <= v.a)
    {
        j = 0;
        while(j <= v.b)
        {
            if(set(v.prev[i][j]) == 1)
                v.next[i][j] = '1';
            if(set(v.prev[i][j]) == 0)
                v.next[i][j] = '0';
            j++; 
        }
        i++;        
    }
    return(v.next);
}

char **zoom(vector v)
{
    
}
vector  parse_move(vector  v)
{
    int     i;

    v.a = ft_strlen(v.prev[0]);
    v.b = size_y(v.prev);
    v.next = malloc(sizeof(char *) * (v.b + 1));
    v.next[v.b + 1] = NULL;
    i = 0;
    while(v.next[i])
    {
        v.next[i] = malloc(sizeof(char) * (v.a + 1));
        v.next[i][v.a+1] = '\0';
        i++;
    }
    if(!(abs(v.a) == 0 && abs(v.b) == 0))
        v.next = move(v);
    if(abs(v.z) > 0)
        v.next = zoom(v);
    return(v);
}



int main()
{
    return(0);
}
