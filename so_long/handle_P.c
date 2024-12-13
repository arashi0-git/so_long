/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_P.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:50:52 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/13 20:03:26 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	render_map(t_field *field)
{
	size_t	x;
	size_t	y;
	char	c;

	mlx_clear_window(field->mlx, field->mlx_win);
	y = 0;
	while (y < field->map.height)
	{
		x = 0;
		while (x < field->map.width)
		{
			c = field->map.map[y][x];
			if (c == '1')
				mlx_put_image_to_window(field->mlx, field->mlx_win,
					field->img.wall, x * field->tile_size, y
					* field->tile_size);
			else if (c == 'P')
				mlx_put_image_to_window(field->mlx, field->mlx_win,
					field->img.player, x * field->tile_size, y
					* field->tile_size);
			else if (c == 'C')
				mlx_put_image_to_window(field->mlx, field->mlx_win,
					field->img.collectible, x * field->tile_size, y
					* field->tile_size);
			else if (c == 'E')
				mlx_put_image_to_window(field->mlx, field->mlx_win,
					field->img.exit, x * field->tile_size, y
					* field->tile_size);
			else if (c == '0')
				mlx_put_image_to_window(field->mlx, field->mlx_win,
					field->img.floor, x * field->tile_size, y
					* field->tile_size);
			x++;
		}
		y++;
	}
}

void	move_player(t_field *field, int dy, int dx)
{
	int		new_y;
	int		new_x;
	char	dest_tile;

	new_y = field->player.y + dy;
	new_x = field->player.x + dx;
	dest_tile = field->map.map[new_y][new_x];
	if (dest_tile == '1')
		return ;
	if (dest_tile == 'C')
	{
		field->map.collect_count--;
		field->map.map[new_y][new_x] = '0';
	}
	if (dest_tile == 'E')
	{
		if (field->map.collect_count == 0)
		{
			mlx_destroy_window(field->mlx, field->mlx_win);
			exit(0);
		}
		else
			return ;
	}
	field->map.map[field->player.y][field->player.x] = '0';
	field->map.map[new_y][new_x] = 'P';
	field->player.y = new_y;
	field->player.x = new_x;
	render_map(field);
}

int	handle_keypress(int keycode, t_field *field)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(field->mlx, field->mlx_win);
		exit(0);
	}
	else if (keycode == KEY_W)
		move_player(field, -1, 0);
	else if (keycode == KEY_S)
		move_player(field, 1, 0);
	else if (keycode == KEY_A)
		move_player(field, 0, -1);
	else if (keycode == KEY_D)
		move_player(field, 0, 1);
	return (0);
}
