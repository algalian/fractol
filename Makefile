

NAME		= fractol


SRCS		= render.c

OBJS		= $(SRCS:%.c=%.o)


LIBFT		= libft/libft.a
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -Imlx -I include -I libft -g3 -O2 -DSTRINGPUTX11
MINI		= -L./mlx -lmlx -framework OpenGL -framework AppKit 


${NAME}: ${OBJS}
	@make -sC libft
	@$(CC) $(OBJS) $(LIBFT) $(MINI) -o $(NAME)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME) 

clean:
	@make clean -sC libft
	@make clean -sC mlx
	@rm -rf $(OBJS)

fclean: clean
	@make fclean -sC libft
	@rm -f $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re re_bonus bonus