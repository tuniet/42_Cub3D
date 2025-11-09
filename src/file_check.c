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
