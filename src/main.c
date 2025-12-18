/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:33:15 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 19:33:15 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	has_cub_extension(char *file)
{
	int	len;

	if (!file)
		return (0);
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	if (ft_strcmp(file + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

void	initdata(t_data **data)
{
	*data = ft_calloc(1, sizeof(t_data));
	(*data)->map = ft_calloc(1, sizeof(t_map));
	(*data)->game = ft_calloc(1, sizeof(t_game));
	(*data)->map_fd = 0;
}

void	early_free(t_data *data)
{
	if (data->game)
		free(data->game);
	if (data->map)
		free(data->map);
	if (data)
		free(data);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	if (ac != 2 || av[1][0] == '\0')
		return (printf("Error\nUsage: ./cub3D [.cub map]\n"), 1);
	if (!has_cub_extension(av[1]))
		return (printf("Error\nInvalid file extension\n"), 1);
	initdata(&data);
	data->map_fd = open(av[1], O_RDONLY);
	if (data->map_fd < 0)
		return (early_free(data), perror("open"), 1);
	parse_cub_file(data);
	mainloop(data);
	return (0);
}
