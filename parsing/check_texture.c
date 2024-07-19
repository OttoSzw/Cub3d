/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:53:36 by ticouvre          #+#    #+#             */
/*   Updated: 2024/06/27 12:24:25 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *str, int i, int j, t_data *s)
{
	if (str[0] == 'N' && !s->north)
	{
		s->north = ft_strndup(str + i, j);
		if (!s->north)
			return (free(str), ERROR_MALLOC);
		return (free(str), 0);
	}
	else if (str[0] == 'S' && !s->south)
	{
		s->south = ft_strndup(str + i, j);
		if (!s->south)
			return (free(str), ERROR_MALLOC);
		return (free(str), 0);
	}
	else if ((str[0] == 'W') || (str[0] == 'E'))
		return (parse_texture_line(str, i, j, s));
	return (free(str), 1);
}

int	parse_color(char *str, int i, int j, t_data *s)
{
	int	x;

	x = i;
	if (count_digit(str) > 9)
		return (free(str), 1);
	if (!ft_isdigit(str[x]))
		return (free(str), 1);
	while (ft_isdigit(str[x]))
		x++;
	if (str[x] == ',')
		x++;
	if (!ft_isdigit(str[x]))
		return (free(str), 1);
	while (ft_isdigit(str[x]))
		x++;
	if (str[x] == ',')
		x++;
	if (!ft_isdigit(str[x]))
		return (free(str), 1);
	while (ft_isdigit(str[x]))
		x++;
	if (x != j + i)
		return (free(str), 1);
	return (get_color(str, i, s));
}

int	get_color(char *str, int i, t_data *s)
{
	if (str[0] == 'F' && s->floor[0] == -1)
	{
		s->floor[0] = ft_atoi(str + i);
		s->floor[1] = ft_atoi(str + i + ft_intlen(s->floor[0]) + 1);
		s->floor[2] = ft_atoi(str + i + ft_intlen(s->floor[0])
				+ ft_intlen(s->floor[1]) + 2);
		if (!(s->floor[0] >= 0 && s->floor[0] <= 255) || !(s->floor[1] >= 0
				&& s->floor[1] <= 255) || !(s->floor[2] >= 0
				&& s->floor[2] <= 255))
			return (free(str), 1);
	}
	else if (str[0] == 'C' && s->ceiling[0] == -1)
	{
		s->ceiling[0] = ft_atoi(str + i);
		s->ceiling[1] = ft_atoi(str + i + ft_intlen(s->ceiling[0]) + 1);
		s->ceiling[2] = ft_atoi(str + i + ft_intlen(s->ceiling[0])
				+ ft_intlen(s->ceiling[1]) + 2);
		if (!(s->ceiling[0] >= 0 && s->ceiling[0] <= 255)
			|| !(s->ceiling[1] >= 0 && s->ceiling[1] <= 255)
			|| !(s->ceiling[2] >= 0 && s->ceiling[2] <= 255))
			return (free(str), 1);
	}
	free(str);
	return (0);
}

int	check_texture(t_data *s, t_raycasting *ray)
{
	char	*line;
	int		res;

	line = get_next_line(s->fd);
	res = check_line(line, s);
	while (res == 0 && (!s->north || !s->south || !s->west || !s->east
			|| s->floor[0] == -1 || s->ceiling[0] == -1))
	{
		line = get_next_line(s->fd);
		res = check_line(line, s);
	}
	if (res == 1 || res == ERROR_MALLOC)
	{
		printf("Error\nInvalid texture/color.\n");
		return (1);
	}
	if (!s->north || !s->south || !s->west || !s->east || s->floor[0] == -1
		|| s->ceiling[0] == -1)
		return (printf("Error\nInvalid texture/color.\n"), 1);
	if (get_texture(s, ray))
		return (1);
	return (0);
}

int	get_texture(t_data *s, t_raycasting *ray)
{
	ray->textures[0].img_data = mlx_xpm_file_to_image(ray->mlx_ptr, s->north,
			&ray->textures[0].tex_width, &ray->textures[0].tex_height);
	if (!(ray->textures[0].img_data))
	{
		printf("Error\nInvalid north texture.\n");
		return (1);
	}
	ray->textures[0].addr = mlx_get_data_addr(ray->textures[0].img_data,
			&ray->textures[0].bpp, &ray->textures[0].size_line,
			&ray->textures[0].endian);
	ray->textures[1].img_data = mlx_xpm_file_to_image(ray->mlx_ptr, s->south,
			&ray->textures[1].tex_width, &ray->textures[1].tex_height);
	if (!(ray->textures[1].img_data))
	{
		printf("Error\nInvalid south texture.\n");
		mlx_destroy_image(ray->mlx_ptr, ray->textures[0].img_data);
		return (1);
	}
	ray->textures[1].addr = mlx_get_data_addr(ray->textures[1].img_data,
			&ray->textures[1].bpp, &ray->textures[1].size_line,
			&ray->textures[1].endian);
	return (get_texture_line(s, ray));
}
