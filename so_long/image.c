/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:02:42 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/13 20:20:58 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	load_images(t_field *field)
{
	ft_printf("Loading player image: images/player.xpm\n");
	field->img.player = mlx_xpm_file_to_image(field->mlx, "images/player.xpm",
			&field->img.img_width, &field->img.img_height);
	if (!field->img.player)
		exit_for_error("Failed to load player image");
	else
		ft_printf("Player image loaded successfully: %p\n", field->img.player);
	field->img.wall = mlx_xpm_file_to_image(field->mlx, "images/wall.xpm",
			&field->img.img_width, &field->img.img_height);
	field->img.collectible = mlx_xpm_file_to_image(field->mlx,
			"images/collectible.xpm", &field->img.img_width,
			&field->img.img_height);
	field->img.exit = mlx_xpm_file_to_image(field->mlx, "images/exit.xpm",
			&field->img.img_width, &field->img.img_height);
	field->img.floor = mlx_xpm_file_to_image(field->mlx, "images/floor.xpm",
			&field->img.img_width, &field->img.img_height); // オプション
	if (!field->img.player || !field->img.wall || !field->img.collectible
		|| !field->img.exit)
		exit_for_error("Failed to load img");
	if (!field->img.floor)
		exit_for_error("Failed to load floor image");
}
