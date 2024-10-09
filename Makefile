DEFAULT_GOAL := all

NAME = cub3D
CFLAGS = -Wall -Werror -Wextra -g
SRC = main.c parse.c raycasting.c utils.c render.c stack.c
OBJ = $(SRC:.c=.o)
HEADER = $(NAME).h
INCLUDES += -Ilibft -Iminilibx

all: $(NAME)

libft/libft.a:
	make -C libft

minilibx/libmlx.a:
	make -C minilibx

%.o: %.c $(HEADER)
	cc -o $@ $(CFLAGS) $(INCLUDES) -c  $<

$(NAME): $(OBJ) $(HEADER) libft/libft.a minilibx/libmlx.a
	cc $(OBJ) libft/libft.a minilibx/libmlx.a -L /usr/X11/lib -lXext -lX11 -lm -lz  -o $(NAME)

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