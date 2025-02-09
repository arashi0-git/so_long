/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:54:16 by aryamamo          #+#    #+#             */
/*   Updated: 2025/02/09 11:11:48 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_middle(char *row, size_t width, t_game *game, size_t y)
{
	size_t	x;

	if (row[0] != '1' || row[width - 1] != '1')
		return (1);
	x = 0;
	while (x < width && row[x] != '\n')
	{
		if (ft_strchr("10CPE", row[x]) == NULL)
			return (1);
		if (row[x] == 'C')
			game->field.collect += 1;
		if (row[x] == 'P')
		{
			game->field.position += 1;
			game->player.x = x;
			game->player.y = y;
		}
		if (row[x] == 'E')
			game->field.exit += 1;
		if (game->field.position > 1 || game->field.exit > 1)
			return (1);
		x++;
	}
	return (0);
}

int	check_wall(char *row)
{
	while (*row)
	{
		if (*row != '1' && *row != '\n')
			return (1);
		row++;
	}
	return (0);
}

size_t	row_len(const char *row)
{
	size_t	i;

	i = 0;
	while (*row != '\0')
	{
		if (ft_strchr("10CPE", *row))
			i++;
		row++;
	}
	return (i);
}

int	field_inform(t_list *field, t_game *game)
{
	size_t	i;

	i = 0;
	game->field.width = row_len(field->content);
	while (field->content != NULL)
	{
		if (i != 0 && game->field.width != row_len(field->content))
			return (1);
		if (i == 0 || i + 1 == game->field.height)
		{
			if (check_wall(field->content) == 1)
				return (1);
		}
		else
		{
			if (check_middle(field->content, game->field.width, game, i) == 1)
				return (1);
		}
		i++;
		field = field->next;
	}
	if (!game->field.collect || !game->field.exit || !game->field.position)
		return (1);
	return (0);
}

void	check_fielddata(int fd, t_game *game)
{
	t_list	*current;
	t_list	head;

	game->field.height = 0;
	errno = 0;
	head.next = NULL;
	current = &head;
	while (1)
	{
		current->next = ft_lstnew(get_next_line(fd));
		if ((!current->next || !current->next->content) && errno)
			error_lstclear(head.next, strerror(errno));
		current = current->next;
		if (current->content == NULL)
			break ;
		game->field.height++;
	}
	if (head.next->content == NULL || field_inform(head.next, game) == 1)
		error_lstclear(head.next, "invalid map");
	move_lst(game, head.next);
	if (is_solve(game) == 1)
		error("map can not solve");
}
