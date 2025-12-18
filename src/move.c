/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:33:12 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 20:53:07 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	move_forward(int poscheckX, int poscheckY, t_game *game)
{
	if (poscheckX == 0)
		game->pos_x += game->dir_x * game->move_speed;
	if (poscheckY == 0)
		game->pos_y += game->dir_y * game->move_speed;
}

void	move_backwards(int poscheckX, int poscheckY, t_game *game)
{
	if (poscheckX == 0)
		game->pos_x -= game->dir_x * game->move_speed;
	if (poscheckY == 0)
		game->pos_y -= game->dir_y * game->move_speed;
}

void	rotate_right(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->dir_x;
	game->dir_x = game->dir_x * cos(game->rotate_speed * -1) - game->dir_y
		* sin(game->rotate_speed * -1);
	game->dir_y = old_dirx * sin(game->rotate_speed * -1) + game->dir_y
		* cos(game->rotate_speed * -1);
	old_planex = game->plane_x;
	game->plane_x = game->plane_x * cos(game->rotate_speed * -1) - game->plane_y
		* sin(game->rotate_speed * -1);
	game->plane_y = old_planex * sin(game->rotate_speed * -1) + game->plane_y
		* cos(game->rotate_speed * -1);
}

void	rotate_left(t_game *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->dir_x;
	game->dir_x = game->dir_x * cos(game->rotate_speed) - game->dir_y
		* sin(game->rotate_speed);
	game->dir_y = old_dirx * sin(game->rotate_speed) + game->dir_y
		* cos(game->rotate_speed);
	old_planex = game->plane_x;
	game->plane_x = game->plane_x * cos(game->rotate_speed) - game->plane_y
		* sin(game->rotate_speed);
	game->plane_y = old_planex * sin(game->rotate_speed) + game->plane_y
		* cos(game->rotate_speed);
}
