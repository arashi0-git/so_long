/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:18:01 by aryamamo          #+#    #+#             */
/*   Updated: 2025/01/16 16:20:28 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	update_position(t_game *game, size_t prev_x, size_t prev_y)
{
	char	prev_tile;

	prev_tile = game->player_tile;
	game->field.field[prev_y][prev_x] = prev_tile;
	image_choice(game, prev_tile);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, prev_x
		* TILE_SIZE, prev_y * TILE_SIZE);
	mlx_destroy_image(game->mlx, game->img.img);
	game->player_tile = game->field.field[game->player.y][game->player.x];
	game->field.field[game->player.y][game->player.x] = 'P';
	image_choice(game, 'P');
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img,
		game->player.x * TILE_SIZE, game->player.y * TILE_SIZE);
	mlx_destroy_image(game->mlx, game->img.img);
	if (game->player_tile == 'C')
	{
		game->field.collect--;
		game->player_tile = '0';
	}
	return (0);
}

int	allow_move(t_game *game, char next_p)
{
	if (next_p == 'E')
	{
		if (game->field.collect == 0)
			mlx_loop_end(game->mlx);
	}
	if (next_p != '1')
	{
		game->move_count += 1;
		ft_putstr_fd("move count-> ", 1);
		ft_putnbr_fd(game->move_count, 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	return (0);
}

void	updata_player(t_game *game, size_t x, size_t y)
{
	game->player.x = x;
	game->player.y = y;
}

int	handle_key(int key, void *game0)
{
	size_t	x;
	size_t	y;
	t_game	*game;

	game = (t_game *)game0;
	x = game->player.x;
	y = game->player.y;
	if (key == KEY_ESC)
		mlx_loop_end(game->mlx);
	if (key == KEY_W || key == KEY_Z || key == KEY_UP)
		game->player.y -= 1;
	else if (key == KEY_S || key == KEY_DOWN)
		game->player.y += 1;
	else if (key == KEY_A || key == KEY_Q || key == KEY_LEFT)
		game->player.x -= 1;
	else if (key == KEY_D || key == KEY_RIGHT)
		game->player.x += 1;
	else
		return (0);
	if (allow_move(game, game->field.field[game->player.y][game->player.x]))
		update_position(game, x, y);
	else
		updata_player(game, x, y);
	return (0);
}

int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}
