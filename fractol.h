/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algalian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:14:15 by algalian          #+#    #+#             */
/*   Updated: 2023/11/02 20:14:35 by algalian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include<mlx.h>
# include<stdbool.h>
# include<math.h>
# include"libft.h"

# define HEIGHT				800
# define WIDTH				800
# define ESC				53
# define A					0
# define LEFT				123
# define D					2
# define RIGHT				124
# define W					13
# define UP					126
# define S					1
# define DOWN				125
# define PLUS				69
# define E					14
# define MINUS				78
# define R					15
# define C_DOWN				84
# define C_UP				91
# define C_LEFT				86
# define C_RIGHT			88
# define ENHANCE			10
# define WHEEL_UP			4
# define WHEEL_DOWN			5
# define ENTER				36
# define SPACE				49
# define BLACK				0x000000
# define WHITE				0xFFFFFF
# define RED				0xFF0000
# define GREEN				0x00FF00
# define BLUE				0x0000FF

typedef struct img
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
}	t_move;

typedef struct complex
{
	double	a;
	double	b;
}	t_complex;

typedef struct prompt
{
	char		choice;
	t_complex	c;
}	t_prompt;

typedef struct pair
{
	t_complex	z;
	t_complex	c;
}	t_pair;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	int			w;
	int			h;
	double		rank_w;
	double		rank_h;
	int			max_iter;
	int			*palette;
	int			color;
	t_img		img;
	t_move		m;
	t_complex	c;
	t_prompt	user;
}	t_data;

int		ft_close(void);
int		key_event(int keycode, t_data *data);
int		mouse_hook(int button, int x, int y, t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
int		render(t_data *data);
void	fractal_set(t_data *data, int x, int y);
int		ft_error(int errorid);
void	you_are_here(t_data *data);
void	palette(int keycode, t_data *data);

#endif