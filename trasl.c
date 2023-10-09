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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > i)
	{
		dst[i] = '\0';
	}	
	return (ft_strlen(src));
}

int fractal_set(int j, int i) //regla inventada.  
{
    if((j + i) % 2 == 0)
        return(0);
    return(1);
}

vector upp(vector v)
{
    int i;
    int j;

    i = 0;
    j = 1;
    while(j <= HEIGHT - 1)
    {
        ft_strlcpy(v.next[j],v.prev[j-1], WIDTH + 1);
        j++;
    }
    v.next[j] = NULL;
    return(v);

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
    i = 0;
    j = 1;
    while(j <= HEIGHT - 1)
    {
        ft_strlcpy(v.next[j],v.prev[j-1], WIDTH + 1);
        j++;
    }
    v.next[j] = NULL;
    return(v);
}

int main()
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
}