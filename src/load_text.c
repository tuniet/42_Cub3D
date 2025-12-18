/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:33:17 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 19:49:03 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	load_textures(t_data *data)
{
	t_game		*game;
	t_texture	*paths[4];
	int			i;

	i = -1;
	paths[0] = data->map->north_text;
	paths[1] = data->map->south_text;
	paths[2] = data->map->west_text;
	paths[3] = data->map->east_text;
	game = data->game;
	while (++i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, paths[i]->path,
				&game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].img)
			error_exit("Invalid texture");
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_length,
				&game->textures[i].endian);
		if (!game->textures[i].addr)
			error_exit("Failed to get texture address");
	}
}
