/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:32:47 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 20:52:01 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	sel_texture(t_data *data, t_img *texture, t_raycast ray)
{
	if (ray.side == 1)
	{
		if (ray.ray_diry < 0)
			*texture = data->game->textures[0];
		else
			*texture = data->game->textures[2];
	}
	else
	{
		if (ray.ray_dirx < 0)
			*texture = data->game->textures[3];
		else
			*texture = data->game->textures[1];
	}
}

static void	texture_calc(t_data *data, t_raycast *ray, t_img *texture)
{
	if (ray->side == 0)
		ray->wall_x = data->game->pos_y + ray->perpwall_dist * ray->ray_diry;
	else
		ray->wall_x = data->game->pos_x + ray->perpwall_dist * ray->ray_dirx;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)(texture->width));
	if ((ray->side == 0 && ray->ray_dirx > 0) || (ray->side == 1
			&& ray->ray_diry < 0))
		ray->tex_x = texture->width - ray->tex_x - 1;
}

static void	draw_wall_column(t_data *data, t_raycast *ray, t_img *texture,
		int x)
{
	ray->y = ray->draw_start;
	while (ray->y < ray->draw_end)
	{
		ray->d = ray->y * 256 - HEIGHT * 128 + ray->line_height * 128;
		ray->tex_y = ((ray->d * texture->height) / ray->line_height) / 256;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		else if (ray->tex_y >= texture->height)
			ray->tex_y = texture->height - 1;
		ray->color = *(unsigned int *)(texture->addr + (ray->tex_y
					* texture->line_length + ray->tex_x * (texture->bpp / 8)));
		put_pixel_walls(&data->game->img, x, ray);
		ray->y++;
	}
}

static void	draw_ceiling_and_floor(t_raycast *ray, t_data *data, int x)
{
	ray->y = 0;
	while (ray->y < ray->draw_start)
	{
		put_pixel_ceiling(data, x, ray->y);
		ray->y++;
	}
	ray->y = ray->draw_end;
	while (ray->y < HEIGHT)
	{
		put_pixel_floor(data, x, ray->y);
		ray->y++;
	}
}

void	draw_view(t_data *data)
{
	t_raycast	ray;
	t_img		texture;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		raycast_init(data, &ray, x);
		raycast_dist(data, &ray);
		dda(data, &ray);
		wall_calc(&ray);
		sel_texture(data, &texture, ray);
		texture_calc(data, &ray, &texture);
		draw_wall_column(data, &ray, &texture, x);
		draw_ceiling_and_floor(&ray, data, x);
		x++;
	}
}
