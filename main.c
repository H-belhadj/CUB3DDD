/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:46:29 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/27 20:19:28 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	if (argc != 2)
	{
		printf("ERROR💩💩");
		return (TRUE);
	}
	parsing(argv[1]);
	return (FALSE);
}