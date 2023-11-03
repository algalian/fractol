#include"fractol.h"

void    you_are_here(t_data *data)
{
    ft_printf("center a:%s b:%s zoom: %s", ft_ftoa(data->m.a), ft_ftoa(data->m.b),ft_ftoa(data->m.scale));
    if(data->user.choice != 'm')
        ft_printf(" (julia set: %s %s)",ft_ftoa(data->user.c.a),ft_ftoa(data->user.c.b));  
    ft_printf("\n");
}

int ft_close()
{
	ft_printf("closing\n");
	exit(1);
	return(1);
}


