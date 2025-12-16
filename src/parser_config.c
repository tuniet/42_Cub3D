#include "../include/cub3D.h"

static t_color	*parse_color(char *str)
{
	t_color	*c;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || split_len(rgb) != 3)
		error_exit("Invalid color format");
	if (!is_unsigned_number(rgb[0])
		|| !is_unsigned_number(rgb[1])
		|| !is_unsigned_number(rgb[2]))
		error_exit("Invalid color format");
	c = malloc(sizeof(t_color));
	if (!c)
		error_exit("Malloc failed");
	c->red = ft_atoi(rgb[0]);
	c->green = ft_atoi(rgb[1]);
	c->blue = ft_atoi(rgb[2]);
	if (c->red > 255 || c->green > 255 || c->blue > 255)
		error_exit("Invalid color range");
	free_split(rgb);
	return (c);
}

static t_texture	*new_texture(char *path)
{
	t_texture	*t;
	char		*trimmed;

	if (!path)
		error_exit("Invalid texture path");
	trimmed = trim_spaces(path);
	if (!trimmed || !*trimmed)
		error_exit("Invalid texture path");
	check_texture_file(trimmed);
	t = malloc(sizeof(t_texture));
	if (!t)
		error_exit("Malloc failed");
	t->path = trimmed;
	return (t);
}

void	parse_config_line(t_map *map, char *line)
{
	trim_newline(line);
	if (ft_strncmp(line, "NO ", 3) == 0)
		map->north_text = new_texture(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->south_text = new_texture(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->west_text = new_texture(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->east_text = new_texture(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		map->floor_color = parse_color(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		map->ceiling_color = parse_color(line + 2);
	else
		error_exit("Invalid config line");
}
