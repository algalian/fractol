/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algalian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:06:38 by algalian          #+#    #+#             */
/*   Updated: 2023/11/02 20:06:41 by algalian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

int	ft_error(int errorid)
{
	if (errorid == 1)
	{
		ft_printf("Wrong number of arguments. ");
		ft_printf("Please, type either 'mandelbrot'");
		ft_printf("or 'julia' along a complex value\n");
	}
	if (errorid == 2)
	{
		ft_printf("Wrong fractal set. ");
		ft_printf("Please, type either 'mandelbrot'");
		ft_printf("or 'julia' along a complex value\n");
	}
	if (errorid == 3)
		ft_printf("Please specify numeric values for Julia set\n");
	return (1);
}

static int	parse_prompt(t_data *data, int argc, char **argv)
{
	if (argc != 4 && argc != 2)
		return (ft_error(1));
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "mandelbrot", ft_strlen(argv[1])) != 0
			|| ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot")))
			return (ft_error(2));
		return (0);
	}
	if (ft_strncmp(argv[1], "julia", ft_strlen(argv[1])) != 0
		|| ft_strncmp(argv[1], "julia", ft_strlen("julia")))
		return (ft_error(2));
	data->user.c.a = ft_atof(argv[2]);
	data->user.c.b = ft_atof(argv[3]);
	return (0);
}

static int	*palette_init(void)
{
	int		*arr;

	arr = malloc (sizeof(int) * 4);
	arr[0] = WHITE;
	arr[1] = RED;
	arr[2] = GREEN;
	arr[3] = BLUE;
	return (arr);
}

static void	fractol_init(t_data *data, char **argv)
{
	data->w = WIDTH;
	data->h = HEIGHT;
	data->rank_h = 4;
	data->rank_w = 4;
	data->m.scale = 1;
	data->m.a = 0;
	data->m.b = 0;
	data->max_iter = 20;
	data->c.a = data->rank_h / 2;
	data->c.b = data->rank_w / 2;
	data->color = 0;
	data->palette = palette_init();
	if (ft_strncmp(argv[1], "mandelbrot", ft_strlen("mandelbrot")) == 0)
		data->user.choice = 'm';
	if (ft_strncmp(argv[1], "julia", ft_strlen("julia")) == 0)
		data->user.choice = 'j';
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_prompt(&data, argc, argv) == 1)
		return (1);
	fractol_init (&data, argv);
	data.mlx = mlx_init ();
	data.mlx_win = mlx_new_window(data.mlx, data.w, data.h, argv[1]);
	data.img.mlx_img = mlx_new_image(data.mlx, data.w, data.h);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_hook(data.mlx_win, 2, 0, &key_event, &data);
	mlx_hook(data.mlx_win, 17, 0, &ft_close, &data);
	mlx_mouse_hook(data.mlx_win, mouse_hook, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);
	return (0);
}
