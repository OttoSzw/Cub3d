/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:48:39 by ticouvre          #+#    #+#             */
/*   Updated: 2024/06/27 10:19:15 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map_condition(int x, int y, t_data *s)
{
	if (s->map[y][x] == '0' || s->map[y][x] == 'N' || s->map[y][x] == 'S'
		|| s->map[y][x] == 'E' | s->map[y][x] == 'W')
	{
		if (y == 0)
			return (1);
		if (x >= (int)ft_strlen(s->map[y - 1]) || ft_isspace(s->map[y - 1][x]))
			return (1);
		if (!s->map[y + 1] || x >= (int)ft_strlen(s->map[y + 1]))
			return (1);
		if (ft_isspace(s->map[y + 1][x]))
			return (1);
		if (x + 1 >= (int)ft_strlen(s->map[y]))
			return (1);
		if (ft_isspace(s->map[y][x + 1]))
			return (1);
		if (x == 0)
			return (1);
		if (ft_isspace(s->map[y][x - 1]))
			return (1);
	}
	return (0);
}

int	valid_map_line(int *count, int x, int y, t_data *s)
{
	if (s->map[y][x] == 'N' || s->map[y][x] == 'S' || s->map[y][x] == 'E'
		|| s->map[y][x] == 'W')
	{
		s->orientation = s->map[y][x];
		s->player_x = x;
		s->player_y = y;
		s->map[y][x] = '0';
		(*count)++;
	}
	if (valid_map_condition(x, y, s))
	{
		printf("Error\nInvalid map.\n");
		return (1);
	}
	return (0);
}

int	valid_map(t_data *s)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (valid_map_line(&count, x, y, s))
				return (1);
			x++;
		}
		y++;
	}
	if (count != 1)
	{
		printf("Error\nToo much player’s start position.\n");
		return (1);
	}
	return (0);
}

int	check_map(t_data *s)
{
	int	i;
	int	map;

	map = get_map(s);
	if (map)
		return (map);
	i = 0;
	while (s->tmp[i])
	{
		if (!(s->tmp[i] == '0' || s->tmp[i] == '1' || s->tmp[i] == 'N'
				|| s->tmp[i] == 'S' || s->tmp[i] == 'E' || s->tmp[i] == 'W'
				|| ft_isspace(s->tmp[i])))
		{
			printf("Error\nUnknow character in the map.\n");
			free(s->tmp);
			return (1);
		}
		i++;
	}
	free(s->tmp);
	if (valid_map(s))
		return (1);
	return (0);
}

int	get_map(t_data *s)
{
	char	*line;
	int		empty_line;

	empty_line = 1;
	line = get_next_line(s->fd);
	if (!line)
		return (printf("Error\nMissing map.\n"), 1);
	s->tmp = ft_strdup("\n");
	if (!s->tmp)
		return (ERROR_MALLOC);
	while (line)
	{
		if (get_map_line(line, &empty_line, s))
			return (1);
		line = get_next_line(s->fd);
		if (!check_space_line(line))
		{
			printf("Error\nEmpty line in the map.\n");
			return (free(line), free(s->tmp), 1);
		}
	}
	s->map = ft_split(s->tmp, '\n');
	if (!s->map)
		return (free(s->tmp), ERROR_MALLOC);
	return (0);
}
