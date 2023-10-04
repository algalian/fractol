#include<mlx.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>


int	main(void)
{
	void	*mlx;
    void	*mlx_win;
    int     x;
    int     y;
    int     w;
    int     h;
    float   r;

	mlx = mlx_init();
    w = 500;
    h = 500;
	mlx_win = mlx_new_window(mlx, w, h, "The abyss");
    x = 0;
    y = 500;
    r = 250.000000;
    while(y >= 0)
    {
        x = 0;
        while(x <= 500)
        {
            if(sqrt (pow (abs (x - 250),2) + pow (abs (y - 250),2)) <= r)
            {
                mlx_pixel_put(mlx,mlx_win,x,y,0xFF0000);
            }
            x++;
        }
        y--;
    }
    mlx_loop(mlx);
}