/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:32:44 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 20:55:24 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	raycast_init(t_data *data, t_raycast *ray, int x)
{
	ray->camera_x = 2.0 * (double)x / (double)WIDTH - 1.0;
	ray->ray_dirx = data->game->dir_x + data->game->plane_x * ray->camera_x;
	ray->ray_diry = data->game->dir_y + data->game->plane_y * ray->camera_x;
	ray->map_x = (int)data->game->pos_x;
	ray->map_y = (int)data->game->pos_y;
	if (ray->ray_dirx == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dirx);
	if (ray->ray_diry == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_diry);
	ray->hit = 0;
}

void	raycast_dist(t_data *data, t_raycast *ray)
{
	if (ray->ray_dirx < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (data->game->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->map_x + 1.0 - data->game->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_diry < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (data->game->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->map_y + 1.0 - data->game->pos_y)
			* ray->delta_dist_y;
	}
}

void	dda(t_data *data, t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x >= 0 && ray->map_x < data->game->map_height
			&& ray->map_y >= 0 && ray->map_y < data->game->map_width)
		{
			if (data->game->world_map[ray->map_x][ray->map_y] > 0)
				ray->hit = 1;
		}
		else
		{
			ray->hit = 1;
		}
	}
}

void	wall_calc(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perpwall_dist = (ray->side_distx - ray->delta_dist_x);
	else
		ray->perpwall_dist = (ray->side_disty - ray->delta_dist_y);
	if (ray->perpwall_dist <= 0.0001)
	{
		ray->perpwall_dist = 0.0001;
	}
	ray->line_height = (int)(HEIGHT / ray->perpwall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}
