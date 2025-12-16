#include "../include/cub3D.h"

static void clear_image(t_data *data)
{
	int size;
	char *p;

	if (!data->game->img.addr)
		return;
	size = data->game->img.line_length * HEIGHT;
	p = data->game->img.addr;
	for (int i = 0; i < size; ++i)
		p[i] = 0;
}

int render(t_data *data)
{
	clear_image(data);
	update_movement(data, data->game->world_map);
	draw_view(data);
	mlx_put_image_to_window(data->game->mlx, data->game->win,
							data->game->img.img, 0, 0);
	return 0;
}

void mainloop(t_data *data)
{
	init_game(data);
	load_textures(data);
	data->game->moveSpeed = 0.03;
	data->game->rotateSpeed = 0.01;

	mlx_hook(data->game->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->game->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->game->win, 17, 0, close_window, data);
	mlx_loop_hook(data->game->mlx, render, data);
	mlx_loop(data->game->mlx);
}
