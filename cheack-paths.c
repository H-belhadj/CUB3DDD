/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack-paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelhadj <hbelhadj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:32:12 by hbelhadj          #+#    #+#             */
/*   Updated: 2024/03/28 22:34:07 by hbelhadj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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

char *find_(char **line, char *target)
{
    int i;
    // char *line_ptr;
    // char *target_ptr;
    
    if(line == NULL || target == NULL)
        return (NULL);
    
    i = 0;
    while(line[i])
    {
        if (strncmp(line[i], target, strlen(target)) == 0) 
            return line[i];
        i++;
    }
    return (NULL);
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
        return (NULL);
    while(line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    store = strdup(line + 1);//This line uses the strdup function to create a duplicate of the part of the line after skipping leading spaces or tabs. It starts copying from the position indicated by line + i, which is the first non-space or non-tab character
    if(!store)
        return (NULL);
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

int paths(char **line)
{
    bzero(paths_struct.pars.textures, sizeof(char *) * 4);
    char *tmp = rest_(find_(line, "NO"), "NO");
    if (!tmp)
        return FALSE;
    free(tmp);
    paths_struct.pars.textures[NO] = str_(rest_(find_(line, "NO"), "NO"));
    tmp = rest_(find_(line, "SO"), "SO");
    if (!tmp)
        return (free(paths_struct.pars.textures[NO]), FALSE);
    free(tmp);
    paths_struct.pars.textures[SO] = str_(rest_(find_(line, "SO"), "SO"));
    tmp = rest_(find_(line, "WE"), "WE");
    if (!tmp)
        return (free(paths_struct.pars.textures[NO]), free(paths_struct.pars.textures[SO]), FALSE);
    free(tmp);
    paths_struct.pars.textures[WE] = str_(rest_(find_(line, "WE"), "WE"));
    tmp = rest_(find_(line, "EA"), "EA");
    if (!tmp)
        return (free(paths_struct.pars.textures[NO]), free(paths_struct.pars.textures[SO]),
                free(paths_struct.pars.textures[WE]), FALSE);
    free(tmp);
    paths_struct.pars.textures[EA] = str_(rest_(find_(line, "EA"), "EA"));
    return TRUE;
}