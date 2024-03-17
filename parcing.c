/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:54:41 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/17 20:45:07 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int ft_strcmp(const char *s1, const char *s2)
// {
//     while (*s1 && (*s1 == *s2))
//     {
//         s1++;
//         s2++;
//     }
//     return *(const unsigned char *)s1 - *(const unsigned char *)s2;
// }


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] && str2[i] && i < n - 1 && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*r;

	i = 0;
	r = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!(r))
		return (NULL);
	while (*s)
	{
		r[i] = *s;
		s++;
		i++;
	}
	r[i] = '\0';
	return (r);
}

int        is_cub(char        *filename)
{
        char        *ext;

        ext = ft_strchr(filename, '.');
        if (ft_strlen(filename) < 5)
                return(printf("invalid name\n"), 0);
        if (ft_strncmp(ext, ".cub", 4) == 0 && ft_strlen(ext) == 4)
        {
            printf("filename is good\n");
            return (1);
        }
        // return (printf("invalid file .cub"), 1);
        return 0;
}



// int        main(int ac, char **av)
// {
//         if (ac != 2)
//         return (printf("need 2 arguments"), -1);

int line_number(char *str)
{
    int fd;
    int line;
    char buffer;
    ssize_t bytes_read;

    fd = open(str, O_RDONLY);
    line = 0;
    if (fd == -1)
     {
        perror("ERROR: opening file\n");       
        return (-1);
    }
    while((bytes_read = read(fd, &buffer, 1)) > 0)
    {
        if(buffer == '\n')
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

char **read_line(char   *str)
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

char **extract_6(char **file)
{
    char    **extract_6;
    char    *cur_char;
    int     is_all_white;
    int     i;
    int     j;
    int     y;
    
    extract_6 = malloc(sizeof(char *) * 6 + 1);
    i = 0;
    j = 0;
    y = 0;
    while(file[i] && y < 6)
    {
        is_all_white = 1;
        cur_char = file[i];
        while(*cur_char != 0)
        {
            if(*cur_char != ' ' && *cur_char != '\t' && *cur_char != '\n')
            {
                is_all_white = 0;
                break;
            }
            cur_char++;
        }
        if (!is_all_white)
        {
            extract_6[j++] = ft_strdup(file[i]);
            y++;
        }
        i++;
    }
    extract_6[j++] = 0;
    return (extract_6);
}


int check_line(char *str)
{
    char **file;
    char **line;

    file = read_line(str);//read the lines of the file and stroed in an array
    line = extract_6(file);

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