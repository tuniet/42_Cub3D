/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:32:44 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 19:32:45 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	raycast_init(t_data *data, t_raycast *ray, int x)
{
	ray->cameraX = 2.0 * (double)x / (double)WIDTH - 1.0;
	ray->rayDirX = data->game->dirX + data->game->planeX * ray->cameraX;
	ray->rayDirY = data->game->dirY + data->game->planeY * ray->cameraX;
	ray->mapX = (int)data->game->posX;
	ray->mapY = (int)data->game->posY;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
}

void	raycast_dist(t_data *data, t_raycast *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->game->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - data->game->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (data->game->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - data->game->posY) * ray->deltaDistY;
	}
}

void	dda(t_data *data, t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->mapX >= 0 && ray->mapX < data->game->map_height
			&& ray->mapY >= 0 && ray->mapY < data->game->map_width)
		{
			if (data->game->world_map[ray->mapX][ray->mapY] > 0)
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
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	if (ray->perpWallDist <= 0.0001)
	{
		ray->perpWallDist = 0.0001;
	}
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}
