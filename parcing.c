/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:54:41 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/17 18:07:20 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int is_cub(char *str)
{
    if (ft_strcmp(str + (ft_strlen(str) - ft_strlen(".cub")), ".cub")
		|| open(str, O_RDWR) < 0)
	{
		printf("Error\nfile_err\n");
		return (0);
	}
    printf("Map Is Good 😇\n");
	return (1);
}

int line_number(char *str)
{
    int fd;
    int line;
    char buffer;
    ssize_t bytes_read;

    fd = open(str, O_RDONLY);
    line = 0;
    if (fd == -1)
        return (perror("ERROR: opening file\n", -1));
    while((bytes_read = read(fd, &buffer, 1)) > 0)
    {
        if(buffer == '\n');
            line++;
    }
    if(bytes_read == -1)
    {
        perror("ERROR: reading file\n");
        close(fd);
        return (-1);
    }
    close(fd);
    return (line);
}

char **read_line(char*str)
{
    int     i;
    int     fd;
    char    *store_first_line;
    char    **store_all_map;
    
    i = 0;
    fd = open(str, O_RDWR);
    store_first_line = get_next_line(fd);
    store_all_map = malloc(sizeof(char *) * line_number(str) + 1);
    while(store_first_line != 0)
    {
        store_all_map[i] = strdup(store_first_line);
        free(store_first_line);
        store_first_line = get_next_line(fd);
        i++;
    }
    free(store_first_line);
    close(fd);
    store_all_map[i] = 0;
    return (store_all_map);
}


int check_line(char *str)
{
    char **file;
    // char **line;

    file = read_line(str);

    return 1;
}

int parsing(char *str)
{
    // (void)str;
    if (!is_cub(str))
        return (printf("check '.cub'\n"), 0);
    if (!check_line(str))
        return (printf("check file\n"), 0);
    return 1;
}