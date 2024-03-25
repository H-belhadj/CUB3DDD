/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:46:29 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/25 20:57:31 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	if (argc != 2)
	{
		printf("ERROR💩💩💩💩💩💩💩💩");
		return (1);
	}
	parsing(argv[1]);
	// if (argc == 2)
	// {
	// if(parsing(argv[1]))
	// game();
	// }
	// else
	//     printf("error");
	return (0);
}