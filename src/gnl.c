/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:33:26 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 19:33:27 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*get_next_line(int fd)
{
	char	c;
	char	*line;
	int		i;
	int		r;

	i = 0;
	line = malloc(10000);
	if (!line)
		return (NULL);
	r = read(fd, &c, 1);
	while (r > 0)
	{
		line[i++] = c;
		if (c == '\n')
			break ;
		r = read(fd, &c, 1);
	}
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}
