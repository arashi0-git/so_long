/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:21:13 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/13 17:37:57 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

static void	validate_entity(size_t player, size_t collect, size_t exit,
		t_field *field)
{
	field->map.collect_count = collect;
	if (player != 1)
		exit_for_error("Invalid number of players");
	if (collect < 1)
		exit_for_error("No collectables found");
	if (exit != 1)
		exit_for_error("No exit found");
}

static void	count_map_entities(t_field *field, size_t *player, size_t *collect,
		size_t *exit)
{
	size_t	y;
	size_t	x;
	char	c;

	y = 0;
	while (y < field->map.height)
	{
		x = 0;
		while (x < field->map.width)
		{
			c = field->map.map[y][x];
			if (c == 'P')
			{
				(*player)++;
				field->player.x = x;
				field->player.y = y;
			}
			else if (c == 'C')
				(*collect)++;
			else if (c == 'E')
				(*exit)++;
			x++;
		}
		y++;
	}
}

void	check_entities(t_field *field)
{
	size_t	player;
	size_t	collect;
	size_t	exit;

	player = 0;
	collect = 0;
	exit = 0;
	count_map_entities(field, &player, &collect, &exit);
	printf("Debug: Players: %zu, Collectibles: %zu, Exits: %zu\n", player,
		collect, exit);
	validate_entity(player, collect, exit, field);
}
