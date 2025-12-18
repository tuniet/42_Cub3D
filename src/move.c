/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:33:12 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 19:34:47 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	move_forward(int poscheckX, int poscheckY, t_game *game)
{
	if (poscheckX == 0)
		game->posX += game->dirX * game->moveSpeed;
	if (poscheckY == 0)
		game->posY += game->dirY * game->moveSpeed;
}

void	move_backwards(int poscheckX, int poscheckY, t_game *game)
{
	if (poscheckX == 0)
		game->posX -= game->dirX * game->moveSpeed;
	if (poscheckY == 0)
		game->posY -= game->dirY * game->moveSpeed;
}

void	rotate_right(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->dirX;
	game->dirX = game->dirX * cos(game->rotateSpeed * -1) - game->dirY
		* sin(game->rotateSpeed * -1);
	game->dirY = old_dirx * sin(game->rotateSpeed * -1) + game->dirY
		* cos(game->rotateSpeed * -1);
	old_planex = game->planeX;
	game->planeX = game->planeX * cos(game->rotateSpeed * -1) - game->planeY
		* sin(game->rotateSpeed * -1);
	game->planeY = old_planex * sin(game->rotateSpeed * -1) + game->planeY
		* cos(game->rotateSpeed * -1);
}

void	rotate_left(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->dirX;
	game->dirX = game->dirX * cos(game->rotateSpeed) - game->dirY
		* sin(game->rotateSpeed);
	game->dirY = old_dirx * sin(game->rotateSpeed) + game->dirY
		* cos(game->rotateSpeed);
	old_planex = game->planeX;
	game->planeX = game->planeX * cos(game->rotateSpeed) - game->planeY
		* sin(game->rotateSpeed);
	game->planeY = old_planex * sin(game->rotateSpeed) + game->planeY
		* cos(game->rotateSpeed);
}
