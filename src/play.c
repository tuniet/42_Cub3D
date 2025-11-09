#include "../include/cub3D.h"

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static void	init_game(t_data *data)
{
    data->game->mlx = mlx_init();
    if (!data->game->mlx)
        return (perror("mlx"), exit(1));
    data->game->win = mlx_new_window(data->game->mlx, WIDTH, HEIGHT,
            "Cub3d");
    if (!data->game->win)
        return (perror("mlx"), exit(1));
    data->game->map_height = 24;
    data->game->map_width = 24;
    data->game->dirX = -1;
    data->game->dirY = 0;
    data->game->posX = 10;
    data->game->posY = 5;
    data->game->planeX = 0;
    data->game->planeY = 0.66;

    data->game->time = 0;
    data->game->oldTime = 0;

    data->game->c_hex = 0x87CEEB;
    data->game->f_hex = 0x228B22;

    data->game->img.img = mlx_new_image(data->game->mlx, WIDTH, HEIGHT);
    data->game->img.addr = mlx_get_data_addr(data->game->img.img,
        &data->game->img.bpp, &data->game->img.line_length, &data->game->img.endian);

    data->game->world_map = malloc(sizeof(int *) * data->game->map_height);
    if (!data->game->world_map)
        return (perror("malloc"), exit(1));
    for (int i = 0; i < data->game->map_height; i++)
    {
        data->game->world_map[i] = malloc(sizeof(int) * data->game->map_width);
        if (!data->game->world_map[i])
            return (perror("malloc"), exit(1));
        for (int j = 0; j < data->game->map_width; j++)
            data->game->world_map[i][j] = worldMap[i][j];
    }
}

static void	clear_image(t_data *data)
{
    int	size;
    char *p;

    if (!data->game->img.addr)
        return ;
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
    data->game->moveSpeed =  0.03;
    data->game->rotateSpeed =  0.01;

	mlx_hook(data->game->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->game->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->game->win, 17, 0, close_window, data);
	mlx_loop_hook(data->game->mlx, render, data);
	mlx_loop(data->game->mlx);

}
