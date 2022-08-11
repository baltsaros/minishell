C_PURPLE_B		=\033[1;95m
C_YELLOW_B		=\033[1;33m
C_RED_B			=\033[1;31m
C_WHITE			=\033[0;97m
C_GREEN			=\033[0;32m
C_GREEN_B		=\033[1;32m
C_RESET			=\033[0m

NAME		= minishell

SRCS		= minishell.c \
				minishell_utils_1.c \
				minishell_utils_2.c \
				nodes_1.c \
				nodes_2.c \
				alloc_check.c \
				ms_free.c \
				parsing_utils.c \
				parsing_utils_2.c \
				parsing_utils_3.c \
				check_input_1.c \
				check_input_2.c \
				data_init.c \
				tokenization.c \
				wildcard.c \
				parsing.c \
				execute.c \
				messages.c \
				execute_utils_1.c \
				execute_utils_2.c \
				execute_utils_3.c \
				signals.c \
				yo_export.c \
				yo_export_utils.c \
				yo_echo.c \
				yo_cd.c \
				yo_env.c \
				yo_unset.c \
				yo_exit.c \
				yo_pwd.c \
				token_simplification.c \
				token_simplification_utils.c \
				token_simplification_utils_2.c \
				token_simplification_utils_3.c \
				token_simplification_utils_4.c \
				dollar_simplification.c \
				quote_transformation.c \
				word_total.c \
				add_flags.c \
				syntax_checker.c

OBJ_DIR		= objs
OBJ_FILES	= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

INCS		= -Ilibft

GCC			= gcc
RM			= rm -f
RMF			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g
CFLAGS_COMP = -lreadline

all:		libft $(NAME)

brew :
			@brew install readline
			@printf "\n$(C_GREEN_B)Installed!$(C_RESET)\n";

$(OBJ_DIR)/%.o: %.c
			@mkdir -p $(OBJ_DIR)
			@printf "$(C_GREEN).$(C_RESET)";
			@$(GCC) $(CFLAGS) -c $< $(INCS) -o $@

$(NAME):	$(OBJS) 
			@$(GCC) $(OBJS) ${INCS} libft/libft.a -o $(NAME) $(CFLAGS_COMP) -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include/
			@printf "\n$(C_GREEN_B)Finished!$(C_RESET)\n";

libft:
			@make -C ./libft

norm:
			@echo "$(C_PURPLE_B)Let's test the Norm!$(C_RESET)";
			@norminette
			@echo "$(C_PURPLE_B)Done!$(C_RESET)";

clean:
			@echo "$(C_RED_B)Deleting minishell o-files...$(C_RESET)";
			@make -C ./libft clean
			@$(RM) $(OBJS)
			@$(RMF) $(OBJ_DIR)
			@echo "$(C_RED_B)Minishell o-files have been deleted!$(C_RESET)";

fclean:		clean
			@make -C ./libft fclean
			@echo "$(C_RED_B)Deleting minishell program...$(C_RESET)";
			@$(RM) $(NAME)
			@echo "$(C_RED_B)Minishell program has been deleted!$(C_RESET)";

re:			fclean all

val:		${NAME}
			valgrind --leak-check=full ./$(NAME)

.PHONY:		all clean fclean libft re .c.o norm brew val
