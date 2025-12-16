#include "../include/cub3D.h"

static void free_all(t_data *data)
{
	int i;

	if (data->game)
	{
		if (data->game->world_map)
		{
			for (i = 0; i < data->game->map_height; i++)
			{
				free(data->game->world_map[i]);
			}
			free(data->game->world_map);
		}
		mlx_destroy_image(data->game->mlx, data->game->img.img);
		mlx_destroy_image(data->game->mlx, data->game->textures[0].img);
		mlx_destroy_image(data->game->mlx, data->game->textures[1].img);
		mlx_destroy_image(data->game->mlx, data->game->textures[2].img);
		mlx_destroy_image(data->game->mlx, data->game->textures[3].img);
		mlx_destroy_display(data->game->mlx);
		free(data->game);
	}

	if (data->map)
	{
		free(data->map->north_text->path);
		free(data->map->north_text);
		free(data->map->south_text->path);
		free(data->map->south_text);
		free(data->map->west_text->path);
		free(data->map->west_text);
		free(data->map->east_text->path);
		free(data->map->east_text);
		free(data->map->floor_color);
		free(data->map->ceiling_color);
		free_split(data->map->matrix);
		free(data->map);
	}

	free(data);

}
int	close_window(t_data *data)
{
    free_all(data);
    exit(0);
    return (0);
}
