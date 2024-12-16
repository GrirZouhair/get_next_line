/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:33:30 by zogrir            #+#    #+#             */
/*   Updated: 2024/12/16 11:23:21 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_store(int fd, char *leftover)
{
	char		*buffer;
	int			byte_read;
	char		*tmp;

	byte_read = 1;
	if (!leftover)
		leftover = ft_strdup("");
	buffer = malloc(sizeof(char) * (size_t)(BUFFER_SIZE + 1));
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
	return (free(buffer), leftover);
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
		return (free(leftover), NULL);
	new_leftover = ft_strdup(leftover + i + 1);
	return (free(leftover), new_leftover);
}

char	*get_next_line(int fd)
{
	static char		*leftover;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = ft_read_store(fd, leftover);
	if (!leftover)
		return (NULL);
	line = ft_extract_line(leftover);
	leftover = ft_update_leftover(leftover);
	return (line);
}
