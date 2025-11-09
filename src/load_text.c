#include "../include/cub3D.h"

static void	north(t_data *data)
{
	t_game	*game;

	game = data->game;
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, "./textures/north.xpm",
			&game->textures[0].width, &game->textures[0].height);
	if (!game->textures[0].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bpp, &game->textures[0].line_length,
			&game->textures[0].endian);
	if (game->textures[0].addr == NULL)
		exit(1);
}

static void	south(t_data *data)
{
	t_game	*game;

	game = data->game;
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx, "./textures/east.xpm",
			&game->textures[1].width, &game->textures[1].height);
	if (!game->textures[1].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bpp, &game->textures[1].line_length,
			&game->textures[1].endian);
	if (game->textures[1].addr == NULL)
		exit(1);
}

static void	east(t_data *data)
{
	t_game	*game;

	game = data->game;
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx, "./textures/south.xpm",
			&game->textures[2].width, &game->textures[2].height);
	if (!game->textures[2].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bpp, &game->textures[2].line_length,
			&game->textures[2].endian);
	if (game->textures[2].addr == NULL)
		exit(1);
}

static void	west(t_data *data)
{
	t_game	*game;

	game = data->game;
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx, "./textures/west.xpm",
			&game->textures[3].width, &game->textures[3].height);
	if (!game->textures[3].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bpp, &game->textures[3].line_length,
			&game->textures[3].endian);
	if (game->textures[3].addr == NULL)
		exit(1);
}
int	load_textures(t_data *data)
{
	north(data);
	south(data);
	east(data);
	west(data);
	return (1);
}
