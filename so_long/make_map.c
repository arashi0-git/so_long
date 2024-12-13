/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:09:44 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/13 16:36:50 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

t_list	*read_line(int fd)
{
	t_list	*head;
	char	*line;
	size_t	len;
	t_list	*node;

	head = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			ft_lstclear(&head, free);
			exit_for_error("Not cleat node");
		}
		ft_lstadd_back(&head, node);
		line = get_next_line(fd);
	}
	return (head);
}

static int	check_width(t_list *head, size_t *height, size_t *width)
{
	t_list	*node;

	node = head;
	*height = ft_lstsize(head);
	if (*height == 0)
		return (0);
	*width = ft_strlen((char *)head->content);
	while (node)
	{
		if (ft_strlen((char *)node->content) != *width)
			return (0);
		node = node->next;
	}
	return (1);
}

static char	**convert_list(t_list *head, size_t height)
{
	char	**map;
	size_t	i;
	t_list	*temp;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		ft_lstclear(&head, free);
		exit_for_error("Not create map");
	}
	map[height] = NULL;
	while (i < height)
	{
		temp = head;
		head = head->next;
		map[i] = (char *)temp->content;
		free(temp);
		i++;
	}
	return (map);
}

char	**read_map(int fd, size_t *height, size_t *width)
{
	t_list	*head;

	head = read_line(fd);
	if (!head || !check_width(head, height, width))
	{
		ft_lstclear(&head, free);
		exit_for_error("Map is invalid");
	}
	return (convert_list(head, *height));
}
