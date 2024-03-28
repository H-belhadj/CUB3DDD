/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:15:40 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/28 22:19:53 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (FALSE);
	while (str1[i] && str2[i] && i < n - 1 && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	is_cub(char *filename)
{
	char    *ext;

	ext = ft_strchr(filename, '.');
	if (ft_strlen(filename) < 5)
		return (printf("invalid name\n"), FALSE);
	if (ft_strncmp(ext, ".cub", 4) == 0 && ft_strlen(ext) == 4)
		return (printf("TEST 1: good💪\n"), TRUE);
	return (FALSE);
}