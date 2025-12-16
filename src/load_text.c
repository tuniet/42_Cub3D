#include "../include/cub3D.h"

void load_textures(t_data *data)
{
  t_game *game;
  t_texture *paths[4] = {
    data->map->north_text,
    data->map->south_text,
    data->map->west_text,
    data->map->east_text
  };

  game = data->game;
  for (int i = 0; i < 4; i++)
  {
    game->textures[i].img = mlx_xpm_file_to_image(
      game->mlx, paths[i]->path,
      &game->textures[i].width,
      &game->textures[i].height
    );
    if (!game->textures[i].img)
      error_exit("Invalid texture");

    game->textures[i].addr = mlx_get_data_addr(
      game->textures[i].img,
      &game->textures[i].bpp,
      &game->textures[i].line_length,
      &game->textures[i].endian
    );
    if (!game->textures[i].addr)
      error_exit("Failed to get texture address");
  }
}
