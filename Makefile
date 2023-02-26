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
DEP_PATH = dep/
LIBFT_PATH = libft/

HEADER = $(INCS_PATH)/$(NAME).h

SRCS = main_para_probar_makefile.c 

OBJS = $(SRCS:%.c=$(BIN_PATH)%.o)
DEPS = $(OBJS:.o=$(DEP_PATH).d)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
DEPFLAGS = -MMD -MP -I inc
DEBUGFLAGS = -g O3
FANITIZEFLAGS = -fsanitize=address

INCS_FLAGS = -I$(LIBFT_PATH) -I/Users/$(USER)/.brew/opt/readline/include
LINK_FLAGS = -L$(LIBFT_PATH) -lft -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

RM = rm -f
MK_DIR = mkdir -p $(@D)

###		RULES		###

all: $(NAME)

$(BIN_PATH)%.o: $(SRCS_PATH)%.c
	@$(MK_DIR)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCS_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
	@echo $(PURPLE)"[Creating libft]"$(NONE)
	@$(MAKE) -C $(LIBFT_PATH) --silent
	@echo $(PURPLE)"[Creating $(NAME)]"$(NONE)
	@$(CC) -o $(NAME) $(OBJS) $(LINK_FLAGS) #-fsanitize=address
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
	@./minishell

print-%:
	$(info '$*'='$($*)')

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

.PHONY: all clean fclean re run
