#include "../include/cub3D.h"

static void	validate_config(t_map *map)
{
	if (!map->north_text || !map->south_text
		|| !map->west_text || !map->east_text
		|| !map->floor_color || !map->ceiling_color)
		error_exit("Missing configuration");
}

static void	validate_map(t_map *map)
{
	if (map_height(map->matrix) < 3)
		error_exit("Map too small");
	validate_map_chars(map);
	validate_closed_map(map);
}

void	parse_cub_file(t_data *data)
{
	char	*line;
	int		in_map;

	in_map = 0;
	while ((line = get_next_line(data->map_fd)))
	{
		if (!in_map && is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (!in_map && is_map_line(line))
			in_map = 1;
		if (!in_map)
			parse_config_line(data->map, line);
		else
			add_map_line(&data->map->matrix, line);
		free(line);
	}
	if (!data->map->matrix)
		error_exit("No map found");
	validate_config(data->map);
	validate_map(data->map);
}
