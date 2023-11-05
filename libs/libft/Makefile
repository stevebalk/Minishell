NAME		=	libft.a
INCLUDES	=	include/
SRCS_DIR 	=	src/
OBJS_DIR	=	obj/
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g -I
RM			=	rm -f
AR			=	ar rcs

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

FTIS_DIR		=	ft_is/
FTIS			=	ft_isalnum ft_isalpha ft_isascii ft_isdigit \
					ft_isprint ft_is_str_int ft_is_str_num ft_is_space

FTMEM_DIR		=	ft_mem/
FTMEM			=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove ft_memset \
					ft_free_array ft_free_2darray

FTPUT_DIR		=	ft_put/
FTPUT			=	ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd \
					ft_putnbr_base

FTTO_DIR		=	ft_to/
FTTO			=	ft_atoi ft_atolli ft_itoa ft_tolower ft_toupper

FTSTR_DIR		=	ft_str/
FTSTR			=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
					ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
					ft_strnstr ft_strrchr ft_strtrim ft_substr ft_streq \
					ft_strnjoin

FTLST_DIR		=	ft_lst/
FTLST			=	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
					ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

FTNUM_DIR		=	ft_num/
FTNUM			=	ft_abs ft_round ft_sign

FTPRINTF_DIR	=	ft_printf/
FTPRINTF		=	ft_parse ft_print_chars ft_printf ft_print_hex ft_print_nbrs ft_util

GNL_DIR			=	get_next_line/
GNL				=	get_next_line get_next_line_utils

SRC_FILES+=$(addprefix $(FTIS_DIR),$(FTIS))
SRC_FILES+=$(addprefix $(FTMEM_DIR),$(FTMEM))
SRC_FILES+=$(addprefix $(FTPUT_DIR),$(FTPUT))
SRC_FILES+=$(addprefix $(FTTO_DIR),$(FTTO))
SRC_FILES+=$(addprefix $(FTSTR_DIR),$(FTSTR))
SRC_FILES+=$(addprefix $(FTLST_DIR),$(FTLST))
SRC_FILES+=$(addprefix $(FTNUM_DIR),$(FTNUM))
SRC_FILES+=$(addprefix $(FTPRINTF_DIR),$(FTPRINTF))
SRC_FILES+=$(addprefix $(GNL_DIR),$(GNL))

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJSF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)
			@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJSF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJSF):
			@mkdir -p $(OBJS_DIR)
			@mkdir -p $(OBJS_DIR)$(FTIS_DIR)
			@mkdir -p $(OBJS_DIR)$(FTMEM_DIR)
			@mkdir -p $(OBJS_DIR)$(FTPUT_DIR)
			@mkdir -p $(OBJS_DIR)$(FTTO_DIR)
			@mkdir -p $(OBJS_DIR)$(FTSTR_DIR)
			@mkdir -p $(OBJS_DIR)$(FTLST_DIR)
			@mkdir -p $(OBJS_DIR)$(FTNUM_DIR)
			@mkdir -p $(OBJS_DIR)$(FTPRINTF_DIR)
			@mkdir -p $(OBJS_DIR)$(GNL_DIR)

clean:
			@$(RM) -rf $(OBJS_DIR)
			@$(RM) -f $(OBJSF)
			@echo "$(BLUE)libft objects files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

norm:
	@norminette $(SRCS) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm