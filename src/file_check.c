#include "../include/cub3D.h"

int	valid_extension(char *av[])
{
	int	i;

	i = ft_strlen(av[1]);
	if (ft_strncmp(&av[1][i - 4], ".cub", 4))
		return (1);
	return (0);
}

int map_exists(char *av[], t_data *data)
{
    data->map_fd = open(av[1], O_RDONLY);
    if (data->map_fd < 0)
        return (perror("open"), exit(0), 0);
    return 1;
}

int	has_png_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strcmp(path + len - 4, ".png") == 0);
}

int	has_xpm_extension(char *path)
{
	int	len;

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


