/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:54:41 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/17 16:43:46 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int is_cub(char *str)
{
    if (strcmp(str + (strlen(str) - strlen(".cub")), ".cub") || open(str, O_RDWR) < 0)
        return (printf("Error: file_error\n"), 0);
    return (1)
}

int parsing(char *str)
{
    if(!is_cub(str))
    {
        printf("check '.cub' \n");
        return (0);
    }
}