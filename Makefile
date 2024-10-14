DEFAULT_GOAL := all

NAME = cub3D
CFLAGS = -Wall -Werror -Wextra -g
SRC = main.c parse.c raycasting.c utils.c render.c stack.c exec.c player_movements.c raycasting_inters.c raycasting_utils.c vector_utils.c
OBJ = $(SRC:.c=.o)
HEADER = $(NAME).h
INCLUDES += -Ilibft -Iminilibx
CC = clang

all: $(NAME)

libft/libft.a:
	make -C libft

minilibx/libmlx.a:
	make -C minilibx

%.o: %.c $(HEADER)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c  $<

$(NAME): $(OBJ) $(HEADER) libft/libft.a minilibx/libmlx.a
	$(CC) $(OBJ) libft/libft.a minilibx/libmlx.a -L /usr/X11/lib -lXext -lX11 -lm -lz  -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C minilibx clean
	make -C libft fclean

test: all
	./$(NAME) map/subject_map.cub

re: fclean all