/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:05:34 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 20:46:08 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

	i = -1;
	len = 0;
	if (s == NULL)
	{
		return (NULL);
	}
	while (len < n && s[len] != '\0')
	{
		len++;
	}
	dup = malloc(len + 1);
	if (dup == NULL)
	{
		return (NULL);
	}
	while (++i < len)
	{
		dup[i] = s[i];
	}
	dup[len] = '\0';
	return (dup);
}
