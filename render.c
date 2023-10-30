
#include"mlx/mlx.h"
#include<mlx.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
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
#include<math.h>

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED   0xFF0000
# define GREEN 0x00FF00
# define BLUE  0x0000FF

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
} move;

typedef struct complex
{
	double a;
	double b;
} complex;

typedef struct prompt
{
	char 	*choice;
	complex c;
} prompt;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	int     w;
	int     h;
	double	rank_w;
	double	rank_h;
	int		max_iter;
	int		color;
	t_img  	img;
	move	m;
	complex c;
	prompt 	user;
}	t_data;

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
	{
		return (1);
	}
	return (0);
}
static int	ft_blanks(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
	{
		return (1);
	}
	return (0);
}

static int	clean_string(const char *str, unsigned int i)
{
	if (ft_isdigit(str[i]) == 1)
		return (i);
	if (ft_blanks(str[i]) != 1 && (str[i] != '+' && str[i] != '-'))
		if (ft_isdigit(str[i]) != 1)
			return (-1);
	if (str[i] == '+' || str[i] == '-')
	{
		if (ft_isdigit(str[i + 1]) != 1)
			return (-1);
		return (i + 1);
	}
	if (ft_blanks(str[i]) == 1)
	{
		while (ft_blanks(str[i]) == 1)
			i++;
		return (clean_string(str, i));
	}
	return (-1);
}

static int	sign(const char *str, unsigned int i)
{
	if (i == 0)
		return (1);
	if (str[i - 1] == '-')
	{
		return (-1);
	}
	return (1);
}

double	ft_atof(const char *str)
{
	int		i;
	double	num;
	double	nextf;
	int		pos;
	
	i = clean_string(str, 0);
	if(i < 0)
	{
		printf("Please specify a numeric value");
		exit(1);
	}
	num = str[i] - '0';
	i++;
	while (ft_isdigit(str[i]) == 1)
	{
		nextf = str[i++] - '0';
		num = num * 10 + nextf;
	}
	i++;
	pos = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		nextf = str[i++] - '0';
		num = num * 10 + nextf;
		pos++;
	}
	return (num * sign(str, clean_string(str, 0)) / pow(10, pos));
}
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

int	close(t_data *data)
{
	printf("closing\n");
	mlx_destroy_window(data->mlx,data->mlx_win);
	exit(1);
	return(0);
}

int key_event(int keycode, t_data *data)
{

	if(keycode == 53)
		close(data);
	mlx_destroy_image(data->mlx,data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx,data->w,data->h);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	if(keycode == 0 || keycode == 123)
		data->m.a -= 0.15 * (2 * data->m.scale/0.95);
	if(keycode == 2 || keycode == 124)
		data->m.a += 0.15 * (2 * data->m.scale/0.95);
	if(keycode == 13 || keycode == 126)
		data->m.b += 0.15 * (2 * data->m.scale/0.95);
	if(keycode == 1 || keycode == 125)
		data->m.b -= 0.15 * (2 * data->m.scale/0.95);
	if((keycode == 69 || keycode == 14) && data->m.scale <= 1)
	{
		data->max_iter += 10;
		printf("iterations: %d\n", data->max_iter);
	}
	if((keycode == 78 || keycode == 15) && data->max_iter - 10 > 0)
	{
		data->max_iter -= 10;
		printf("iterations: %d\n", data->max_iter);
	}
	if(keycode == 84)
		data->user.c.b = data->user.c.b - 0.01;
	if(keycode == 91)
		data->user.c.b =  data->user.c.b + 0.01;
	if(keycode == 86)
		data->user.c.a = data->user.c.a - 0.01;
	if(keycode == 88)
		data->user.c.a = data->user.c.a + 0.01;
	return(0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	x = 0;
	y = 0;
	mlx_destroy_image(data->mlx,data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx,data->w,data->h);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	if(button == 4)
		data->m.scale *= 0.95;
	if(button == 5)
		data->m.scale *= 1.1;
	return(0); 
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void fractal_set(t_data *data, int x, int y)
{
	int		p;
	complex z;
	complex c; 
	int color;

	if(strcmp(data->user.choice,"mandelbrot") == 0)
	{
		c.a = data->c.a;
		c.b = data->c.b;
		z.a = 0;
		z.b = 0;
	}
	else if(strcmp(data->user.choice,"julia") == 0)
	{
		c.a = data->user.c.a;
		c.b = data->user.c.b;
		z.a = data->c.a;
		z.b = data->c.b;
	}
	p = 0;
	while(p < data->max_iter)
	{
		z = ft_csqrt(z);
		z = ft_csum(z,c);
		if(z.a*z.a + z.b*z.b > 4)
		{	
			color = p*((RED - GREEN)/data->max_iter);
			img_pix_put(&data->img,x,y,color);
			return;
		}
		p++;
	}
	img_pix_put(&data->img,x,y,BLACK);
	return;
}

int	render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->c.b = data->rank_h/2 * data->m.scale + data->m.b;
	while(y < data->h)
	{
		x = 0;
		data->c.a = -data->rank_w/2 * data->m.scale + data->m.a;
		while(x < data->w)
		{
			fractal_set(data,x,y);
			x++;
			data->c.a += (data->rank_w/data->w) * data->m.scale;
		}
		y++; 
		data->c.b -= (data->rank_h/data->h) * data->m.scale;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
	return(0);
}

void	parse_prompt(t_data *data, int argc, char **argv)
{
	if(argc != 4 && argc != 2)
	{
		printf("Invalid arg number");
		exit(1);
	}
	if(argc == 2)
	{
		if(strcmp(argv[1], "mandelbrot") != 0)
		{
			printf("Invalid fractal set");
			exit(1);
		}
		return;
	}
	if(strcmp(argv[1], "julia") != 0)
	{
		printf("Invalid fractal set");
		exit(1);
	}
	data->user.c.a = ft_atof(argv[2]);
	data->user.c.b = ft_atof(argv[3]);
}
void	fractol_init(t_data *data, char **argv)
{
	data->w = 800;
	data->h = 800;
	data->rank_h = 4;
	data->rank_w = 4;
	data->m.scale = 1;
	data->m.a = 0;
	data->m.b = 0;
	data->max_iter = 20;
	data->c.a = -2;
	data->c.b = 2;
	data->user.choice = calloc(11, sizeof(char));
	strcpy(data->user.choice, argv[1]);
}
int	main(int argc, char **argv)
{
	t_data  data;

	parse_prompt(&data, argc, argv);
	fractol_init(&data, argv);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, "Una ventana");
	data.img.mlx_img = mlx_new_image(data.mlx, data.w, data.h);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_hook(data.mlx_win,2, 0, &key_event, &data);
	mlx_hook(data.mlx_win,17, 0,&close,&data);
	mlx_mouse_hook(data.mlx_win,mouse_hook, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	return(0);
}