/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack-colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:40:40 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/28 22:41:40 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ex_color(char **line)
{
    char *tmp;
    
    tmp = rest_(find_(line, "F"), "F");
    if(!tmp)
        return (FALSE);
    free(tmp);
    paths_struct.pars.F_color = str_(rest_(find_(line, "F"), "F"));
    tmp = rest_(find_(line, "C"), "C");
    
    if(!tmp)
        return (free(paths_struct.pars.F_color), FALSE);
    free(tmp);
    paths_struct.pars.C_color = str_(rest_(find_(line, "C"), "C"));
    return (TRUE);
}