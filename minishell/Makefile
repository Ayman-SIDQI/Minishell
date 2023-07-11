NAME=minishell
CC=cc
CFLAGS= -Wall -Wextra -Werror#-fsanitize=thread -g# #
LIBFT_DIRECTORY = ./libft/
# ARGS =-Iinclude -lreadline -L /Users/asidqi/.brew/opt/readline/lib -I /Users/asidqi/.brew/opt/readline/include
ARGS =-Iinclude -L/Users/asidqi/.brew/opt/readline/lib -lreadline -I/Users/asidqi/.brew/opt/readline/include
LIBFT = $(LIBFT_DIRECTORY)libft.a
SRC = minishell.c \
      initializors.c \
      env_functions.c \
      builts.c \
      lexer.c \
      lexer_utils.c \
      set_functions.c \
      execution_2.c \
      execution_3.c \
      checkers.c \
      pars_utils.c \
      built_cmds.c \
      util_func.c \
      parsing.c \
      free_func.c \
      support.c \
      pipe_sys.c \
      pwd.c \
      cd.c \
      echo.c \
      export.c \
      heredoc.c \
      single_builtin.c \
      newlfunc.c \
      funcs.c \
      seters.c \
      absocute.c\
      support_two.c\
      support_three.c\
      support_four.c\
      support_five.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(ARGS) -o $(NAME)

%.o: %.c libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIRECTORY) clean

fclean: clean
	@rm -rf $(NAME) $(LIBFT)
	@make -C $(LIBFT_DIRECTORY) fclean

re: fclean $(LIBFT) all

bonus: all

.PHONY: all clean fclean re