/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:07:19 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 20:52:56 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <math.h>

void	update_movement(t_data *data, int **worldMap)
{
	double	variables[2];
	double	radius;

	radius = 0.25;
	variables[0] = data->game->move_speed;
	variables[1] = radius;
	move(data, worldMap, variables);
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
