#include "../include/cub3D.h"
#include <math.h>

/* check 4 corner cells around (x,y) with given radius */
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

void	update_movement(t_data *data, int **worldMap)
{
    double oldX = data->game->posX;
    double oldY = data->game->posY;
    double nextX;
    double nextY;
    int map_h = data->game->map_height;
    int map_w = data->game->map_width;
    double speed = data->game->moveSpeed;
    double radius = 0.25; /* collision margin: increase to make collision "wider" */

    if (data->game->key_w)
    {
        nextX = oldX + data->game->dirX * speed;
        nextY = oldY + data->game->dirY * speed;
        if (can_move(nextX, oldY, worldMap, map_h, map_w, radius))
            data->game->posX = nextX;
        if (can_move(oldX, nextY, worldMap, map_h, map_w, radius))
            data->game->posY = nextY;
    }
    if (data->game->key_s)
    {
        nextX = oldX - data->game->dirX * speed;
        nextY = oldY - data->game->dirY * speed;
        if (can_move(nextX, oldY, worldMap, map_h, map_w, radius))
            data->game->posX = nextX;
        if (can_move(oldX, nextY, worldMap, map_h, map_w, radius))
            data->game->posY = nextY;
    }
    if (data->game->key_d)
        rotate_right(data->game);
    if (data->game->key_a)
        rotate_left(data->game);
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
