/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:53:29 by zogrir            #+#    #+#             */
/*   Updated: 2024/12/16 11:41:28 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_store(int fd, char *leftover)
{
	char		*buffer;
	int		byte_read;
	char		*tmp;

	byte_read = 1;
	if (!leftover)
		leftover = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(leftover), NULL);
	while (byte_read > 0 && !ft_strchr(leftover, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buffer), free(leftover), NULL);
		if (byte_read == 0)
			break ;
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
	if (!leftover[i] || !leftover)
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
	static char		*leftover[OPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	leftover[fd] = ft_read_store(fd, leftover[fd]);
	if (!leftover[fd])
		return (NULL);
	line = ft_extract_line(leftover[fd]);
	leftover[fd] = ft_update_leftover(leftover[fd]);
	return (line);
}
