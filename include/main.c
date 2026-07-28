#include "cub3d_parser.h"
#include <stdio.h>

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
}

static void	print_map(t_data *data)
{
	int	i;

	printf("Map (%d x %d):\n", data->map_width, data->map_height);
	i = 0;
	while (i < data->map_height)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}

static void	print_data(t_data *data)
{
	printf("NO: %s\n", data->no);
	printf("SO: %s\n", data->so);
	printf("WE: %s\n", data->we);
	printf("EA: %s\n", data->ea);

	printf("Floor   : %d,%d,%d\n",
		data->floor[0], data->floor[1], data->floor[2]);
	printf("Ceiling : %d,%d,%d\n",
		data->ceiling[0], data->ceiling[1], data->ceiling[2]);

	printf("Player : (%d, %d) %c\n",
		data->player_x,
		data->player_y,
		data->player_dir);

	print_map(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Usage: %s map.cub\n", argv[0]);
		return (1);
	}
	init_data(&data);
	if (parse_file(argv[1], &data))
	{
		printf("Error\n");
		return (1);
	}
	printf("Parsing successful!\n\n");
	print_data(&data);
	free_data(&data);
	return (0);
}