/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguerrou <bguerrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:25:38 by bguerrou          #+#    #+#             */
/*   Updated: 2025/08/14 18:09:40 by bguerrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_alt_strchr(char *s, int c)
{
	int		i;
	int		j;
	char	*new;
	int		len;

	i = 0;
	while (s[i] && s[i] != (char) c)
		i++;
	len = ft_strlen(s) - i;
	new = malloc(sizeof(char) * len + 2);
	if (!new)
		return (NULL);
	j = 0;
	while (j < len)
		new[j++] = s[++i];
	new[j] = '\0';
	free(s);
	return (new);
}

static char	*ft_cut(char *src, char sep)
{
	char	*str;
	int		char_pos;
	int		i;

	if (!src)
		return (NULL);
	char_pos = 0;
	while (src[char_pos] && src[char_pos] != sep)
		char_pos++;
	str = malloc(sizeof(char) * char_pos + 2);
	if (!str)
		return (NULL);
	i = -1;
	while (++i <= char_pos)
		str[i] = src[i];
	str[i] = '\0';
	return (str);
}

char	*altered_ft_strjoin(char *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = ft_calloc(sizeof(char), len + 2);
	if (!join)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		join[i] = (s1)[i];
	free(s1);
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	return (join);
}

static char	*get_next(int fd, char *cursor, char *buffer)
{
	int			reader;

	reader = 1;
	if (!cursor)
		cursor = ft_calloc(1, sizeof(char));
	if (!cursor)
		return (NULL);
	while (!ft_has_char(cursor, '\n') && reader)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		buffer[reader] = '\0';
		cursor = altered_ft_strjoin(cursor, buffer);
		if (!cursor)
			return (NULL);
		if (reader == 0 && !ft_strlen(cursor))
			return (free(cursor), NULL);
	}
	return (cursor);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*cursor[MAX_FD];
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(cursor[fd]);
		cursor[fd] = NULL;
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	cursor[fd] = get_next(fd, cursor[fd], buffer);
	free(buffer);
	if (!cursor[fd])
		return (NULL);
	line = ft_cut(cursor[fd], '\n');
	if (!line)
		return (NULL);
	cursor[fd] = ft_alt_strchr(cursor[fd], '\n');
	if (!cursor[fd])
		return (free(line), NULL);
	return (line);
}
