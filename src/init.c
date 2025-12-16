#include "../include/cub3D.h"

static void set_dir(t_data *data, double dirX, double dirY, double planeX, double planeY)
{
	data->game->dirX = dirX;
	data->game->dirY = dirY;
	data->game->planeX = planeX;
	data->game->planeY = planeY;
}

static void set_start_pos(t_data *data, char c, int x, int y)
{
	if (ft_strchr("NSEW", c))
	{
		data->game->posX = x + 0.5;
		data->game->posY = y + 0.5;
		if (c == 'N')
		{
			set_dir(data, -1, 0, 0, 0.66);
		}
		else if (c == 'S')
		{
			set_dir(data, 1, 0, 0, -0.66);
		}
		else if (c == 'E')
		{
			set_dir(data, 0, 1, 0.66, 0);
		}
		else if (c == 'W')
		{
			set_dir(data, 0, -1, -0.66, 0);
		}
	}
}

static void init_map(t_data *data)
{
	int x, y;
	char c;

	y = 0;
	while (y < data->game->map_height)
	{
		data->game->world_map[y] =
			malloc(sizeof(int) * data->game->map_width);
		if (!data->game->world_map[y])
			return (perror("malloc"), exit(1));
		x = 0;
		while (x < data->game->map_width)
		{
			c = get_map_char(data->map, y, x);

			if (c == '1')
				data->game->world_map[y][x] = 1;
			else
				data->game->world_map[y][x] = 0;
			set_start_pos(data, c, x, y);
			x++;
		}
		y++;
	}
}

//data->game->dirX = -1;
	//data->game->dirY = 0;
	//data->game->posX = 10;
	//data->game->posY = 5;
	//data->game->planeX = 0;
	//data->game->planeY = 0.66;

void init_game(t_data *data)
{
	data->game->mlx = mlx_init();
	if (!data->game->mlx)
		return (perror("mlx"), exit(1));
	data->game->win = mlx_new_window(data->game->mlx, WIDTH, HEIGHT,
									 "Cub3d");
	if (!data->game->win)
		return (perror("mlx"), exit(1));
	data->game->map_height = map_height(data->map->matrix);
	data->game->map_width = map_width(data->map->matrix);
	data->game->time = 0;
	data->game->oldTime = 0;
	data->game->f_hex = (data->map->floor_color->red << 16) | (data->map->floor_color->green << 8) | data->map->floor_color->blue;
	data->game->c_hex = (data->map->ceiling_color->red << 16) | (data->map->ceiling_color->green << 8) | data->map->ceiling_color->blue;

	data->game->img.img = mlx_new_image(data->game->mlx, WIDTH, HEIGHT);
	data->game->img.addr = mlx_get_data_addr(data->game->img.img,
											 &data->game->img.bpp, &data->game->img.line_length, &data->game->img.endian);
	data->game->world_map = malloc(sizeof(int *) * data->game->map_height);
	if (!data->game->world_map)
		return (perror("malloc"), exit(1));
	init_map(data);
	data->game->time = 0;
	data->game->oldTime = 0;
}
