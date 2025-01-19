/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:41:38 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/04 12:24:26 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_save(int fd, char *saved, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!gnl_strchr(saved, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		saved = gnl_strjoin(saved, buffer);
		if (!saved)
		{
			free(buffer);
			return (NULL);
		}
	}
	return (saved);
}

static char	*read_to_buffer(int fd, char *saved)
{
	char	*buffer;

	if (!saved)
	{
		saved = gnl_strdup("");
		if (!saved)
			return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	saved = read_and_save(fd, saved, buffer);
	if (!saved)
		return (NULL);
	if (saved[0] == '\0')
	{
		free(saved);
		saved = NULL;
	}
	free(buffer);
	return (saved);
}

static char	*extract_line(char *saved)
{
	char	*line;
	size_t	len;

	if (!saved)
		return (NULL);
	len = 0;
	while (saved[len] && saved[len] != '\n')
		len++;
	line = (char *)malloc((len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	len = 0;
	while (saved[len] && saved[len] != '\n')
	{
		line[len] = saved[len];
		len++;
	}
	if (saved[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

static char	*save_remaining(char *saved)
{
	char	*new_saved;
	size_t	start;

	start = 0;
	while (saved[start] && saved[start] != '\n')
		start++;
	if (!saved[start])
	{
		free(saved);
		return (NULL);
	}
	new_saved = gnl_substr(saved, start + 1, gnl_strlen(saved) - start);
	if (!new_saved)
	{
		free(saved);
		return (NULL);
	}
	free(saved);
	return (new_saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_to_buffer(fd, saved);
	if (!saved)
		return (NULL);
	line = extract_line(saved);
	if (!line)
		return (NULL);
	saved = save_remaining(saved);
	return (line);
}
