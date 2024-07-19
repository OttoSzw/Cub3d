/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oszwalbe <oszwalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:55:46 by ticouvre          #+#    #+#             */
/*   Updated: 2024/06/27 12:15:02 by oszwalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_space_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (ft_isspace(str[i]))
		i++;
	if (i != (int)ft_strlen(str))
		return (1);
	return (0);
}

int	get_map_line(char *line, int *empty_line, t_data *s)
{
	while (!check_space_line(line) && empty_line)
	{
		free(line);
		line = get_next_line(s->fd);
	}
	if (!line)
	{
		printf("Error\nMissing map.\n");
		free(s->tmp);
		return (1);
	}
	empty_line = 0;
	s->tmp = ft_strjoin_gnl(s->tmp, line);
	if (!s->tmp)
		return (ERROR_MALLOC);
	free(line);
	return (0);
}

int	parse_texture_line(char *str, int i, int j, t_data *s)
{
	if (str[0] == 'W' && !s->west)
	{
		s->west = ft_strndup(str + i, j);
		if (!s->west)
			return (free(str), ERROR_MALLOC);
		return (free(str), 0);
	}
	else if (str[0] == 'E' && !s->east)
	{
		s->east = ft_strndup(str + i, j);
		if (!s->east)
			return (free(str), ERROR_MALLOC);
		return (free(str), 0);
	}
	return (free(str), 1);
}

void	destruction_image(t_raycasting *ray)
{
	printf("Error\nInvalid west texture.\n");
	mlx_destroy_image(ray->mlx_ptr, ray->textures[0].img_data);
	mlx_destroy_image(ray->mlx_ptr, ray->textures[1].img_data);
	mlx_destroy_image(ray->mlx_ptr, ray->textures[2].img_data);
}

int	get_texture_line(t_data *s, t_raycasting *ray)
{
	ray->textures[2].img_data = mlx_xpm_file_to_image(ray->mlx_ptr, s->east,
			&ray->textures[2].tex_width, &ray->textures[2].tex_height);
	if (!(ray->textures[2].img_data))
	{
		printf("Error\nInvalid east texture.\n");
		mlx_destroy_image(ray->mlx_ptr, ray->textures[0].img_data);
		mlx_destroy_image(ray->mlx_ptr, ray->textures[1].img_data);
		return (1);
	}
	ray->textures[2].addr = mlx_get_data_addr(ray->textures[2].img_data,
			&ray->textures[2].bpp, &ray->textures[2].size_line,
			&ray->textures[2].endian);
	ray->textures[3].img_data = mlx_xpm_file_to_image(ray->mlx_ptr, s->west,
			&ray->textures[3].tex_width, &ray->textures[3].tex_height);
	if (!(ray->textures[3].img_data))
	{
		destruction_image(ray);
		return (1);
	}
	ray->textures[3].addr = mlx_get_data_addr(ray->textures[3].img_data,
			&ray->textures[3].bpp, &ray->textures[3].size_line,
			&ray->textures[3].endian);
	return (0);
}
