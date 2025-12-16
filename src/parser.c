#include "../include/cub3D.h"

void	error_exit(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

// ================ FILES CHECK ============

int	has_png_extension(char *path)
{
	int len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strcmp(path + len - 4, ".png") == 0);
}

int	has_xpm_extension(char *path)
{
	int len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strcmp(path + len - 4, ".xpm") == 0);
}

void	check_texture_file(char *path)
{
	int	fd;

  //TODO : change to xpn
	//if (!has_png_extension(path))
	//	error_exit("Texture must be a .png file");
	if (!has_xpm_extension(path))
		error_exit("Texture must be a .xpm file");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Texture file not found or unreadable");
	close(fd);
}

// ================ GNL ============

char	*get_next_line(int fd)
{
	char	c;
	char	*line;
	int		i;
	int		r;

	i = 0;
	line = malloc(10000);
	if (!line)
		return (NULL);
	r = read(fd, &c, 1);
	while (r > 0)
	{
		line[i++] = c;
		if (c == '\n')
			break;
		r = read(fd, &c, 1);
	}
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

// =========== SPLIT ===========

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	if (len != 0)
		ft_strlcpy(ret, s + start, len + 1);
	else
		ret[0] = '\0';
	return (ret);
}

static int	ft_wrdcount(const char *s, char c)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			ret++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**ret;

	i = ft_wrdcount(s, c);
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	if (!ret)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			ret[i++] = ft_substr(s, 0, len);
			s += len;
		}
	}
	ret[i] = NULL;
	return (ret);
}

// =========== UTILS ===========

char	*trim_spaces(char *s)
{
	int		start;
	int		end;
	char	*trimmed;

	start = 0;
	while (s[start] == ' ' || s[start] == '\t')
		start++;
	end = ft_strlen(s);
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		end--;
	trimmed = ft_substr(s, start, end - start);
	if (!trimmed)
		error_exit("Malloc failed");
	return (trimmed);
}

void	trim_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
			return ;
		}
		i++;
	}
}

int	is_unsigned_number(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0');
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
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

// =========== MAP-UTILS ===========

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

// =========== PARSING ===========

t_color	*parse_color(char *str)
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

t_texture	*new_texture(char *path)
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

// =========== CONFIGURATION  ===========

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

// =========== MAP VALIDATION ===========

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

char	get_map_char(t_map *map, int y, int x)
{
	if (y < 0 || x < 0 || !map->matrix[y]
		|| x >= (int)ft_strlen(map->matrix[y]))
		return (' ');
	return (map->matrix[y][x]);
}

int	is_valid_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	validate_map_chars(t_map *map)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (map->matrix[y])
	{
		x = 0;
		while (map->matrix[y][x])
		{
			if (!is_valid_map_char(map->matrix[y][x]))
				error_exit("Invalid map character");
			if (ft_strchr("NSEW", map->matrix[y][x]))
				player++;
			x++;
		}
		y++;
	}
	if (player != 1)
		error_exit("Invalid player count");
}

void	validate_closed_map(t_map *map)
{
	int	y;
	int	x;
	int	h;
	int	w;

	h = map_height(map->matrix);
	w = map_width(map->matrix);
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (get_map_char(map, y, x) == '0')
			{
				if (get_map_char(map, y - 1, x) == ' '
					|| get_map_char(map, y + 1, x) == ' '
					|| get_map_char(map, y, x - 1) == ' '
					|| get_map_char(map, y, x + 1) == ' ')
					error_exit("Map not closed");
			}
			x++;
		}
		y++;
	}
}

// ========== VALIDATE ==========

static void	validate_config(t_map *map)
{
	if (!map->north_text || !map->south_text
		|| !map->west_text || !map->east_text
		|| !map->floor_color || !map->ceiling_color)
		error_exit("Missing configuration");
}

void	validate_map(t_map *map)
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

