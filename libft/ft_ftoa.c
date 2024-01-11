/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algalian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:14:21 by algalian          #+#    #+#             */
/*   Updated: 2023/11/03 19:14:27 by algalian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdio.h>
#include<math.h>

char	*ft_ftoa(double n)
{
	char	*s;
	char	*p;
	int		i;

	s = ft_itoa(truncf(n));
	p = malloc(sizeof(char) * 7);
	i = 1;
	n = fabs(n);
	n -= truncf(n);
	p[0] = '.';
	while (i < 7)
	{
		n *= 10;
		p[i] = (int) truncf(n) + '0';
		n -= truncf(n);
		i++;
	}
	p[7] = '\0';
	return (ft_strjoin(s, p));
}
