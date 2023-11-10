/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algalian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:53:24 by algalian          #+#    #+#             */
/*   Updated: 2023/11/10 14:54:09 by algalian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fractol.h"

void	you_are_here(t_data *data)
{
	ft_printf("center a:%s b:%s zoom: %s",
		ft_ftoa(data->m.a), ft_ftoa(data->m.b), ft_ftoa(data->m.scale));
	if (data->user.choice != 'm')
		ft_printf(" (julia set: %s %s)",
			ft_ftoa(data->user.c.a), ft_ftoa(data->user.c.b));
	ft_printf("\n");
}

int	ft_close(void)
{
	ft_printf("closing\n");
	exit(1);
	return (1);
}

void	palette(int keycode, t_data *data)
{
	if (keycode == 36)
	{
		if (data->color < 3)
			data->color++;
		else if (data->color >= 3)
			data->color = 0;
	}
}
