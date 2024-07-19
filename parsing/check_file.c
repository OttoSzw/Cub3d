/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:37:10 by ticouvre          #+#    #+#             */
/*   Updated: 2024/06/27 10:52:48 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char *str, t_data *s)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (len_str < 4 || !(str[len_str - 1] == 'b' && str[len_str - 2] == 'u'
			&& str[len_str - 3] == 'c' && str[len_str - 4] == '.'))
	{
		printf("%s", "Error\nInvalid file name.\n");
		return (1);
	}
	s->fd = open(str, O_RDONLY);
	if (s->fd < 0)
	{
		printf("Error\nFile doesn't exist.\n");
		return (1);
	}
	len_str = check_line(get_next_line(s->fd), s);
	if (len_str)
	{
		if (len_str == 3)
			return (printf("Error\nEmpty file.\n"), 1);
		printf("Error\nInvalid texture/color.\n");
		return (1);
	}
	return (0);
}

int	check_line(char *str, t_data *s)
{
	int	i;

	i = 0;
	if (!str)
		return (ERROR_MALLOC);
	if (!check_space_line(str))
		return (free(str), 0);
	else if (!ft_strncmp(str, "NO ", 2) && !s->north)
		return (get_line(str, s));
	else if (!ft_strncmp(str, "SO ", 2) && !s->south)
		return (get_line(str, s));
	else if (!ft_strncmp(str, "WE ", 2) && !s->west)
		return (get_line(str, s));
	else if (!ft_strncmp(str, "EA ", 2) && !s->east)
		return (get_line(str, s));
	else if (!ft_strncmp(str, "F ", 2) && s->floor[0])
		return (get_line(str, s));
	else if (!ft_strncmp(str, "C ", 2) && s->ceiling[0])
		return (get_line(str, s));
	return (free(str), 1);
}

int	get_line(char *str, t_data *s)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	k = 0;
	i = 2;
	while (ft_isspace(str[i]))
		i++;
	while (str[i + j] && !ft_isspace(str[i + j]))
		j++;
	while (ft_isspace(str[i + j + k]))
		k++;
	if (str[i + j + k] != '\0' || j == 0)
	{
		free(str);
		return (1);
	}
	if (str[0] == 'F' || str[0] == 'C')
		return (parse_color(str, i, j, s));
	return (parse_texture(str, i, j, s));
}
