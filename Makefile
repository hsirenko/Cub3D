# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 16:17:53 by hsirenko          #+#    #+#              #
#    Updated: 2024/09/30 18:14:01 by kseniakarem      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Source files
SRCS = $(wildcard *.c)
#error_checker.c stack_utils.c init_stack_a.c main.c  init_push_swap.c sort_stacks.c \
#rev_rotate.c push.c swap.c rotate.c \
#main.c \

OBJS	:= $(SRCS:%.c=%.o)
NAME = cub3D   #name of my target executable

#Compiler
CC = gcc
RM = rm -f

#Compiler and linker flags
CFLAGS = -g -Wall -Wextra -Werror
LDLIBS = minilibx #-lmlx_Linux #libraries to link
MINILIBX = libmlx.a
LDFLAGS = -I$(LDLIBS) -lXext -lX11 -lm -lz #-Lminilibx-linux   #linker flags, which specify which directories to search for libraries
#-l flag will automatically append the lib prefix and the .a extension.

#Directories for header files
INC_DIRS =  -I/usr/include -Iminilibx #-Iminilibx-linux #specifies the directories to search for header files using the -I flag. It includes the minilibx-linux directory for finding headers.

#Targets
all:	$(NAME) #This is the default target that gets built when you run make with no arguments. It depends on the $(NAME) target, which is my final executable.

${NAME}:	${OBJS}  #This section defines how to build my target ($(NAME)). It depends on $(OBJS)
			@make -C minilibx
			$(CC) $(CFLAGS) $(SRCS) $(MINLIBX) -o $(NAME) -L$(LDLIBS) -lmlx $(LDFLAGS)
# $(CC) $(CFLAGS) $(INC_DIRS) $(LDFLAGS) $^ $(LDLIBS) -o $@ #The final line compiles and links the object files ($^) into the target executable ($@).
                                                                      # It includes compiler flags ($(CFLAGS)), library directories ($(LDFLAGS)), and libraries to link ($(LDLIBS)).

minilibx-linux:              #These rules indicate how to build the mlx_Linux library.
			make -C minilibx-linux

%.o: %.c                                          #This is a generic rule for compiling source files (%.c) into object files (%.o).
		$(CC) $(CFLAGS) $(INC_DIRS) -O3 -c $< -o $@  
#It uses the compiler ($(CC)), compiler flags ($(CFLAGS)), include directories ($(INC_DIRS)), and input and output filenames ($< and $@, respectively).

clean:                              #The clean target removes object files ($(OBJS)) using the $(RM) command
			make clean -C minilibx

			${RM} ${OBJS}

fclean: clean                       #The fclean target depends on clean and additionally removes the final executable ($(NAME)) and cleans the minilibx-linux directory.
			${RM} $(NAME)
			${RM} $(MINILIBX)

re: 		fclean all              #The re (rebuild) target first runs make fclean to clean everything, and then it runs make all to rebuild the project from scratch.

test: $(NAME)
	./$(NAME) ./map/subject_map.cub

.PHONY:		all clean fclean re

#These lines mark the targets all, clean, fclean, and re as phony targets, which tells make not to treat them as files but as actions to perform.
#This is important to ensure that these targets are always executed when invoked, even if there are no changes to the source files.