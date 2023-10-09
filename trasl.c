#include<stdio.h>
#include<stdlib.h>
#define WIDTH 3
#define HEIGHT 3

typedef struct vector
{
    char   **next;
    char   **prev;
    int    a;
    int    b;
} vector;



int fractal_set(int j, int i) //regla inventada.  
{
    if((j + i) % 2 == 0)
        return(0);
    return(1);
}

vector up(vector v)
{
    int i;
    int j;

    i = 0;
    while(v.prev[0][i])
    {
        if(fractal_set(-1, i) == 1)
            v.next[0][i] = '1';
        if(fractal_set(-1, i) == 0)
            v.next[0][i] = '0';
        i++;
    }
    v.next[0][i] = '\0';
    j = 1;
    i = 0;

    while(j <= HEIGHT - 1)
    {
        i = 0;
        while(v.prev[j][i])
        {
            v.next[j][i] = v.prev[j-1][i];
            i++;
        }
        v.next[j][i] = '\0';
        j++;
    }
    v.next[j] = NULL;
    return(v);
}

/*int main()
{
    vector v;
    int i;

    v.a = 1;
    v.b = -1;
    v.prev = malloc(4 * sizeof(char *));
    v.next = malloc(4 * sizeof(char *));
    v.prev[0] = "010";
    v.prev[1] = "101";
    v.prev[2] = "010";
    i = 0;
    while(i < 4)
    {
        v.next[i] = malloc(sizeof(char) * 4);
        i++;
    }
    v = up(v);
    i = 0;
    while(v.next[i])
    {
        printf("%s\n", v.next[i]);
        i++;
    }
    return(0);
}*/