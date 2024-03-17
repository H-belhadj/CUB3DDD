/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:41:23 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/17 17:31:34 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"


typedef struct s_value{
    char    *str;
    int     i;
    int j;
    char *total;
}t_value;

int is_cub(char *str);
char **read_line(char*str);
int check_line(char *str);
int parsing(char *str);


#endif