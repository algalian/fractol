#include<mlx.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct move
{
    float	a;
    float	b;
    float	scale;
} move;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	int     w;
	int     h;
	float	rank_w;
	float	rank_h;
	t_img  	img;
	move	m;
}	t_data;

typedef struct complex
{
	double a;
	double b;
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

bool fractal_set(complex c)
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
			return(false);
		p++;

	}
	return(true);
}

void close(t_data data)
{
	mlx_destroy_window(data.mlx,data.mlx_win);

}

int key_event(t_data data)
{   
	close(data);
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
	c.b = (data->rank_h/2)  * data->m.scale + data->m.b;
	while(y <= data->h)
	{
		x = 0;
		c.a = (-data->rank_w/2) * data->m.scale + data->m.a;
		while(x <= data->w)
		{
			if(fractal_set(c) == 0  && (c.b > -2 && c.a < 2))
				img_pix_put(&data->img,  x, y, 0x0000FF);
			x++;
			c.a += (data->rank_w/data->w)*data->m.scale;
		}
		y++; 
		c.b -= (data->rank_h/data->h)*data->m.scale;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
	return(0);
}

int	main()
{
	t_data  data;

	data.mlx = mlx_init();
	data.w = 800;
	data.h = 800;
	data.rank_h = 4;
	data.rank_w = 4;
	data.m.scale = 0.0001;
	data.m.a = 0.20005;
	data.m.b = 0.55;
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, "Una ventana");
	data.img.mlx_img = mlx_new_image(data.mlx, data.w, data.h);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_key_hook(data.mlx_win, &key_event, &data);
	mlx_loop(data.mlx);
	return(0);
} 