/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:58:41 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/14 18:47:00 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 10

# endif
# define MAX_FD 10240

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalldigit(const char *str);
int			ft_isalnum(int c);
int			ft_isallalpha(char *str);
int			ft_isallalnum(char *str);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*custom_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			is_allchar(char *str, char c);
int			is_allchar(char *str, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *nptr);
long long	ft_atoll(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		*custom_calloc(size_t nmemb, size_t size, int val);
char		*ft_strdup(const char *s);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_cpytillsep(char const *s, char c);
char		*ft_itoa(int c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *list);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_putnbrbase_fd(unsigned int n, char *base, int fd);
void		ft_putchar_counts(char c, int *charcount);
void		ft_putstr_counts(char *s, int *charcount);
void		ft_putnbr_counts(int n, int *charcount);
void		ft_putnbrbase_counts(uintptr_t n, char *base,
				int *charcount, int iter);
int			ft_printf(const char *str, ...);
char		*get_next_line(int fd);
char		*altered_ft_strjoin(char *s1, char const *s2);
int			ft_has_char(char *str, char c);
char		*ft_strndup(const char *s, size_t n);
void		free_arr(char **arr, int size);
int			ft_countwords(char const *s, char c);
int			ft_max(int a, int b);
int			ft_min(int a, int b);

#endif
