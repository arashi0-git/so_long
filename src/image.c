/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:19:14 by aryamamo          #+#    #+#             */
/*   Updated: 2025/01/19 10:01:15 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	image_choice(t_game *game, char c)
{
	if (c == '1')
		game->img.img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
				&game->img.img_height, &game->img.img_width);
	else if (c == '0')
		game->img.img = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
				&game->img.img_height, &game->img.img_width);
	else if (c == 'C')
		game->img.img = mlx_xpm_file_to_image(game->mlx,
				"textures/collectable.xpm", &game->img.img_height,
				&game->img.img_width);
	else if (c == 'P')
		game->img.img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
				&game->img.img_height, &game->img.img_width);
	else if (c == 'E')
		game->img.img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
				&game->img.img_height, &game->img.img_width);
	if (game->img.img == NULL)
		error("get_image failed");
}

void	get_image(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->field.height)
	{
		x = 0;
		while (x < game->field.width)
		{
			image_choice(game, game->field.field[y][x]);
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x
				* TILE_SIZE, y * TILE_SIZE);
			mlx_destroy_image(game->mlx, game->img.img);
			if (game->field.field[y][x] == 'P')
			{
				game->player.x = x;
				game->player.y = y;
				game->player_tile = '0';
			}
			x++;
		}
		y++;
	}
}
