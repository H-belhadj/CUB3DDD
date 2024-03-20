/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:41:23 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/20 17:43:39 by hbelhadj         ###   ########.fr       */
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
    int int_value;
    double double_value;
    char *sting_value;
}t_value;

// Define a struct to hold paths
typedef struct s_paths {
    t_value path_no;
    t_value path_so;
    t_value path_we;
    t_value path_ea;
} t_paths;

typedef struct s_pars{
    char *path_no;
    char *path_we;
    char *path_ea;
    char *colorf;
    char *colorc;
    char **f;
    char **c;
    char **map;
    char pos;
    int x;
    int y;
}t_pars;


int is_cub(char *str);
char **read_line(char*str);
int check_line(char *str);
int parsing(char *str);


#endif