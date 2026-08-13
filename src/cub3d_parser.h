/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alozpola <alozpola@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 18:04:29 by alozpola          #+#    #+#             */
/*   Updated: 2026/08/13 18:04:30 by alozpola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSER_H
# define CUB3D_PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

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
}	t_data;

int		skip_spaces(char *str, int i);
int		is_empty_line(char *line);
int		is_map_line(char *line);
int		check_extension(char *file, char *ext);
void	free_map(char **map);
int		parse_texture(char *line, char **dst);
int		parse_color(char *str, int color[3]);
void	free_data(t_data *data);
int		ft_isspace(int c);
int		parse_config(char *line, t_data *data);
int		parse_map(char *line, t_data *data);
int		parse_file(char *file, t_data *data);
int		normalize_map(t_data *data);
int		check_chars(t_data *data);
int		validate_map(t_data *data);

int		ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);
char	*get_next_line(int fd);

#endif