NAME = cub3D

SRC =   parsing/main.c\
		parsing/check_file.c\
		parsing/check_map.c\
		parsing/check_texture.c\
		parsing/utils.c\
		raycasting/main.c\
		raycasting/raycasting.c\
		raycasting/utils_window.c\
		raycasting/utils_move.c\
		raycasting/draw_texture.c\
		

CC = cc -Ilibft -Iincludes -Wall -Wextra -Werror -g3

OBJ = $(SRC:.c=.o)

LIBFT = -L libft -lft

HEADER = -I libft -I minilibx-linux/

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C minilibx-linux
	$(CC) $(OBJ) -g -L minilibx-linux/ $(LIBFT) -lmlx -lXext -lX11 -o $(NAME) -lm $(HEADERS)

.c.o:
	$(CC) $(HEADERS) -c $< -o $(<:.c=.o)

clean:
	make -C libft clean
	make clean -C minilibx-linux
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
