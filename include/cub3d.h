/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/19 20:53:18 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# define BUFFER_SIZE 10

typedef struct s_data
{
	char			**map;
	int				map_width;
	int				map_height;

	char			*no;
	char			*so;
	char			*we;
	char			*ea;

	int				floor[3];
	int				ceiling[3];
	int				floor_set;
	int				ceiling_set;

	int				map_started;
	int				map_ended;

	int				player_x;
	int				player_y;
	char			player_dir;
}					t_data;

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
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
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

typedef struct s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
	int				color;
}					t_rect;

typedef struct s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			perp_dist;
	int				side;
}					t_ray;

void				run_dda(t_game *game, t_ray *ray);
void				init_dda(t_game *game, t_ray *ray, double *side_dist,
						int *step);
void				draw_walls(t_game *game);
void				update_player(t_game *game);
void				draw_column(t_game *game, int x, t_ray *ray);
void				draw_rect(t_game *game, t_rect rect);
void				update_player(t_game *game);

void				put_pixel(t_game *game, int x, int y, int color);
void				draw_walls(t_game *game);
int					render_frame(t_game *game);
void				move_player(t_game *game, double move_x, double move_y);

int					skip_whitespace(char *str, int i);
int					empty_line_checker(char *line);
int					map_line_checker(char *line);
int					extension_checker(char *file, char *ext);
void				free_map(char **map);
int					texture_parser(char *line, char **dst);
int					color_parser(char *str, int color[3]);
void				free_data(t_data *data);
int					ft_isspace(int c);
int					main_parser(char *line, t_data *data);
int					map_parser(char *line, t_data *data);
int					file_opener(char *file, t_data *data);
int					normalize_map(t_data *data);
int					chars_checker(t_data *data);
int					validate_map(t_data *data);

char				*get_next_line(int fd);

int					init_texture(t_game *game);
int					free_game(t_game *game);
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);
void				move_player(t_game *game, double move_x, double move_y);
void				init_player_from_data(t_game *game);
int					close_game(t_game *game);

#endif
