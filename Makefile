# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bedavis <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/23 11:05:54 by bedavis           #+#    #+#              #
#    Updated: 2019/12/23 11:06:58 by bedavis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

#Source files
SRC = main.c keyboard.c help.c help2.c read.c colors.c draw.c make_arrays.c \
	  mouse.c p3d.c usage.c \

#Object files
OBJ = $(addprefix $(OBJECT_DIRECTORY),$(SRC:.c=.o))

#Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

#ft library
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/
LIBFT_LINK = -L $(LIBFT_DIRECTORY) -l ft

INCLUDES = -I $(HEADERS_DIRECTORY) -I $(LIBFT_HEADERS) -I $(MINILIBX_HEADERS)

#minilib
MINILIBX = $(MINILIBX_DIRECTORY)liblmx.a
MINILIBX_DIRECTORY = ./minilibx_macos/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)
MINILIBX_LINK = -L $(MINILIBX_DIRECTORY) -l mlx -framework OpenGL -framework AppKit

#directories
HEADERS_DIRECTORY = ./includes/
OBJECT_DIRECTORY = ./obj/
SOURCE_DIRECTORY = ./src/

all: obj $(MINILIBX) $(LIBFT) $(NAME)

obj:
		mkdir -p $(OBJECT_DIRECTORY)

$(OBJECT_DIRECTORY)%.o:$(SOURCE_DIRECTORY)%.c
		$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(MINILIBX):
	make -C $(MINILIBX_DIRECTORY)

$(LIBFT):
	make -C $(LIBFT_DIRECTORY)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX_LINK) $(LIBFT_LINK) -lm -o $(NAME)

clean:
	rm -rf $(OBJECT_DIRECTORY)
	make -C $(MINILIBX_DIRECTORY) clean
	make -C $(LIBFT_DIRECTORY) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIRECTORY) fclean

re : fclean all
