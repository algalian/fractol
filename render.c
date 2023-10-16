#include<mlx.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
}	t_img;


typedef struct s_data
{
    void	*mlx;
    void	*mlx_win;
    int     w;
    int     h;
    double  rank;
    t_img  img;
}	t_data;

typedef struct complex
{
    float a;
    float b;
} complex;

complex   ft_csum(complex x, complex y)
{
    complex z;
    z.a = x.a + y.a;
    z.b = x.b + y.b;
    return(z);
}
complex ft_csqrt(complex x)
{
    complex z;

    z.a = x.a * x.a - x.b * x.b;
    z.b = 2 * x.a * x.b;
    return(z);    
}


int fractal_set(complex c)
{
    int     p;
    complex z;

    z.a = 0;
    z.b = 0;
    p = 0;
    while(p <= 1000)
    {
        z = ft_csqrt(z);
        z = ft_csum(z,c);
        if(hypot(z.a, z.b)>2)
            return(0);
        p++;

    }
    return(1);
}

/*int is_in_mandelbrot(float complex c)
{
    float complex z;
    int i;
    
    i = 0;
    z = 0;
    while ( i < 1000) 
    {
        z = z * z + c;
        if (cabsf(z) > 2) 
            return(0);
        i++;
    }
    return (1); 
}*/

int close(t_data *data)
{   

    /*printf("%p\n", data->mlx);
    printf("%p\n", data->mlx_win);*/
    mlx_clear_window(data->mlx,data->mlx_win);
    //printf("%d\n",mlx_clear_window(data->mlx,data->mlx_win));
    //mlx_destroy_window(data->mlx, data->mlx_win);
    printf("ventana destruida\n");
    return(0);

}
void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;
    
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}

int render(t_data *data)
{
    int x;
    int y;
    complex c;


    y = 0;
    c.b = data->rank/2;
    while(y <= data->h && c.b >= -2)
    {
        x = 0;
        c.a = -data->rank/2;
        while(x <= data->w && c.a <= 2)
        {
            if(fractal_set(c) == 0)
                img_pix_put(&data->img,  x, y, 0x0000FF);
            x++;
            c.a += (data->rank/data->h);
        }
        y++;
        c.b -= (data->rank/data->w);
    }
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
    return(0);
}

int	main()
{
    t_data  data;

	data.mlx = mlx_init();
    if(!data.mlx)
    {
        free(data.mlx);
        return(1);
    }
    data.w = 800;
    data.h = 800;
    data.rank = 4;
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, "Una ventana");
    if(!data.mlx_win)
    {
        free(data.mlx_win);
        return(1);
    }
    data.img.mlx_img = mlx_new_image(data.mlx, data.w, data.h);
    data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
    mlx_loop_hook(data.mlx, &render, &data);
    mlx_key_hook(data.mlx_win, &close, &data);
    mlx_loop(data.mlx);
    return(0);
}