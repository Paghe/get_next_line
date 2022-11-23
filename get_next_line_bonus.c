/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apaghera <apaghera@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:35:21 by apaghera          #+#    #+#             */
/*   Updated: 2022/11/23 17:20:36 by apaghera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	if (size && total / size != count)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}

char	*get_read_line(int fd, char *stash)
{
	char			*buff;
	int				i;

	i = 1;
	buff = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buff)
		return (free(stash), NULL);
	while (i)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (free(buff), free(stash), NULL);
		buff[i] = '\0';
		if (!stash)
			stash = ft_strdup(buff);
		else
			stash = ft_strjoin(stash, buff);
		if (ft_strchr(stash, '\n') != 0)
			i = 0;
	}
	free(buff);
	return (stash);
}

char	*next_line(char *stash)
{
	char	*cpy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n' && ft_strlen(stash) > 1 && stash[i + 1])
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	cpy = ft_calloc(sizeof(char), ft_strlen(stash) - i + 1);
	if (!cpy)
		return (NULL);
	i++;
	while (stash[i])
		cpy[j++] = stash[i++];
	cpy[j] = '\0';
	free(stash);
	return (cpy);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024] = {NULL};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = get_read_line(fd, stash[fd]);
	if (!stash[fd])
		return (free(stash[fd]), NULL);
	line = ft_new_line(stash[fd]);
	if (!line)
		return (free(stash[fd]), NULL);
	stash[fd] = next_line(stash[fd]);
	if (!stash[fd])
		return (free(line), NULL);
	return (line);
}
