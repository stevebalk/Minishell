# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 14:06:14 by sbalk             #+#    #+#              #
#    Updated: 2023/11/28 15:53:08 by sbalk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lexer
LIB_DIR		= libs/libft/
LIB_NAME	= libft.a
CC			= cc
CFLAGS		= -Werror -Wall -Wextra -g
# CFLAGS		= -Werror -Wall -Wextra -fsanitize=address -g
RM			= rm
SRC_DIR		= src/
OBJ_DIR		= obj/
INCLUDE		= -I include -I libs/libft/include

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
				error/error_handling \
				error/error_checks \
				free/free_structs \
				lexer/lexer \
				lexer/lexer_util \
				lexer/lexer_token_logic \
				expander/expander \
				expander/expand_variable \
				expander/checks \
				expander/list_functions \
				expander/expand_word_chunks \
				expander/join_chunks \
				expander/create_chunks \
				expander/env_checks \
				# parser/parser 
				

SRC				=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ				=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))


all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIB_DIR)
			@$(CC) $(CFLAGS) $(OBJ) -L $(LIB_DIR) -lft -o $(NAME)
			@echo "$(GREEN)Created $(NAME)!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)/lexer
			@mkdir -p $(OBJ_DIR)/expander
			# @mkdir -p $(OBJ_DIR)/parser
			@mkdir -p $(OBJ_DIR)/error
			@mkdir -p $(OBJ_DIR)/free
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIB_DIR)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@make fclean -C $(LIB_DIR)
			@$(RM) -f $(NAME)
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
