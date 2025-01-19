/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:43:36 by aryamamo          #+#    #+#             */
/*   Updated: 2025/01/15 16:47:11 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_lst(t_game *game, t_list *field)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	game->field.field = (char **)ft_calloc(game->field.height + 1,
			sizeof(char *));
	if (game->field.field == NULL)
		error_lstclear(field, "faild malloc");
	tmp = field;
	while (i < game->field.height)
	{
		game->field.field[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&field, NULL);
}

void	dfs(t_game *game, int y, int x, t_dfs *data)
{
	if (y < 0 || y >= (int)game->field.height || x < 0
		|| x >= (int)game->field.width)
		return ;
	if (game->field.field[y][x] == '1' || data->visited[y][x])
		return ;
	data->visited[y][x] = 1;
	if (game->field.field[y][x] == 'C')
		data->collected++;
	if (game->field.field[y][x] == 'E')
		data->exit_found = 1;
	dfs(game, y - 1, x, data);
	dfs(game, y + 1, x, data);
	dfs(game, y, x - 1, data);
	dfs(game, y, x + 1, data);
}

static void	free_visited(int **visited, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(visited[i++]);
	free(visited);
}

int	is_solve(t_game *game)
{
	size_t	y;
	t_dfs	data;
	size_t	i;

	y = 0;
	i = 0;
	data.visited = (int **)malloc(sizeof(int *) * game->field.height);
	if (!data.visited)
		error("malloc error");
	while (y < game->field.height)
	{
		data.visited[y] = (int *)ft_calloc(game->field.width, sizeof(int));
		if (!data.visited[y])
			error("malloc error");
		y++;
	}
	data.collected = 0;
	data.exit_found = 0;
	dfs(game, (int)game->player.y, (int)game->player.x, &data);
	free_visited(data.visited, game->field.height);
	if (data.collected != game->field.collect || data.exit_found == 0)
		return (1);
	return (0);
}
