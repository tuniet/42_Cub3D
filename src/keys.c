#include "../include/cub3D.h"

int	close_window(t_data *data)
{
	//frees
	(void)data;
	exit(0);
	return (0);
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

    /* Move forward */
    if (data->game->key_w)
    {
        nextX = oldX + data->game->dirX * speed;
        nextY = oldY + data->game->dirY * speed;
        /* check X move */
        if ((int)nextX >= 0 && (int)nextX < map_h && (int)oldY >= 0 && (int)oldY < map_w)
        {
            if (worldMap[(int)nextX][(int)oldY] == 0)
                data->game->posX = nextX;
        }
        /* check Y move */
        if ((int)oldX >= 0 && (int)oldX < map_h && (int)nextY >= 0 && (int)nextY < map_w)
        {
            if (worldMap[(int)oldX][(int)nextY] == 0)
                data->game->posY = nextY;
        }
    }

    /* Move backwards */
    if (data->game->key_s)
    {
        nextX = oldX - data->game->dirX * speed;
        nextY = oldY - data->game->dirY * speed;
        if ((int)nextX >= 0 && (int)nextX < map_h && (int)oldY >= 0 && (int)oldY < map_w)
        {
            if (worldMap[(int)nextX][(int)oldY] == 0)
                data->game->posX = nextX;
        }
        if ((int)oldX >= 0 && (int)oldX < map_h && (int)nextY >= 0 && (int)nextY < map_w)
        {
            if (worldMap[(int)oldX][(int)nextY] == 0)
                data->game->posY = nextY;
        }
    }

    /* Rotation (unchanged) */
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
