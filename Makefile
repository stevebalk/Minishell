# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:06:14 by sbalk             #+#    #+#              #
#    Updated: 2023/11/10 18:16:07 by jopeters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIB_DIR		= libs/libft/
LIB_NAME	= libft.a
CC			= cc
CFLAGS		= -Werror -Wall -Wextra -g 
# CFLAGS		= -Werror -Wall -Wextra -fsanitize=address -g
RM			= rm
SRC_DIR		= src/
OBJ_DIR		= obj/
INCLUDE		= -I include -I /libs/libft/include -I /libs/readline
READLINE_DIR = /libs/readline
READLINE_NAME = libreadline.a


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
				utils/colors_a \
				utils/colors_b \
				utils/history \
				prompt/prompt

SRC				=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ				=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))


all:		$(NAME)

read:
			@echo $(shell pwd) 
			cd $(shell pwd)/libs/readline && @echo $(shell pwd) 			
#			./configure
#			cd $(READLINE_DIR) && ./configure
#			./configure
#			@make -C $(READLINE_DIR)
			
# $(READLINE_DIR)$(READLINE_NAME) -lreadline
$(NAME):	$(OBJ)
			@make -C $(LIB_DIR)
#			@$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) -lft -o $(NAME)
			@$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) -lft -o $(NAME) -lreadline
			@echo "$(GREEN)Created $(NAME)!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)/utils
			@mkdir -p $(OBJ_DIR)/prompt
			
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIB_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@make fclean -C $(LIB_DIR)
			@$(RM) -f $(NAME)
#			@echo "$(CYAN)$(NAME) executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for $(NAME)!$(DEF_COLOR)"

norm:
			@norminette $(SRC) include/$(NAME).h| grep -v Norme -B1 || true

git:		fclean
			@git status
			@git add *
			@git status

.PHONY:		all clean fclean re norm git
