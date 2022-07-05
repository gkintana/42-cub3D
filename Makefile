# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 08:46:09 by gkintana          #+#    #+#              #
#    Updated: 2022/07/05 22:55:24 by gkintana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

LIBFT_DIR	=	libft
LIBFT		=	libft.a

MLXL_DIR	=	minilibx_linux
MLXL		=	libmlx_Linux.a
LINK_MLXL	=	-L$(MLXL_DIR) -lmlx_Linux -I$(MLXL_DIR) -lXext -lX11 -lm -lz

MLXM_DIR	=	minilibx_mac
MLXM		=	libmlx.a
LINK_MLXM	=	-L $(MLXM_DIR) -lmlx -framework OpenGL -framework AppKit

INC_DIR		=	include
SRC_DIR		=	sources
OBJ_DIR		=	objects

SRCS		=	main.c

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
			$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -I$(MLXL_DIR) -O3 -c $< -o $@
# $(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -I$(MLXM_DIR) -O3 -c $< -o $@

all:		$(NAME)

# LINUX
$(NAME):	$(MLXL) $(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(LINK_MLXL) -o $@

# MAC
# $(NAME):	$(MLXM) $(LIBFT) $(OBJS)
# 			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(LINK_MLXM) -o $@

$(LIBFT):
			@printf $(DEFAULT)
			@make -C $(LIBFT_DIR) all

$(MLXL):
			@printf $(DEFAULT)
			@make -C $(MLXL_DIR) all

$(MLXM):
			@printf $(DEFAULT)
			@make -C $(MLXM_DIR) all

clean:
			@make -C $(LIBFT_DIR) fclean
			@make -C $(MLXL_DIR) clean
			@make -C $(MLXM_DIR) clean
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
