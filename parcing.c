/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:54:41 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/20 20:44:07 by hbelhadj         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*results;

	if (s == NULL)
		return (ft_strdup("\0"));
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	if (len >= ft_strlen(s) - start)
		results = (char *)malloc(sizeof(char) * ft_strlen(s) - start + 1);
	else
		results = (char *)malloc(sizeof(char) * (len + 1));
	if (!results)
		return (NULL);
	s = s + start;
	while (s[i] && i < len)
	{
		results[i] = s[i];
		i++;
	}
	*(results + i) = '\0';
	return (results);
}

void    *free_(char **file)
{
    int i;

    i = -1;
    while (file[++i])
        free(file[i]);
    free (file);
    return (NULL);
}


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

char *rest_(char *line, char *str)
{
    int i;//used as an index to traverse the input line.
    char *rest;//store the extracted rest of the line and the first part of the line, respectively.
    char *store;//store the extracted rest of the line and the first part of the line, respectively.
    char *start;
    
    i = 0;
    if(!line)
        return (NULL);
    //This while loop iterates through the input line until it finds a non-space or non-tab character.
    while(line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    store = strdup(line + 1);//This line uses the strdup function to create a duplicate of the part of the line after skipping leading spaces or tabs. It starts copying from the position indicated by line + i, which is the first non-space or non-tab character
    if(!store)
        return (NULL);
    if (strncmp(store, str, ft_strlen(str)) != 0)
    {
        free(store);
        return (NULL);
    }
    start = strchr(store, ' ');
    if (!start)
        start = strchr(store, '\t');
    if (!start)
    {
        free(store);
        return (NULL);
    }
    rest = strdup(start);
    free(store);
    return (rest);
}

char *find_(char **line, char *target)
{
    int i;
    char *cur_line;
    char *line_ptr;
    char *target_ptr;
    
    if(line == NULL || target == NULL)
        return (NULL);
    
    i = 0;
    while(line[i])
    {
        cur_line = line[i];
        while(*cur_line)
        {
            if (*cur_line == *target)
            {
                line_ptr = cur_line;
                target_ptr = target;
                while (*target_ptr && *line_ptr == *target_ptr)
                {
                    line_ptr++;
                    target_ptr++;
                }
                if(*target_ptr == '\0')
                    return (line[i]);
            }
            cur_line++;
        }  
        i++;
    }
    return (NULL);
}
char *str_(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if(!str)
        return (NULL);
    while(str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    j = i;
    while(str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        i++;
    if(i == j)
        return (NULL);
    return (ft_substr(str, j, i - j));
}
// Define the paths function
int paths(char **line)
{
    t_paths *paths_struct;
    // Extract path associated with "NO"
    char *tmp = rest_(find_(line, "NO"), "NO");
    if (!tmp)
        return 0;
    free(tmp);
    paths_struct->path_no.string_value = str_(rest_(find_(line, "NO"), "NO"));

    // Extract path associated with "SO"
    tmp = rest_(find_(line, "SO"), "SO");
    if (!tmp)
        return (free(paths_struct->path_no.string_value), 0);
    free(tmp);
    paths_struct->path_so.string_value = str_(rest_(find_(line, "SO"), "SO"));

    // Extract path associated with "WE"
    tmp = rest_(find_(line, "WE"), "WE");
    if (!tmp)
        return (free(paths_struct->path_no.string_value), free(paths_struct->path_so.string_value), 0);
    free(tmp);
    paths_struct->path_we.string_value = str_(rest_(find_(line, "WE"), "WE"));

    // Extract path associated with "EA"
    tmp = rest_(find_(line, "EA"), "EA");
    if (!tmp)
        return (free(paths_struct->path_no.string_value), free(paths_struct->path_so.string_value),
                free(paths_struct->path_we.string_value), 0);
    free(tmp);
    paths_struct->path_ea.string_value = str_(rest_(find_(line, "EA"), "EA"));
    return 1;
}

int check_line(char *str)
{
    char **file;
    char **line;

    file = read_line(str);//read the lines of the file and stroed in an array
    line = extract_6(file);
    free_(file);
    if(!paths(line))
        return (free_(line), 0);
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