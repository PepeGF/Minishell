### --- COLORS --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
YELLOW	= '\033[1;33m'
NONE	= '\033[0m'
BLUE	= '\033[1;34m'


### --- VARIABLES --- ###
NAME = minishell


SRCS_PATH = src/
INCS_PATH = inc/
BIN_PATH = bin/
LIBFT_PATH = libft/

HEADER = $(INCS_PATH)/$(NAME).h

SRCS = main_para_probar_makefile.c 

OBJS = $(SRCS:%.c=bin/%.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
DEBUGFLAGS = -g O3
FANITIZEFLAGS = -fsanitize=address
LIBFT_FLAGS = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft
#LIBRL_FLAGS = -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline
LIBRL_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -lreadline
RM = rm -f

###		RULES		###

all: $(NAME)

$(BIN_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p $(BIN_PATH)
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH) -I/Users/$(USER)/.brew/opt/readline/include -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
	@$(MAKE) -C $(LIBFT_PATH) --silent
	@echo $(PURPLE)"[Creating $(NAME)]"$(NONE)
	@$(CC) -o $(NAME) $(OBJS) $(LIBFT_FLAGS) $(LIBRL_FLAGS) #-fsanitize=address
	@echo $(GREEN)"$(NAME): ready to be executed"$(NONE)

clean:
	@$(RM) $(OBJS)
	@rm -rf $(BIN_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean --silent
	@echo $(RED)"[Object Files Deleted]"$(NONE)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --silent
	@echo $(RED)"[Executable File Deleted]"$(NONE)

re: fclean 
	@$(MAKE)

run:
	@$(MAKE)
	./minishell

.PHONY: all clean fclean re run
