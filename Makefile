# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:06:14 by sbalk             #+#    #+#              #
#    Updated: 2023/11/05 16:26:28 by sbalk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
LIB_DIR		= libft/
LIB_NAME	= libft.a
MLX_DIR		= minilibx-linux/
MLX_NAME	= libmlx.a
CC			= cc
CFLAGS		= -Werror -Wall -Wextra -g
# CFLAGS		= -Werror -Wall -Wextra -fsanitize=address -g
RM			= rm
SRC_DIR		= src/
OBJ_DIR		= obj/
INCLUDE		= -I include -I /libs/libft/include -I include -

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES	=	main \
				init/init_fdf \
				init/init_keyhooks \
				init/init_maps \
				init/init_mlx \
				init/init_projections \
				parsing/parsing \
				parsing/check_map \
				parsing/altitude_color \
				user_input/key_handling \
				user_input/key_press_checks \
				draw/draw \
				draw/draw_hud \
				draw/draw_line \
				draw/draw_line_gradient \
				draw/draw_rect \
				draw/draw_mesh \
				draw/update_canvas \
				projection/projection \
				projection/zoom \
				projection/height_manipulation \
				projection/rotation \
				projection/transform \
				projection/autorotate \
				misc/error \
				misc/math \
				misc/exit \

SRC				=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ				=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))


all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIB_DIR)
			@make -C $(MLX_DIR)
			@$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) -lft -L $(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
			# @$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) -lft minilibx-linux/libmlx.a minilibx-linux/libmlx_Darwin.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm -o $(NAME)
			@echo "$(GREEN)Created $(NAME)!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)/user_input
			@mkdir -p $(OBJ_DIR)/projection
			@mkdir -p $(OBJ_DIR)/parsing
			@mkdir -p $(OBJ_DIR)/misc
			@mkdir -p $(OBJ_DIR)/draw
			@mkdir -p $(OBJ_DIR)/init
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIB_DIR)
			@make clean -C $(MLX_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@make fclean -C $(LIB_DIR)
			@$(RM) -f $(NAME)
			@$(RM) -f $(CHECKER)
			@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME)!$(DEF_COLOR)"

norm:
			@norminette $(SRC) include/$(NAME).h| grep -v Norme -B1 || true

git:		fclean
			@git status
			@git add *
			@git status

.PHONY:		all clean fclean re norm git
