/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algalian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:51:33 by algalian          #+#    #+#             */
/*   Updated: 2023/11/02 20:51:42 by algalian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

t_complex	ft_csum(t_complex x, t_complex y)
{
	t_complex	z;

	z.a = x.a + y.a;
	z.b = x.b + y.b;
	return (z);
}

t_complex	ft_csqrt(t_complex x)
{
	t_complex	z;

	z.a = x.a * x.a - x.b * x.b;
	z.b = 2 * x.a * x.b;
	return (z);
}

t_pair	swap_to_julia(t_data *data)
{
	t_pair	q;

	if (data->user.choice == 'm')
	{
		q.c.a = data->c.a;
		q.c.b = data->c.b;
		q.z.a = 0;
		q.z.b = 0;
		return (q);
	}
	q.c.a = data->user.c.a;
	q.c.b = data->user.c.b;
	q.z.a = data->c.a;
	q.z.b = data->c.b;
	return (q);
}

void	fractal_set(t_data *data, int x, int y)
{
	int			p;
	t_pair		q;
	int			color;

	q = swap_to_julia(data);
	p = 0;
	while (p < data->max_iter)
	{
		q.z = ft_csqrt(q.z);
		q.z = ft_csum(q.z, q.c);
		if (q.z.a * q.z.a + q.z.b * q.z.b > 4)
		{	
			color = p * (WHITE / data->max_iter);
			img_pix_put(&data->img, x, y, color);
			return ;
		}
		p++;
	}
	img_pix_put (&data->img, x, y, BLACK);
	return ;
}
