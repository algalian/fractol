#include"fractol.h"




vector  zoom_in(vector v)
{
    printf("in parsed\n");
    return(v);
}

vector  zoom_out(vector v)
{
    printf("out parsed\n");
    return(v);
}
vector  parse_trasl(vector v)
{
    if(v.a > 0)
        v = right(v);
    if(v.a < 0)
        v = left(v);
    if(v.b < 0)
        v = up(v);
    if(v.b > 0)
        v = down(v);
    return(v);
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
        v = parse_trasl(v);
    if(v.z > 0)
        v = zoom_in(v);
    if(v.z < 0)
        v = zoom_out(v);
    return(v);
}


/*int main()
{
    vector v;
    
    v.a = 1;
    v.b = -1;
    v.z = 1;
    v.prev = (char **)malloc(2 * sizeof(char *));
    v.next = (char **)malloc(2 * sizeof(char *));
    v.prev[0] = "AAAA";
    v.prev[1] = "BBBB";
    v.next[0] = "CCCC";
    v.next[1] = "DDDD";
    parse_move(v);
    return(0);
}*/
