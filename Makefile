### --- COLORS --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
YELLOW	= '\033[1;33m'
NONE	= '\033[0m'
BLUE	= '\033[1;34m'

### --- VARIABLES --- ###

NAME := bin/minishell

MAKEFLAGS += --no-print-directory

MK_DIR = mkdir -p $(@D)

SHELL := /bin/bash
UNAME := $(shell uname -s)



LIBFT := libft/libft.a

SRC_DIR := src/
BUILD_DIR := .build/

SRC := \
main.c \
lexer/lexer.c \
lexer/redir_split.c \
lexer/smart_split.c \
lexer/split_utils.c \
lexer/check_syntax.c \
expander/expander.c \
expander/expander_utils.c \
parser/parser.c \
parser/get_arg_n_pipe.c \
parser/get_files.c \
parser/here_doc.c \
parser/rm_quotes.c \
executor/executor.c \
executor/exec_utils.c \
executor/child_functions.c \
executor/paths.c \
utils/vars_utils.c \
utils/errors.c \
utils/utils.c \
utils/signals.c \
builtins/builtins.c \
builtins/builtins_utils.c \
builtins/builtins_redirections.c \
builtins/env.c \
builtins/pwd.c \
builtins/export.c \
builtins/export_utils.c \
builtins/unset.c \
builtins/echo.c \
builtins/cd.c \
builtins/cd_utils.c \
builtins/exit.c

SRC := $(SRC:%=$(SRC_DIR)%)


INC := \
inc/ \
libft/inc/


OBJS := $(SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)


DEPS := \
$(OBJS:.o=.d) \

CC = gcc

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS := -MMD -MP
DEBUGFLAGS = -g3 #-fsanitize=address

INCS_FLAGS = $(addprefix -I, $(INC)) -I/Users/$(USER)/.brew/opt/readline/include
LINK_FLAGS = $(LIBFT) -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

ifeq ($(UNAME), Linux)
INCS_FLAGS = $(addprefix -I, $(INC)) -I/usr/local/include
LINK_FLAGS = $(LIBFT) -L/usr/local/lib -lreadline
endif

RM = rm -rf

RED_COL :=$(shell tput setaf 1)
GREEN_COL :=$(shell tput setaf 2)
RESET_COL :=$(shell tput sgr0)

all: $(NAME)


$(NAME): $(OBJS) $(LIBFT)
	$(MK_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUGFLAGS) $(OBJS) $(LINK_FLAGS) -o $(NAME)
	@echo "$(GREEN_COL)$(@F) CREATED$(RESET_COL)"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(MK_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUGFLAGS) $(INCS_FLAGS) -c -o $@ $<

$(LIBFT):
	make -C $(dir $(LIBFT))

-include $(DEPS)

clean:
	make clean -C $(dir $(LIBFT))
	$(RM) $(BUILD_DIR)
	@echo "$(RED_COL)$(BUILD_DIR) DELETED$(RESET_COL)"
	@if [ -d "$(BONUS_DIR)$(BUILD_DIR)" ]; then \
		$(RM) $(BONUS_DIR)$(BUILD_DIR); \
		echo "$(RED_COL)$(BONUS_DIR)$(BUILD_DIR) DELETED$(RESET_COL)"; fi

fclean: clean
	make fclean -C $(dir $(LIBFT))
	$(RM) $(dir $(NAME))
	@echo "$(RED_COL)$(dir $(NAME)) DELETED$(RESET_COL)"


re: fclean all

run:
	@$(MAKE)
	@./minishell

print-%:
	$(info '$*'='$($*)')

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"


.PHONY: all clean fclean re gen_dir

.SILENT:

