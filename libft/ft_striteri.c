/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algalian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:35:57 by algalian          #+#    #+#             */
/*   Updated: 2023/01/30 12:35:58 by algalian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*void my_func(unsigned int i, char *str)
{
 	printf("My inner function: index = %d and the string is %s\n", i, str);
}
int main()
{
 	char str[10] = "Hello.";
 	printf("The result is %s\n", str); ft_striteri(str, my_func);
 	return 0;
 }*/
