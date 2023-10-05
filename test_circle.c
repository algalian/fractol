#include<mlx.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>


typedef struct s_data
{
    void	*mlx;
    void	*mlx_win;
    int     w;
    int     h;
}	t_data;

int close(t_data *data)
{   
    /*printf("%p\n", data->mlx);
    printf("%p\n", data->mlx_win);*/
    mlx_destroy_window(data->mlx, data->mlx_win);
    printf("ventana destruida\n");
    return(0);
}
int render(t_data *data)
{
    int x;
    int y;
    float r;

    data->h = 500;
    data->w = 500;
    x = 0;
    y = data->h;
    r = 250;
    while(y >= 0)
    {
        x = 0;
        while(x <= data->w)
        {
            if(sqrt (pow (abs (x - (data->w/2)),2) + pow (abs (y - (data->h/2)),2)) <= r)
            {
                mlx_pixel_put(data->mlx, data->mlx_win, x, y, 0xFF0000);
            }
            x++;
        }
        y--;
    }
    return(0);
}

int	main(void)
{
    t_data  data;

	data.mlx = mlx_init();
    if(!data.mlx)
    {
        free(data.mlx);
        return(1);
    }
    data.w = 500;
    data.h = 500;
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, "Una ventana");
    if(!data.mlx_win)
    {
        free(data.mlx_win);
        return(1);
    }
    data.w = 500;
    data.h = 500;
    mlx_loop_hook(data.mlx, &render, &data);
    mlx_key_hook(data.mlx_win, &close, &data);
    mlx_loop(data.mlx);
    return(0);
}