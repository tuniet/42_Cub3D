/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:32:52 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 20:53:07 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	clear_image(t_data *data)
{
	int		size;
	char	*p;
	int		i;

	i = 0;
	if (!data->game->img.addr)
		return ;
	size = data->game->img.line_length * HEIGHT;
	p = data->game->img.addr;
	while (i++ < size)
		p[i] = 0;
}

int	render(t_data *data)
{
	clear_image(data);
	update_movement(data, data->game->world_map);
	draw_view(data);
	mlx_put_image_to_window(data->game->mlx, data->game->win,
		data->game->img.img, 0, 0);
	return (0);
}

void	mainloop(t_data *data)
{
	init_game(data);
	load_textures(data);
	data->game->move_speed = 0.1;
	data->game->rotate_speed = 0.05;
	mlx_hook(data->game->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->game->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->game->win, 17, 0, close_window, data);
	mlx_loop_hook(data->game->mlx, render, data);
	mlx_loop(data->game->mlx);
}
