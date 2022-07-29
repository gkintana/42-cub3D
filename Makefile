# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 08:46:09 by gkintana          #+#    #+#              #
#    Updated: 2022/07/29 13:09:39 by gkintana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

LIBFT_DIR	=	libft
LIBFT		=	libft.a

ifeq ($(shell uname -s), Linux)
	MLX_DIR		=	minilibx_linux
	MLX			=	libmlx_Linux.a
	LINK_MLX	=	-I$(MLX_DIR) -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
endif

ifeq ($(shell uname -s), Darwin)
	MLX_DIR		=	minilibx_mac
	MLX			=	libmlx.a
	LINK_MLX	=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

INC_DIR		=	include
SRC_DIR		=	sources
OBJ_DIR		=	objects

SRCS		=	main.c \
				draw_functions.c \
				keyboard.c \
				mouse.c \
				parse.c \
				player_calculations.c \
				player_initialization.c \
				raycast_textures.c \
				raycast.c \
				utils.c

OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:%c=%o))

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror
LIB_AR		=	ar rcs
RM			=	rm -rf

DEFAULT		=	"\033[0m"
RED			=	"\033[0;31m"
GREEN		=	"\033[1;32m"
YELLOW		=	"\033[1;33m"
PURPLE		=	"\033[3;35m"
CYAN		=	"\033[3;36m"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@printf $(CYAN)
			$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -I$(MLX_DIR) -O3 -c $< -o $@

all:		$(NAME)

$(NAME):	$(MLX) $(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(LINK_MLX) -o $@

$(LIBFT):
			@printf $(DEFAULT)
			@make -C $(LIBFT_DIR) all

$(MLX):
			@printf $(DEFAULT)
			@make -C $(MLX_DIR) all

clean:
			@make -C $(LIBFT_DIR) fclean
			@make -C $(MLX_DIR) clean
			@$(RM) $(OBJ_DIR)
			@echo $(RED)"Deleted cub3D object files & folder"$(DEFAULT)

fclean:		clean
			@$(RM) $(NAME)
			@echo $(RED)"Deleted cub3D executable"$(DEFAULT)

norm:
			@make -C $(LIBFT_DIR) norm
			@echo $(DEFAULT)$(YELLOW_BU)"cub3D .c files"$(DEFAULT)$(CYAN)
			@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
			@echo $(DEFAULT)$(YELLOW_BU)"cub3D .h files"$(DEFAULT)$(CYAN)
			@norminette -R CheckDefine $(INC_DIR)/*.h

re:			fclean all

.PHONY:		all clean fclean re
