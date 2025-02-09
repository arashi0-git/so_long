/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:59:54 by aryamamo          #+#    #+#             */
/*   Updated: 2025/01/19 10:04:13 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_game(t_game game, char **field, size_t i)
{
	while (i > 0)
		free(field[--i]);
	free(field);
	mlx_clear_window(game.mlx, game.mlx_win);
	mlx_destroy_window(game.mlx, game.mlx_win);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
}

int	open_file(char *av)
{
	int		fd;
	size_t	av_len;

	av_len = ft_strlen(av);
	if (av_len < 4 || ft_strncmp(av + av_len - 4, ".ber", 5))
		error("invalid extension");
	fd = open(av, O_RDONLY);
	if (fd == -1)
		error(strerror(errno));
	return (fd);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	if (ac != 2)
		error("invalid argument");
	fd = open_file(av[1]);
	game = (t_game){0};
	check_fielddata(fd, &game);
	close(fd);
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		error(strerror(errno));
	game.mlx_win = mlx_new_window(game.mlx, game.field.width * TILE_SIZE,
			game.field.height * TILE_SIZE, av[0]);
	if (game.mlx_win == NULL)
		error(strerror(errno));
	get_image(&game);
	mlx_hook(game.mlx_win, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.mlx_win, 17, 1L << 17, close_window, &game);
	mlx_loop(game.mlx);
	free_game(game, game.field.field, game.field.height);
	return (0);
}
