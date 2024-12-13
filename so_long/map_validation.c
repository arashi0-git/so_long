/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:11:22 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/13 17:08:35 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	check_walls(t_field *field)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (x < field->map.width)
	{
		if (field->map.map[0][x] != '1' || field->map.map[field->map.height
			- 1][x] != '1')
			exit_for_error("Map is not surrounded by walls");
		x++;
	}
	while (y < field->map.height)
	{
		if (field->map.map[y][0] != '1' || field->map.map[y][field->map.width
			- 1] != '1')
			exit_for_error("Map is not surrounded by walls");
		y++;
	}
}

static void	dfs(t_field *field, int y, int x, t_dfs *data)
{
	if (y < 0 || (size_t)y >= field->map.height || x < 0
		|| (size_t)x >= field->map.width)
		return ;
	if (field->map.map[y][x] == '1' || data->visited[y][x])
		return ;
	data->visited[y][x] = 1;
	if (field->map.map[y][x] == 'C')
		data->collected++;
	if (field->map.map[y][x] == 'E')
		data->exit_found = 1;
	dfs(field, y - 1, x, data);
	dfs(field, y + 1, x, data);
	dfs(field, y, x - 1, data);
	dfs(field, y, x + 1, data);
}

static void	free_visited(int **visited, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(visited[i++]);
	free(visited);
}

void	check_solve(t_field *field)
{
	size_t	y;
	t_dfs	data;
	size_t	i;

	y = 0;
	i = 0;
	data.visited = (int **)malloc(sizeof(int *) * field->map.height);
	if (!data.visited)
		exit_for_error("Memory allocation failed");
	while (y < field->map.height)
	{
		data.visited[y] = (int *)ft_calloc(field->map.width, sizeof(int));
		if (!data.visited[y])
			exit_for_error("Memory allocation failed");
		y++;
	}
	data.collected = 0;
	data.exit_found = 0;
	dfs(field, (int)field->player.y, (int)field->player.x, &data);
	free_visited(data.visited, field->map.height);
	if (data.collected != field->map.collect_count || data.exit_found == 0)
		exit_for_error("Map is not solvable");
}
