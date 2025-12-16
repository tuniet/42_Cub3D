#include "../include/cub3D.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	map_width(char **map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map && map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

void	add_map_line(char ***map, char *line)
{
	char	**new;
	int		i;

	trim_newline(line);
	i = 0;
	while (*map && (*map)[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		error_exit("Malloc failed");
	i = 0;
	while (*map && (*map)[i])
	{
		new[i] = (*map)[i];
		i++;
	}
	new[i++] = ft_strdup(line);
	new[i] = NULL;
	free(*map);
	*map = new;
}
