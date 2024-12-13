/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:10:08 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/13 19:06:24 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_map
{
	char		**map;
	size_t		width;
	size_t		height;
	size_t		collect_count;
	size_t		exit_count;
	size_t		player_count;
}				t_map;

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct s_img
{
	void		*player;
	void		*wall;
	void		*collectible;
	void		*exit;
	void		*floor;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct s_field
{
	t_map		map;
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_position	player;
	size_t		move_count;
	size_t		tile_size;
}				t_field;

typedef struct s_dfs
{
	int			**visited;
	size_t		collected;
	int			exit_found;
}				t_dfs;

t_list			*read_line(int fd);
void			check_walls(t_field *field);
void			check_entities(t_field *field);
void			check_solve(t_field *field);
char			**read_map(int fd, size_t *height, size_t *width);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			exit_for_error(char *message);
int				handle_keypress(int keycode, t_field *field);
void			render_map(t_field *field);
void			load_images(t_field *field);

#endif
