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
    double   rank;
    t_img  img;
}	t_data;



int fractal_set(double a, double b)
{
    double  x;
    double  y;
    double  m;
    int     p;

    x = a;
    y = b;
    m = 0;
    p = 0;
    while(fabs(m) <= 2 && p <= 1000)
    {
        a = ((a*a) - (b*b)) + x;
        b = (2*a*b) + y;
        m = sqrt(a*a + b*b);
        p++;
    }
    if(p < 1000)
        return(0);
    return(1);
}


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
    double a;
    double b;

    y = 0;
    b = data->rank/2;
    while(y <= data->h && b >= -2)
    {
        x = 0;
        a = -data->rank/2;
        while(x <= data->w && a <= 2)
        {
            if(fractal_set(a,b) == 0)
                img_pix_put(&data->img,  x, y, 0x0000FF);
            x++;
            a += (data->rank/data->h);
        }
        y++;
        b -= (data->rank/data->w);
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