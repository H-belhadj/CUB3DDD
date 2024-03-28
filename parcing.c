/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:54:41 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/28 22:41:35 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


bool ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}


int check_line(char *str)
{
    char **file;
    char **line;

    file = read_line(str);//read the lines of the file and stroed in an array
    line = extract_6(file);
    free_(file);
    if(!paths(line))
        return (free_(line), FALSE);
    if(!ex_color(line))
        return (free_(line), free_(paths_struct.pars.textures), FALSE);
    printf("TEST 2: good💪\n");
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




// //<<============================check-colors-part======================>>


// //<<============================check-access======================>>
int accessible()
{
    int	fd;
    int i;

    i = -1;
    while (paths_struct.pars.textures[i])
    {
        fd = open(paths_struct.pars.textures[i], O_RDONLY);
        if (fd < 0)
		    return (FALSE);
        close(fd);
    }
    printf("TEST 4: good💪\n");
	return (TRUE);
}
//<<============================check-access======================>>
//<<============================check-map======================>>

int	check_existance(char c)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (paths_struct.pars.map[++i])
	{
		j = -1;
		while (paths_struct.pars.map[i][++j])
		{
			if (paths_struct.pars.map[i][j] == c)
				count++;
		}
	}
	if (!count)
		return (FALSE);
	return (TRUE);
}

int	player_num(void)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	c = 0;
	while (paths_struct.pars.map[++i])
	{
		j = -1;
		while (paths_struct.pars.map[i][++j])
		{
			if (paths_struct.pars.map[i][j] == 'N' || paths_struct.pars.map[i][j] == 'S'
				|| paths_struct.pars.map[i][j] == 'E' || paths_struct.pars.map[i][j] == 'W')
				c++;
		}
	}
	if (c != 1)
		return (FALSE);
	return (1);
}

int	check_content(void)
{
	int	i;
	int	j;

	i = -1;
	while (paths_struct.pars.map[++i])
	{
		j = -1;
		while (paths_struct.pars.map[i][++j])
		{
			if (paths_struct.pars.map[i][j] != '0' && paths_struct.pars.map[i][j] != '1'
				&& paths_struct.pars.map[i][j] != '\n' && paths_struct.pars.map[i][j] != 'N'
				&& paths_struct.pars.map[i][j] != 'S' && paths_struct.pars.map[i][j] != 'E'
				&& paths_struct.pars.map[i][j] != 'W' && paths_struct.pars.map[i][j] != ' ')
				return (FALSE);
		}
	}
	if (!player_num())
		return (FALSE);
	if (!check_existance('0') || !check_existance('1')
		|| !check_existance('\n'))
		return (FALSE);
	return (TRUE);
}



void	player_pos(void)
{
	int	i;
	int	j;

	i = -1;
	while (paths_struct.pars.map[++i])
	{
		j = -1;
		while (paths_struct.pars.map[i][++j])
		{
			if (paths_struct.pars.map[i][j] == 'N' || paths_struct.pars.map[i][j] == 'S'
				|| paths_struct.pars.map[i][j] == 'E' || paths_struct.pars.map[i][j] == 'W')
			{
				paths_struct.pars.pos = paths_struct.pars.map[i][j];
				paths_struct.pars.x = i;
				paths_struct.pars.y = j;
			}
		}
	}
}

int	all_white(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (FALSE);
	}
	return (1);
}

