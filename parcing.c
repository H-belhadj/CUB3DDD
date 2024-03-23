/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:54:41 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/23 18:18:58 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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

int line_number(char *str)
{
    int fd;
    int cnt;
    char *string;

    fd = open(str, O_RDWR);
    if (fd == -1)
    {
        // Error opening file
        perror("Error opening file");
        return FALSE; // Indicate error
    }

    cnt = 1;
    string = get_next_line(fd);
    while (string)
    {
        cnt++;
        free(string);
        string = get_next_line(fd);
    }
    free(string);
    close(fd);

    return cnt;
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
    paths_struct.pars.F_color = str_(rest_(find_(line, "F"), "F"));
    tmp = rest_(find_(line, "C"), "C");
    if(!tmp)
    {

        // printf("CCCCCCCCC 1337");
        return (free(paths_struct.pars.F_color), FALSE);
    }
    // printf("ERROR 1337");
    free(tmp);
    paths_struct.pars.C_color = str_(rest_(find_(line, "C"), "C"));
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
    {
        // printf("==============LA FEVE=============\n");
        return (free_(line), FALSE);
    }
    
    if(!ex_color(line))
    {
        // printf("==============LA FEVE=============\n");
        return (free_(line), free(paths_struct.pars.path_ea), free(paths_struct.pars.path_we), free(paths_struct.pars.path_so), free(paths_struct.pars.path_no), FALSE);
    }
    printf("TEST 2: good\n");
    return (free_(line), TRUE);
}

//<<============================check-colors-part======================>>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (TRUE);
	else
		return (FALSE);
}

int	ft_count_world(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			cnt++;
		i++;
	}
	return (cnt);
}

static	char	**ft_split_world(char  *s, char c)
{
	char	**dest;
	int		i;
	int		j;
	int		simobb;

	dest = malloc(sizeof(char *) * (ft_count_world(s, c) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_count_world(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		simobb = 0;
		while (s[i] && s[i] != c)
		{
			simobb++;
			i++;
		}
		dest[j] = ft_substr(s, (i - simobb), simobb);
		j++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char  *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = ft_split_world(s, c);
	return (dest);
}
int digitcomma_(char *str)
{
    while(*str)
    {
        if(*str != ',' && !ft_isdigit(*str))
            return (FALSE);   
        str++;
    }
    return (TRUE);
}
int commas_(char *str)
{
    int cnt;

    cnt = 0;
    while(*str)
    {
        if(*str == ',')
        {
            cnt++;
            if(cnt > 2)
                return (FALSE);
        }
        str++;
    }
    return (cnt == 2);
}

int	ft_atoi(const char *str)
{
	int	r;
	int	sign;
	int	i;

	r = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}	
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r * sign);
}

int length_(char **str)
{
    int i;
    int len;
    int num;
    
    i = -1;
    while(str[++i])
    {
        len = 0;
        while(str[i][len] != '\0')
            len++;
        if(len < 1 || len > 3)
            return (FALSE);
        num = ft_atoi(str[i]);
        if(num < 0 || num > 255)
            return (FALSE);
    }
    return (TRUE);
}

int check_colors(void)
{
    int i;

    i = 0;
    if(!paths_struct.pars.C_color || !paths_struct.pars.C_color)
        return (FALSE);
    if(!digitcomma_(paths_struct.pars.C_color )|| !digitcomma_(paths_struct.pars.F_color))
        return (FALSE);
    if(!commas_(paths_struct.pars.C_color) && commas_(paths_struct.pars.F_color))
        return (free(paths_struct.pars.F_color), FALSE); 
    if(!commas_(paths_struct.pars.F_color) && commas_(paths_struct.pars.C_color))
        return (free(paths_struct.pars.C_color), FALSE);
    if(!commas_(paths_struct.pars.F_color) && !commas_(paths_struct.pars.C_color))
        return (FALSE);
    paths_struct.pars.c = ft_split(paths_struct.pars.C_color, ',');
    paths_struct.pars.f = ft_split(paths_struct.pars.F_color, ',');
    free(paths_struct.pars.C_color);
    free(paths_struct.pars.F_color);
    if(!length_(paths_struct.pars.c) || !length_(paths_struct.pars.f))
        return (FALSE);
    printf("TEST 3: good💪\n");
    return (TRUE);
}




//<<============================check-colors-part======================>>
int accessible(void)
{
    int	fd;

	fd = open(paths_struct.pars.path_ea, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(paths_struct.pars.path_so, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(paths_struct.pars.path_no, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(paths_struct.pars.path_we, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

//<<============================check-access======================>>



//<<============================check-access======================>>

int parsing(char *str)
{
    if (!is_cub(str))
        return (printf("TEST 1: BAD\n"), FALSE);
    sleep(1);
    if (!check_line(str))
        return (printf("TEST 2: BAD\n"), FALSE);
    sleep(1);
    if (!check_colors())
        return (printf("TEST 3: BAD\n"), FALSE);
    sleep(1);
    if(!accessible())
        return (printf("TEST 4: BAD\n"), FALSE);

    // printf("code error : %d\n", check_line(str));
    return (TRUE);
}