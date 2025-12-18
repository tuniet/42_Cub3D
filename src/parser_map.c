/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:33:06 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 19:33:06 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	is_valid_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

char	get_map_char(t_map *map, int y, int x)
{
	if (y < 0 || x < 0 || !map->matrix[y]
		|| x >= (int)ft_strlen(map->matrix[y]))
		return (' ');
	return (map->matrix[y][x]);
}

void	validate_map_chars(t_map *map)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (map->matrix[y])
	{
		x = 0;
		while (map->matrix[y][x])
		{
			if (!is_valid_map_char(map->matrix[y][x]))
				error_exit("Invalid map character");
			if (ft_strchr("NSEW", map->matrix[y][x]))
				player++;
			x++;
		}
		y++;
	}
	if (player != 1)
		error_exit("Invalid player count");
}

void	validate_closed_map(t_map *map)
{
	int	y;
	int	x;
	int	h;
	int	w;

	h = map_height(map->matrix);
	w = map_width(map->matrix);
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (get_map_char(map, y, x) == '0')
			{
				if (get_map_char(map, y - 1, x) == ' ' || get_map_char(map, y
						+ 1, x) == ' ' || get_map_char(map, y, x - 1) == ' '
					|| get_map_char(map, y, x + 1) == ' ')
					error_exit("Map not closed");
			}
			x++;
		}
		y++;
	}
}
