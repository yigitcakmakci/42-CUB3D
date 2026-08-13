/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 21:37:24 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_parser.h"
# include "mlx.h"

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef struct s_key_control
{
	int				key_W;
	int				key_A;
	int				key_S;
	int				key_D;
	int				key_right_arrow;
	int				key_left_arrow;
}					t_key_control;

typedef struct s_player
{
	t_key_control	key_control;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			angle;
}					t_player;

typedef struct s_window
{
	int				height;
	int				width;
	int				fov;
}					t_window;

typedef struct s_configuration
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_configuration;

typedef struct s_game
{
	t_data			data;
	t_window		window;
	t_configuration	conf;
	t_player		player;
	t_texture		texture[4];
}					t_game;

int					init_texture(t_game *game);
int					free_game(t_game *game);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
void				move_player(t_game *game, double move_x, double move_y);
void				init_player_from_data(t_game *game);
int					close_game(t_game *game);

#endif
