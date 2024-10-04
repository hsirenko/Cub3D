DEFAULT_GOAL := all

NAME = cub3D
CFLAGS = -Wall -Werror -Wextra -g
SRC = main.c parse.c raycasting.c utils.c
OBJ = $(SRC:.c=.o)
HEADER = $(NAME).h
INCLUDES += -Ilibft -Iminilibx

all: $(NAME)

libft/libft.a:
	make -C libft

%.o: %.c $(HEADER)
	cc -o $@ $(CFLAGS) $(INCLUDES) -c  $<

$(NAME): $(OBJ) $(HEADER) libft/libft.a
	cc $(OBJ) libft/libft.a minilibx/libmlx.a -lXext -lX11 -lm -lz  -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

test: all
	./$(NAME) map/subject_map.cub

re: fclean all