/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:28:36 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 20:30:56 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <math.h>

int	can_move(t_data *data, double xy[], int **worldMap, double radius)
{
	double	rx[2];
	int		ix;
	int		iy;
	int		i;
	int		j;

	rx[0] = -radius;
	rx[1] = radius;
	i = -1;
	j = -1;
	while (++i < 2)
	{
		while (++j < 2)
		{
			ix = (int)floor(xy[0] + rx[i]);
			iy = (int)floor(xy[1] + rx[j]);
			if (ix < 0 || ix >= data->game->map_height || iy < 0
				|| iy >= data->game->map_width)
				return (0);
			if (worldMap[ix][iy] != 0)
				return (0);
		}
		j = -1;
	}
	return (1);
}

void	move_for(t_data *data, double next[], int **worldMap,
		double variables[])
{
	double	check[2];

	next[0] = data->game->posX + data->game->dirX * variables[0];
	next[1] = data->game->posY + data->game->dirY * variables[0];
	check[0] = next[0];
	check[1] = data->game->posY;
	if (can_move(data, check, worldMap, variables[1]))
		data->game->posX = next[0];
	check[0] = data->game->posX;
	check[1] = next[1];
	if (can_move(data, check, worldMap, variables[1]))
		data->game->posY = next[1];
}

void	move_back(t_data *data, double next[], int **worldMap,
		double variables[])
{
	double	check[2];

	next[0] = data->game->posX - data->game->dirX * variables[0];
	next[1] = data->game->posY - data->game->dirY * variables[0];
	check[0] = next[0];
	check[1] = data->game->posY;
	if (can_move(data, check, worldMap, variables[1]))
		data->game->posX = next[0];
	check[0] = data->game->posX;
	check[1] = next[1];
	if (can_move(data, check, worldMap, variables[1]))
		data->game->posY = next[1];
}

void	move(t_data *data, int **worldMap, double variables[])
{
	double	next[2];

	if (data->game->key_w)
		move_for(data, next, worldMap, variables);
	if (data->game->key_s)
		move_back(data, next, worldMap, variables);
	if (data->game->key_d)
		rotate_right(data->game);
	if (data->game->key_a)
		rotate_left(data->game);
}
