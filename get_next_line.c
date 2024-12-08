/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:33:30 by zogrir            #+#    #+#             */
/*   Updated: 2024/12/08 18:39:37 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_read_store(int fd, char *leftover)
{
	char		*buffer;
	ssize_t		byte_read;
	char		*tmp;

	byte_read = 1;
	if (!leftover)
		leftover = ft_strdup("");
	if (!leftover)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(leftover);
		return (NULL);
	}
	while ( byte_read > 0 && !ft_strchr(leftover, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			free(leftover);
			return (NULL);
		}
		if (byte_read == 0)
			break;
		buffer[byte_read] = '\0';
		tmp = ft_strjoin(leftover, buffer);
		free(leftover);
		leftover = tmp;
	}
	free(buffer);
	return (leftover);
}
char	*ft_extract_line(char *leftover)
{
	size_t		i;
	char		*line;

	i = 0;
	if (!leftover || !*leftover)
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, leftover, i + 1);
	return (line);
}

char	*ft_update_leftover(char *leftover)
{
	char		*new_leftover;
	size_t		i;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	new_leftover = ft_strdup(leftover + i + 1);
	free(leftover);
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char		*leftover;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	leftover = ft_read_store(fd, leftover);
	if (!leftover)
		return (NULL);
	line = ft_extract_line(leftover);
	if (!line)
	{
		free (leftover);
		leftover = NULL;
		return (NULL);
	}
	leftover = ft_update_leftover(leftover);
	return (line);
}
