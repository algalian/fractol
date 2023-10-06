# include"fractol.h"



char **move(int a, int b, char **s, cmplx trasl)
{
    char **move;
    int i;
    int j;

    i = size_y(s);
    move = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while(move[i])
    {
        move[i] = malloc(sizeof(char) * (ft_strlen(move[i])+1));
        i++;
    }
    i = 0;
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

int main()
{
    return(0);
}