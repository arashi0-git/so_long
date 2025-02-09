/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:00:49 by aryamamo          #+#    #+#             */
/*   Updated: 2025/01/16 16:16:08 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>

# define TILE_SIZE 64

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_Z 122
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100

# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

# define KEY_ESC 65307

typedef struct s_queue
{
	size_t			x;
	size_t			y;
	struct s_queue	*next;
}					t_queue;

typedef struct s_field
{
	char			**field;
	size_t			width;
	size_t			height;
	size_t			collect;
	size_t			exit;
	size_t			position;
}					t_field;

typedef struct s_player
{
	size_t			x;
	size_t			y;

}					t_player;

typedef struct s_img
{
	void			*img;
	int				img_width;
	int				img_height;
}					t_img;

typedef struct s_game
{
	t_field			field;
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	t_player		player;
	size_t			move_count;
	char			player_tile;
}					t_game;

typedef struct s_dfs
{
	int				**visited;
	size_t			collected;
	int				exit_found;
}					t_dfs;

void				move_lst(t_game *game, t_list *field);
void				error_lstclear(t_list *map, char *msg);
void				error(char *msg);
void				check_fielddata(int fd, t_game *game);
int					handle_key(int key, void *game0);
void				image_choice(t_game *game, char c);
int					close_window(t_game *game);
void				get_image(t_game *game);
int					is_solve(t_game *game);

#endif