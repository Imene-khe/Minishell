NAME = libft.a

SRCS =  ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putnbrbase_fd.c \
		ft_printf_functions.c \
		ft_printf.c \
		get_next_line.c \
		ft_has_char.c \
		ft_strndup.c \
		free_arr.c \
		ft_countwords.c \
		ft_max_min.c

OBJS = $(SRCS:%.c=obj/%.o)

BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

BONUS_OBJS = $(BONUS:%.c=obj/%.o)

CC = cc
CFLAG = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS) libft.h

bonus: $(OBJS) $(BONUS_OBJS) $(NAME)
	@ar rcs $(NAME) $(BONUS) $(OBJS) $(BONUS_OBJS) libft.h

obj/%.o: %.c
	@mkdir -p obj
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -rf obj
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
