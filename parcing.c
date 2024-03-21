/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:54:41 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/21 22:55:45 by hbelhadj         ###   ########.fr       */
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

#define TRUE 1
#define FALSE 0

char	*ft_strdup(char *s)
{
	int		i;
	char	*r;

	i = 0;
	if (!s)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!r)
		return (NULL);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*results;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len >= ft_strlen(s) - start)
		results = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		results = (char *)malloc(sizeof(char) * (len + 1));
	if (!results)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		results[i] = s[start + i];
		i++;
	}
	results[i] = '\0';
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


int	ft_strncmp( char *s1,  char *s2, size_t n)
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



int        is_cub(char        *filename)
{
        char        *ext;

        ext = ft_strchr(filename, '.');
        if (ft_strlen(filename) < 5)
                return(printf("invalid name\n"), 0);
        if (ft_strncmp(ext, ".cub", 4) == 0 && ft_strlen(ext) == 4)
        {
            printf("TEST 1: good💪🏻\n");
            return (1);
        }
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
    // printf("line_number : %d\n", line_number(str));
    store_first_line = get_next_line(fd);
    store_all_map = malloc(sizeof(char *) * line_number(str) + 1);
    while(store_first_line != 0)
    {
        store_all_map[i] = ft_strdup(store_first_line);
        // printf("=======> %s\n", store_all_map[i]);
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
            // printf("<====== %s =====>\n", extract_6[j++]);
            // printf("<====== %d =====>\n", j++);
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

    (void)str;
    
    i = 0;
    if(!line)
    {
        return (NULL);
    }
    //This while loop iterates through the input line until it finds a non-space or non-tab character.
    while(line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    store = strdup(line + 1);//This line uses the strdup function to create a duplicate of the part of the line after skipping leading spaces or tabs. It starts copying from the position indicated by line + i, which is the first non-space or non-tab character
    if(!store)
    {
        return (NULL);
    }
    // if (ft_strncmp(store, str, ft_strlen(str)) != 0)
    // {
    //     printf("*********42\n");
    //     printf("store : %s\n", store);
    //     printf("str : %s\n", str);
    //     free(store);
    //     return (NULL);
    // }
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
    paths_struct.pars.path_ea = NULL;
    paths_struct.pars.path_no = NULL;
    paths_struct.pars.path_we = NULL;
    paths_struct.pars.path_so = NULL;

    // Extract path associated with "NO"
    char *tmp = rest_(find_(line, "NO"), "NO");
    if (!tmp)
    {
        // printf("ERROR 1337\n");
        return FALSE;
    }
    free(tmp);
    paths_struct.pars.path_no = str_(rest_(find_(line, "NO"), "NO"));
    // printf("%s------>\n", paths_struct.pars.path_no);

    // Extract path associated with "SO"
    tmp = rest_(find_(line, "SO"), "SO");
    if (!tmp)
        return (free(paths_struct.pars.path_no), FALSE);
    free(tmp);
    paths_struct.pars.path_so = str_(rest_(find_(line, "SO"), "SO"));
    // printf("%s------>\n", paths_struct.pars.path_so);

    // Extract path associated with "WE"
    tmp = rest_(find_(line, "WE"), "WE");
    if (!tmp)
        return (free(paths_struct.pars.path_no), free(paths_struct.pars.path_so), FALSE);
    free(tmp);
    paths_struct.pars.path_we = str_(rest_(find_(line, "WE"), "WE"));
    // printf("%s------>\n", paths_struct.pars.path_we);

    // Extract path associated with "EA"
    tmp = rest_(find_(line, "EA"), "EA");
    if (!tmp)
        return (free(paths_struct.pars.path_no), free(paths_struct.pars.path_so),
                free(paths_struct.pars.path_we), FALSE);
    free(tmp);
    // printf("%s------>\n", paths_struct.pars.path_ea);
    paths_struct.pars.path_ea = str_(rest_(find_(line, "EA"), "EA"));
    return TRUE;
}
int ex_color(char **line)
{
    char *tmp;

    tmp = rest_(find_(line, "F"), "F");
    if(!tmp)
    {
        // printf("FFFFFFFFFF 1337");
        return (FALSE);
    }
    free(tmp);
    paths_struct.pars.ex_color = str_(rest_(find_(line, "F"), "F"));
    tmp = rest_(find_(line, "C"), "C");
    if(!tmp)
    {

        // printf("CCCCCCCCC 1337");
        return (free(paths_struct.pars.ex_color), FALSE);
    }
    // printf("ERROR 1337");
    free(tmp);
    paths_struct.pars.ex_color = str_(rest_(find_(line, "C"), "C"));
    // printf("ERROR 1337******");
    return (TRUE);
}

int check_line(char *str)
{
    char **file;
    char **line;

    file = read_line(str);//read the lines of the file and stroed in an array
    line = extract_6(file);
    // free_(file);

    if(!paths(line))
        return (free_(line), FALSE);
    if(!ex_color(line))
        return (free_(line), free(paths_struct.pars.path_ea), free(paths_struct.pars.path_we), free(paths_struct.pars.path_so), free(paths_struct.pars.path_no), FALSE);
    printf("TEST 2: good💪🏻\n");
    return (free_(line), TRUE);
}

int parsing(char *str)
{
    if (!is_cub(str))
        return (printf("check '.cub'\n"), 0);
    if (!check_line(str))
        return (printf("check file\n"), FALSE);
    // printf("code error : %d\n", check_line(str));
    return 1;
}