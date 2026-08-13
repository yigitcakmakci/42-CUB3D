/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycakmakc <ycakmakc@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 20:13:29 by ycakmakc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSER_H
# define CUB3D_PARSER_H

# include <fcntl.h>
# include <libft.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	char	**map;
	int		map_width;
	int		map_height;

	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	int		floor[3];
	int		ceiling[3];

	int		floor_set;
	int		ceiling_set;

	int		map_started;
	int		map_ended;

	int		player_x;
	int		player_y;
	char	player_dir;
}			t_data;

int			skip_spaces(char *str, int i);
int			is_empty_line(char *line);
int			is_map_line(char *line);
int			check_extension(char *file, char *ext);
void		free_map(char **map);
int			parse_texture(char *line, char **dst);
int			parse_color(char *str, int color[3]);
void		free_data(t_data *data);
int			ft_isspace(int c);
int			parse_config(char *line, t_data *data);
int			parse_map(char *line, t_data *data);
int			parse_file(char *file, t_data *data);
int			normalize_map(t_data *data);
int			check_chars(t_data *data);
int			validate_map(t_data *data);

char		*get_next_line(int fd);

#endif
