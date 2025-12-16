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
  int x,y;
  char c;

    data->game->mlx = mlx_init();
    if (!data->game->mlx)
        return (perror("mlx"), exit(1));
    data->game->win = mlx_new_window(data->game->mlx, WIDTH, HEIGHT,
            "Cub3d");
    if (!data->game->win)
        return (perror("mlx"), exit(1));
    //data->game->map_height = 24;
    //data->game->map_width = 24;
    data->game->map_height = map_height(data->map->matrix);
    data->game->map_width = map_width(data->map->matrix);
    data->game->dirX = -1;
    data->game->dirY = 0;
    data->game->posX = 10;
    data->game->posY = 5;
    data->game->planeX = 0;
    data->game->planeY = 0.66;

    data->game->time = 0;
    data->game->oldTime = 0;

  data->game->f_hex = (data->map->floor_color->red << 16)
    | (data->map->floor_color->green << 8)
    | data->map->floor_color->blue;

  data->game->c_hex = (data->map->ceiling_color->red << 16)
    | (data->map->ceiling_color->green << 8)
    | data->map->ceiling_color->blue;
/*
    data->game->c_hex = 0x87CEEB;
    data->game->f_hex = 0x228B22;
*/

    data->game->img.img = mlx_new_image(data->game->mlx, WIDTH, HEIGHT);
    data->game->img.addr = mlx_get_data_addr(data->game->img.img,
        &data->game->img.bpp, &data->game->img.line_length, &data->game->img.endian);

    data->game->world_map = malloc(sizeof(int *) * data->game->map_height);
    if (!data->game->world_map)
        return (perror("malloc"), exit(1));

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

      /* ===== Player start ===== */
      if (ft_strchr("NSEW", c))
      {
        data->game->posX = x + 0.5;
        data->game->posY = y + 0.5;

        if (c == 'N')
        {
          data->game->dirX = -1;
          data->game->dirY = 0;
          data->game->planeX = 0;
          data->game->planeY = 0.66;
        }
        else if (c == 'S')
        {
          data->game->dirX = 1;
          data->game->dirY = 0;
          data->game->planeX = 0;
          data->game->planeY = -0.66;
        }
        else if (c == 'E')
        {
          data->game->dirX = 0;
          data->game->dirY = 1;
          data->game->planeX = 0.66;
          data->game->planeY = 0;
        }
        else if (c == 'W')
        {
          data->game->dirX = 0;
          data->game->dirY = -1;
          data->game->planeX = -0.66;
          data->game->planeY = 0;
        }
      }
      x++;
    }
    y++;
  }

  data->game->time = 0;
  data->game->oldTime = 0;


// FIXED MAP
/* 
    for (int i = 0; i < data->game->map_height; i++)
    {
        data->game->world_map[i] = malloc(sizeof(int) * data->game->map_width);
        if (!data->game->world_map[i])
            return (perror("malloc"), exit(1));
        for (int j = 0; j < data->game->map_width; j++)
            data->game->world_map[i][j] = worldMap[i][j];
    }
*/ 
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
