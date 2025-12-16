#include "../include/cub3D.h"
#include <math.h>

static int	can_move(double x, double y, int **worldMap, int map_h, int map_w, double radius)
{
    double rx[2] = {-radius, radius};
    double ry[2] = {-radius, radius};
    int ix, iy;

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            ix = (int)floor(x + rx[i]);
            iy = (int)floor(y + ry[j]);
            if (ix < 0 || ix >= map_h || iy < 0 || iy >= map_w)
                return 0;
            if (worldMap[ix][iy] != 0)
                return 0;
        }
    }
    return 1;
}

static void move(t_data *data, double old[], int **worldMap, int map_size[], double variables[])
{
    double next[2];

    if (data->game->key_w)
    {
        next[0] = old[0] + data->game->dirX * variables[0];
        next[1] = old[1] + data->game->dirY * variables[0];
        if (can_move(next[0], old[1], worldMap, map_size[0], map_size[1], variables[1]))
            data->game->posX = next[0];
        if (can_move(old[0], next[1], worldMap, map_size[0], map_size[1], variables[1]))
            data->game->posY = next[1];
    }
    if (data->game->key_s)
    {
        next[0] = old[0] - data->game->dirX * variables[0];
        next[1] = old[1] - data->game->dirY * variables[0];
        if (can_move(next[0], old[1], worldMap, map_size[0], map_size[1], variables[1]))
            data->game->posX = next[0];
        if (can_move(old[0], next[1], worldMap, map_size[0], map_size[1], variables[1]))
            data->game->posY = next[1];
    }
    if (data->game->key_d)
        rotate_right(data->game);
    if (data->game->key_a)
        rotate_left(data->game);
}
void	update_movement(t_data *data, int **worldMap)
{
    double old[2];
    int map_size[2];
    double variables[2];
    double radius = 0.25;

    old[0] = data->game->posX;
    old[1] = data->game->posY;
    map_size[0] = data->game->map_height;
    map_size[1] = data->game->map_width;
    variables[0] = data->game->moveSpeed;
    variables[1] = radius;

    move(data, old, worldMap, map_size, variables);

}

int	key_press(int key, t_data *data)
{
    if (key == 65307)
        close_window(data);
    if (key == 119)
        data->game->key_w = 1;
    if (key == 115)
        data->game->key_s = 1;
    if (key == 97)
        data->game->key_a = 1;
    if (key == 100)
        data->game->key_d = 1;
    return (0);
}

int	key_release(int key, t_data *data)
{
    if (key == 119)
        data->game->key_w = 0;
    if (key == 115)
        data->game->key_s = 0;
    if (key == 97)
        data->game->key_a = 0;
    if (key == 100)
        data->game->key_d = 0;
    return (0);
}
