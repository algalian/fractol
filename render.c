/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algalian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:46:08 by algalian          #+#    #+#             */
/*   Updated: 2023/11/02 21:46:10 by algalian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

int	render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->c.b = data->rank_h / 2 * data->m.scale + data->m.b;
	while (y < data->h)
	{
		x = 0;
		data->c.a = -data->rank_w / 2 * data->m.scale + data->m.a;
		while (x < data->w)
		{
			fractal_set(data, x, y);
			x++;
			data->c.a += (data->rank_w / data->w) * data->m.scale;
		}
		y++;
		data->c.b -= (data->rank_h / data->h) * data->m.scale;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.mlx_img, 0, 0);
	return (0);
}