int	lines_number(char *str)
{
	char	*s;
	int		fd;
	int		i;

	i = 0;
	fd = open(str, O_RDWR);
	s = get_next_line(fd);
	while (s)
	{
		++i;
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
	return (i);
}
int	end(char **file, char *str)
{
	int	e;

	e = lines_number(str);
	e--;
	while (all_white(file[e]))
		e--;
	return (e);
}


int	dot_cub(char *str)
{
	if (strcmp(str + (ft_strlen(str) - ft_strlen(".cub")), ".cub")
		|| open(str, O_RDWR) < 0)
	{
		printf("Error\nfile_err\n");
		return (FALSE);
	}
	return (TRUE);
}


int	map_len(void)
{
	int	i;

	i = 0; 
	while (paths_struct.pars.map[i])
		i++;
	return (i);
}

int	check_first_last(void)
{
	int	i;
	int	e;

	i = -1;
	while (paths_struct.pars.map[0][++i])
	{
		if (paths_struct.pars.map[0][i] == '0'
			|| paths_struct.pars.map[0][i] == paths_struct.pars.pos)
			return (FALSE);
	}
	e = map_len() - 1;
	i = -1;
	while (paths_struct.pars.map[e][++i])
	{
		if (paths_struct.pars.map[e][i] == '0'
			|| paths_struct.pars.map[e][i] == paths_struct.pars.pos)
			return (FALSE);
	}
	return (1);
}

int	skip_part1(char **tab)
{

	int		i;
	int		c;

	i = -1;
	c = 0;
	while (tab[++i] && c < 6)
	{
		if ((tab[i][0] == ' ' || tab[i][0] == '\t') && !all_white(tab[i]))
			c++;
		else if ((tab[i][0] == ' ' || tab[i][0] == '\t') && all_white(tab[i]))
		{
		}
		else if (tab[i][0] != '\n' && ft_strlen(tab[i]) >= 1)
			c++;
	}
	if (all_white(tab[i]))
		while (all_white(tab[i]))
			i++;
	return (i);
}

void	put_map(char **file, char *str)
{

	int	i;
	int	j;
	int	n;

	i = skip_part1(file);
	paths_struct.pars.map = malloc(sizeof(char *) * ((lines_number(str) - i) + 1));
	j = 0;
	n = 0;
	while (file[i] && i <= end(file, str))
	{
		paths_struct.pars.map[j] = ft_strdup(file[i]);
		j++;
		i++;
	}
	paths_struct.pars.map[j] = NULL;
	free_(file);
}

int	is_closed(char c)
{
	int	i;
	int	j;
	int len_map = map_len();
	// printf("len_map  %d \n", len_map);
	
	i = -1;
	while (paths_struct.pars.map[++i] && i < len_map)
	{
		// printf("%s \n", paths_struct.pars.map[i]);
		j = -1;
		while (paths_struct.pars.map[i][++j])
		{
			// printf("%c \n", paths_struct.pars.map[i][j]);
			if (paths_struct.pars.map[i][j] == c)
			{
				if ((paths_struct.pars.map[i][j - 1] == ' '
					|| paths_struct.pars.map[i][j - 1] == 0)
					|| (paths_struct.pars.map[i][j + 1] == ' '
					|| paths_struct.pars.map[i][j + 1] == 0)
					|| (paths_struct.pars.map[i - 1][j] == ' '
					|| j + 1 >= (int)strlen(paths_struct.pars.map[i - 1]))
					|| (paths_struct.pars.map[i + 1][j] == ' '
					|| j + 1 >= (int)strlen(paths_struct.pars.map[i + 1])))
					return (FALSE);
			}
		}
	}
	return (TRUE);
}

int	empty_line(void)
{
	int	i;

	i = -1;
	while (paths_struct.pars.map[++i])
	{
		if (all_white(paths_struct.pars.map[i]))
			return (FALSE);
	}
	return (TRUE);
}

int	checker_map1(char *str)
{
	// (void)str;
	put_map(read_line(str), str);
	if (!empty_line())
		return (FALSE);
	if (!check_content())
		return (FALSE);
	player_pos();
	if (!check_first_last())
		return (FALSE);
	if (!is_closed(paths_struct.pars.pos))
		return (FALSE);
    printf("TEST 5: good💪\n");
	return (TRUE);
}

//<<============================check-map======================>>


int parsing(char *str)
{
    if (!is_cub(str))
        return (printf("TEST 1: BAD🆘\n"), FALSE);
    usleep(500000);
    if (!check_line(str))
        return (printf("TEST 2: BAD🆘\n"), FALSE);
    usleep(500000);
    if (!check_colors())
        return (printf("TEST 3: BAD🆘\n"), FALSE);
    usleep(500000);
    if(!accessible())
        return (printf("TEST 4: BAD🆘\n"), FALSE);
    usleep(500000);
    if(!checker_map1(str))
        return (printf("TEST 5: BAD🆘\n"), FALSE);
	usleep(500000);
	printf("ZOOOOOT ALL THE TESTS IS GOOD 9ATAAAAAA3 ✅\n");
    return (TRUE);
}