# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/06 18:25:10 by lcoiffie          #+#    #+#              #
#    Updated: 2020/04/14 20:33:36 by lcoiffie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		Cub3D

LIBFT_A =	libft.a

LIBMLX_A =	libmlx.a

COMP =		gcc $(FLAGS) $(CUB3D_H) $(LIBFT_H) $(MLX_H) -c -o

FLAGS =		-Wall -Werror -Wextra

FLAG_MLX =	-framework OpenGL -framework AppKit

CUB3D_H =	-I includes/

MLX_H =		-I minilibx

LIBFT_H = 	-I libft/includes

OBJ_DIR =	obj/

SRC_DIR =	srcs/

LIB_DIR =	libft/

MLX_DIR =	minilibx/

CFILE =		check_file.c \
			check_map.c \
			cub3d.c \
			errors.c \
			errors2.c \
			floor_and_ceiling.c \
			graphic_closing.c \
			graphic_part_1.c \
			graphic_part_2.c \
			keys.c \
			let_s_play.c \
			map.c \
			move.c \
			move2.c \
			my_mlx_color_functions.c \
			my_mlx_image_functions.c \
			player_vectors_init.c \
			read_line.c \
			resolution.c \
			save.c \
			save2.c \
			sprite_texture.c \
			sprite.c \
			sprite2.c \
			struct_gestion.c \
			texture_image.c \
			texture_image2.c \
			wall_texture.c

CFIND =		$(CFILE:%=$(SRC_DIR)%)

OFILE =		$(CFILE:%.c=%.o)

OBJ =		$(addprefix $(OBJ_DIR), $(OFILE))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)
		@echo Create: Cub3D Object directory

$(NAME): $(OBJ)
		@echo LIBFT START
		@make -C $(LIB_DIR)
		@echo $(LIBFT_A) CREATED
		@echo MLX LIB START
		@make -C $(MLX_DIR)
		@echo $(LIBMLX_A) CREATED
		@gcc  -o $(NAME) $(FLAGS) $(FLAG_MLX) $(addprefix $(MLX_DIR), $(LIBMLX_A))  $(addprefix $(LIB_DIR), $(LIBFT_A)) $(addprefix $(OBJ_DIR), $(OFILE))
		@echo CUB3D COMPLETE

$(OBJ): $(CFIND)
		@$(MAKE) $(OFILE)

$(OFILE):
		@echo Create: $(@:obj/%=%)
		@$(COMP) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
		@/bin/rm -rf $(OBJ_DIR)
		@make -C $(LIB_DIR) clean
		@make -C $(MLX_DIR) clean
		@echo Cleaned Cub3D object files

fclean: clean
		@/bin/rm -f $(NAME)
		@make -C $(LIB_DIR) fclean
		@echo Cleaned $(NAME)

re: fclean all

.PHONY: all clean fclean re

