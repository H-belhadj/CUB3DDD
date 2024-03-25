/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:41:23 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/25 20:26:49 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include "get_next_line.h"


enum e_textures {
    NO,
    SO,
    WE,
    EA,
};


// Define a struct to hold paths
typedef struct s_paths {
    char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
    char    *textures[4];
    char    *ex_color;
    char    *C_color;
    char    *F_color;
    char    **f;
    char    **c;
    char    **map;
    long    player_row;
    long    player_col;
} t_paths;

typedef struct s_value{
    t_paths pars;
}           t_value;
t_value     paths_struct;



#define TRUE 1
#define FALSE 0


int is_cub(char *str);
char **read_line(char*str);
int check_line(char *str);
int parsing(char *str);
int accessible();


#endif