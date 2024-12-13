/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:30:25 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/13 20:21:42 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	exit_for_error(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	exit(1);
}

int	open_map(char *av1)
{
	int		fd;
	size_t	av1_len;

	fd = 0;
	av1_len = ft_strlen(av1);
	if (fd < 0)
		exit_for_error(strerror(errno));
	if (av1_len < 4 || ft_strncmp(av1 + av1_len - 4, ".ber", 5))
		exit_for_error("Invalid extension");
	fd = open(av1, O_RDONLY);
	if (fd == -1)
		exit_for_error(strerror(errno));
	return (fd);
}

int	handle_destroy(void *param)
{
	t_field	*field;

	field = (t_field *)param;
	if (field->img.player)
		mlx_destroy_image(field->mlx, field->img.player);
	if (field->img.wall)
		mlx_destroy_image(field->mlx, field->img.wall);
	if (field->img.collectible)
		mlx_destroy_image(field->mlx, field->img.collectible);
	if (field->img.exit)
		mlx_destroy_image(field->mlx, field->img.exit);
	if (field->img.floor)
		mlx_destroy_image(field->mlx, field->img.floor);
	mlx_destroy_window(field->mlx, field->mlx_win);
	exit(0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_field	field;

	field.tile_size = 100;
	if (argc != 2)
		exit_for_error("invalid argument");
	fd = open_map(argv[1]);
	field.map.map = read_map(fd, &field.map.height, &field.map.width);
	close(fd);
	check_walls(&field);
	check_entities(&field);
	check_solve(&field);
	field.mlx = mlx_init();
	if (!field.mlx)
		exit_for_error("MLX initialization failed");
	load_images(&field);
	field.mlx_win = mlx_new_window(field.mlx, field.map.width * field.tile_size,
			field.map.height * field.tile_size, "so_long");
	if (!field.mlx_win)
		exit_for_error("Window create failed");
	mlx_hook(field.mlx_win, 2, 1L << 0, handle_keypress, &field);
	mlx_hook(field.mlx_win, 17, 0, handle_destroy, NULL);
	render_map(&field);
	mlx_loop(field.mlx);
	return (0);
}
