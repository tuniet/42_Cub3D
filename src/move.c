#include "../include/cub3D.h"

void move_forward(int poscheckX, int poscheckY, t_game *game)
{
	if(poscheckX == 0)
        game->posX += game->dirX * game->moveSpeed;
    if(poscheckY == 0)
        game->posY += game->dirY * game->moveSpeed;
}

void move_backwards(int poscheckX, int poscheckY, t_game *game)
{
	if(poscheckX == 0) game->posX -= game->dirX * game->moveSpeed;
    if(poscheckY == 0) game->posY -= game->dirY * game->moveSpeed;
}

void rotate_right(t_game *game)
{
	double oldDirX = game->dirX;
    game->dirX = game->dirX * cos(game->rotateSpeed * - 1) - game->dirY * sin(game->rotateSpeed * - 1);
    game->dirY = oldDirX * sin(game->rotateSpeed * - 1) + game->dirY * cos(game->rotateSpeed * - 1);
    double oldPlaneX = game->planeX;
    game->planeX = game->planeX * cos(game->rotateSpeed * - 1) - game->planeY * sin(game->rotateSpeed * - 1);
    game->planeY = oldPlaneX * sin(game->rotateSpeed * - 1) + game->planeY * cos(game->rotateSpeed * - 1);
}

void rotate_left(t_game *game)
{
	double oldDirX = game->dirX;
    game->dirX = game->dirX * cos(game->rotateSpeed) - game->dirY * sin(game->rotateSpeed);
    game->dirY = oldDirX * sin(game->rotateSpeed) + game->dirY * cos(game->rotateSpeed);
    double oldPlaneX = game->planeX;
    game->planeX = game->planeX * cos(game->rotateSpeed) - game->planeY * sin(game->rotateSpeed);
    game->planeY = oldPlaneX * sin(game->rotateSpeed) + game->planeY * cos(game->rotateSpeed);
}
