/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:32:22 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/16 16:09:55 by alozpola         ###   ########.fr       */
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

int			skip_whitespace(char *str, int i);
int			empty_line_checker(char *line);
int			map_line_checker(char *line);
int			extension_checker(char *file, char *ext);
void		free_map(char **map);
int			texture_parser(char *line, char **dst);
int			color_parser(char *str, int color[3]);
void		free_data(t_data *data);
int			ft_isspace(int c);
int			main_parser(char *line, t_data *data);
int			map_parser(char *line, t_data *data);
int			file_opener(char *file, t_data *data);
int			normalize_map(t_data *data);
int			chars_checker(t_data *data);
int			validate_map(t_data *data);

char		*get_next_line(int fd);

#endif
