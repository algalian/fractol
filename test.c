#include<mlx.h>
#include<math.h>


int	main(void)
{
	void	*mlx;
    void	*mlx_win;
    int     x;
    int     y;
    double  d;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "The abyss");

    y = 500;
    d = 500;
    while(y >= 250)
    {   
        x = 250;
        while((double)y <= d )
        {
            mlx_pixel_put(mlx,mlx_win,x,y,0xFF0000);
            x++;
            d = sqrt(pow(250,2) + 250 + 250 - pow(x,2));     
        }
        y--;
    }
    mlx_loop(mlx);
}