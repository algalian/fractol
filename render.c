#include<mlx.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"X11/keysym.h"
#include"X11/keysymdef.h"
#include"X11/cursorfont.h"
#include"X11/X.h"
#include"X11/Xatom.h"
#include"X11/xbytes.h"
#include"X11/Xfuncproto.h"
#include"X11/Xlib.h"
#include"X11/Xutil.h"
#include"X11/tkIntXlibDecls.h"



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
    double	a;
    double	b;
    double	scale;
	int		brake;
} move;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	int     w;
	int     h;
	double	rank_w;
	double	rank_h;
	t_img  	img;
	move	m;
}	t_data;

typedef struct complex
{
	double a;
	double b;
} complex;

int render(t_data *data);

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

	while(p <= 100)
	{
		z = ft_csqrt(z);
		z = ft_csum(z,c);
		if(hypot(z.a, z.b)>2)
			return(false);
		p++;
	}
	return(true);
}

int	close(t_data data)
{
	printf("closing\n");
	mlx_destroy_window(data.mlx,data.mlx_win);
	exit(1);
	return(0);
}
int ft_brake(t_data *data)
{
	if (data->m.scale - 0.05 * pow(10, -data->m.brake) <= 0)
		data->m.brake += 1;
	return(data->m.brake);
}

int key_event(int keycode, t_data *data)
{
	if(keycode == 53)
		close(*data);
	data->img.mlx_img = mlx_new_image(data->mlx,data->w,data->h);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	if(keycode == 0 || keycode == 123)
		data->m.a = data->m.a - 0.05 * data->m.scale;
	if(keycode == 2 || keycode == 124)
		data->m.a =data->m.a + 0.05 *data ->m.scale;
	if(keycode == 13 || keycode == 126)
		data->m.b = data->m.b + 0.05 *data->m.scale;
	if(keycode == 1 || keycode == 125)
		data->m.b = data->m.b - 0.05 *data->m.scale;
	if(keycode == 69 && data->m.scale < data->w/data->rank_h*pow(10,14))
		data->m.scale = data->m.scale - 0.05 *  pow(10, -ft_brake(data));
	if(keycode == 78)
		data->m.scale = data->m.scale + 0.1 * pow(10, -ft_brake(data));
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
	c.b = data->rank_h/2* data->m.scale + data->m.b;
	while(y < data->h)
	{
		x = 0;
		c.a = -data->rank_w/2 * data->m.scale + data->m.a;
		while(x < data->w)
		{
			if(fractal_set(c) == 1 && (c.b > -2 && c.a < 2))
				img_pix_put(&data->img,  x, y, 0x0000FF);
			if(x == data->w/2 && y == data->h/2)
				img_pix_put(&data->img,x,y,0xFF0000);
			x++;
			c.a += (data->rank_w/data->w)*data->m.scale;
		}
		y++; 
		c.b -= (data->rank_h/data->h)*data->m.scale;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
	printf("%5.14f\n",data->m.scale);
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
	data.m.scale = 1;
	data.m.a = -0.79939982247476;
	data.m.b = -0.16519870491700;
	data.m.brake = 0;
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, "Una ventana");
	data.img.mlx_img = mlx_new_image(data.mlx, data.w, data.h);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_hook(data.mlx_win,2, 0, &key_event, &data);
	mlx_hook(data.mlx_win,17, 0,&close,&data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	return(0);
}