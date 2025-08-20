NAME = minishell

SRCS = $(addprefix src/, \
						main.c \
						process.c \
						lexer/lexing.c \
						expander/expanding.c \
						expander/expanding_utils.c \
						parser/parsing.c \
						parser/paths.c \
						executor/exec.c \
						executor/redir.c \
						executor/heredoc.c \
						executor/pipe.c \
						executor/cmds.c \
						executor/execution.c \
						builtins/builtins1.c \
						builtins/builtins2.c \
						builtins/built_tools.c \
						builtins/export.c \
						errors/errors1.c \
						errors/errors2.c \
						utils/split.c \
						utils/split_again.c \
						utils/tools1.c \
						utils/tools2.c \
						utils/tools3.c \
						utils/frees.c \
						utils/custom_strdup.c \
						utils/custom_strjoin.c \
						utils/lists/line.c \
						utils/lists/history.c \
						environment/env1.c \
						environment/env2.c \
						environment/env3.c \
						utils/trees/trees1.c \
						utils/trees/trees2.c \
						signals/signals.c \
						signals/signals2.c \
						signals/signals3.c)

OBJS = $(SRCS:src/%.c=objs/%.o)

LIBFT = include/libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@cc -o $@ $^ -L include/libft -lft -lreadline -lhistory
	@echo COMPILED

objs/%.o: src/%.c
	@mkdir -p $(dir $@)
	@cc $(FLAGS) -I include/libft -c $< -o $@

$(LIBFT):
	@$(MAKE) -C include/libft

clean:
	@rm -rf objs
	@$(MAKE) -C include/libft clean
	@echo CLEANED

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C include/libft fclean

re: fclean all

.PHONY: all clean fclean re
