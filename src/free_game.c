#include "cub3d.h"
#include "cub3d_parser.h"
#include "cub3d_raycasting.h"

/* ************************************************************************** */
/*                         PARSER (t_data) CLEANUP                            */
/* ************************************************************************** */

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
	free_map(data->map);
	ft_memset(data, 0, sizeof(t_data));
}

/* ************************************************************************** */
/*                       MLX (t_configuration) CLEANUP                        */
/* ************************************************************************** */

/* addr img'in ic buffer'i oldugundan ayrica free edilmez */
void	free_conf(t_configuration *conf)
{
	if (!conf || !conf->mlx)
		return ;
	if (conf->img)
		mlx_destroy_image(conf->mlx, conf->img);
	if (conf->win)
		mlx_destroy_window(conf->mlx, conf->win);
	mlx_destroy_display(conf->mlx);
	free(conf->mlx);
	conf->img = NULL;
	conf->win = NULL;
	conf->addr = NULL;
	conf->mlx = NULL;
}

/* ************************************************************************** */
/*                            FULL GAME CLEANUP                               */
/* ************************************************************************** */

int	free_game(t_game *game)
{
	if (!game)
		return (0);
	free_data(&game->data);
	free_conf(&game->conf);
	return (0);
}