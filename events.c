/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algalian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:32:33 by algalian          #+#    #+#             */
/*   Updated: 2023/11/02 21:32:34 by algalian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

static void	move(int keycode, t_data *data)
{
	if (keycode == A || keycode == LEFT)
		data->m.a -= 0.15 * (2 * data->m.scale / 0.95);
	if (keycode == D || keycode == RIGHT)
		data->m.a += 0.15 * (2 * data->m.scale / 0.95);
	if (keycode == W || keycode == UP)
		data->m.b += 0.15 * (2 * data->m.scale / 0.95);
	if (keycode == S || keycode == DOWN)
		data->m.b -= 0.15 * (2 * data->m.scale / 0.95);
}

static void	enhance(int keycode, t_data *data)
{
	if ((keycode == E || keycode == PLUS) && data->m.scale <= 1)
	{
		data->max_iter += ENHANCE;
		ft_printf("iterations: %d\n", data->max_iter);
	}
	if ((keycode == MINUS || keycode == R) && data->max_iter - 10 > 0)
	{
		data->max_iter -= ENHANCE;
		ft_printf("iterations: %d\n", data->max_iter);
	}
}

static void	julia(int keycode, t_data *data)
{
	if (keycode == C_DOWN)
		data->user.c.b = data->user.c.b - 0.05;
	if (keycode == C_UP)
		data->user.c.b = data->user.c.b + 0.05;
	if (keycode == C_LEFT)
		data->user.c.a = data->user.c.a - 0.05;
	if (keycode == C_RIGHT)
		data->user.c.a = data->user.c.a + 0.05;
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_close();
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx, data->w, data->h);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	move(keycode, data);
	enhance(keycode, data);
	julia(keycode, data);
	palette(keycode, data);
	if (keycode == 49)
		you_are_here(data);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	x = 0;
	y = 0;
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx, data->w, data->h);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (button == WHEEL_UP)
		data->m.scale *= 0.95;
	if (button == WHEEL_DOWN)
		data->m.scale *= 1.1;
	return (0);
}
