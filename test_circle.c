#include<mlx.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>


typedef struct s_data
{
    void	*mlx;
    void	*mlx_win;
}	t_data;


int	handle_no_event(void *data)
{
    void    *dummy;

    dummy = data;
    return (0);
}
int handle_input(int keysym, t_data data)
{   
    int dummy;

    dummy = keysym;
	mlx_destroy_window(data.mlx, data.mlx_win);
    return (0);
}

int	main(void)
{
    t_data  data;
    //int     x;
    //int     y;
    int     w;
    int     h;
    //float   r;

	data.mlx = mlx_init();
    if(!data.mlx)
        return(1);
    w = 500;
    h = 500;
	data.mlx_win = mlx_new_window(data.mlx, w, h, "The abyss");
    if(!data.mlx_win)
    {
        free(data.mlx_win);
        return(1);
    }
    /*x = 0;
    y = h;
    r = 250;
    while(y >= 0)
    {
        x = 0;
        while(x <= w)
        {
            if(sqrt (pow (abs (x - (w/2)),2) + pow (abs (y - (h/2)),2)) <= r)
            {
                mlx_pixel_put(data.mlx,data.mlx_win,x,y,0xFF0000);
            }
            x++;
        }
        y--;
    }*/
    mlx_loop_hook(data.mlx, &handle_no_event, &data);
    //mlx_key_hook(data.mlx_win, &handle_input, &data);
    mlx_hook(data.mlx_win, 2, 1L<<0, &handle_input, &data);
    mlx_loop(data.mlx);
   // mlx_destroy_display(data.mlx);

}