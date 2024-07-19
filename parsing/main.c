/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:09:43 by ticouvre          #+#    #+#             */
/*   Updated: 2024/06/27 09:33:23 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct(t_data *s)
{
	s->north = NULL;
	s->south = NULL;
	s->west = NULL;
	s->east = NULL;
	s->map = NULL;
	s->tmp = NULL;
	s->fd = -1;
	s->ceiling[0] = -1;
	s->floor[0] = -1;
	return (0);
}

int	free_struct(t_data *s, t_raycasting *ray, int img)
{
	int	i;

	i = 0;
	(void)s;
	if (s->north)
		free(s->north);
	if (s->south)
		free(s->south);
	if (s->west)
		free(s->west);
	if (s->east)
		free(s->east);
	if (s->map)
		ft_free_tab(s->map, 0);
	if (s->fd != -1)
		close(s->fd);
	while (i < 4 && ray->textures[i].img_data && img)
		mlx_destroy_image(ray->mlx_ptr, ray->textures[i++].img_data);
	mlx_destroy_display(ray->mlx_ptr);
	free(ray->mlx_ptr);
	free(s);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data			*s;
	t_raycasting	ray;

	if (ac == 2)
	{
		s = malloc(sizeof(t_data));
		if (!s)
			return (ERROR_MALLOC);
		init(&ray);
		init_struct(s);
		if (check_file(av[1], s))
			return (free_struct(s, &ray, 1), 1);
		if (check_texture(s, &ray))
			return (free_struct(s, &ray, 0), 1);
		if (check_map(s))
			return (free_struct(s, &ray, 1), 1);
		init_raycasting2(&ray, s);
		mlx_hook(ray.mlx_win, 33, 1L << 17, clear_window, &ray);
		mlx_hook(ray.mlx_win, 2, 1L << 0, ft_key_press, &ray);
		mlx_loop_hook(ray.mlx_ptr, raycasting, &ray);
		mlx_hook(ray.mlx_win, 3, 1L << 1, ft_key_release, &ray);
		mlx_loop(ray.mlx_ptr);
		free_struct(s, &ray, 1);
	}
	return (printf("Error\nToo few arguments.\n"), 1);
}
