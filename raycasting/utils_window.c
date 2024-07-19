/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:32:39 by oszwalbe          #+#    #+#             */
/*   Updated: 2024/06/27 09:34:19 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_dir_suite(t_raycasting *data, double screen_ratio)
{
	if (data->s->orientation == 'E')
	{
		data->dirx = 0;
		data->diry = 1;
		data->planex = screen_ratio;
		data->planey = 0;
	}
	if (data->s->orientation == 'W')
	{
		data->dirx = 0;
		data->diry = -1;
		data->planex = -screen_ratio;
		data->planey = 0;
	}
}

void	ft_init_dir(t_raycasting *data)
{
	double	screen_ratio;

	screen_ratio = (double)WIDTH / (double)HEIGHT * 0.5;
	if (data->s->orientation == 'N')
	{
		data->dirx = -1;
		data->diry = 0;
		data->planex = 0;
		data->planey = screen_ratio;
	}
	if (data->s->orientation == 'S')
	{
		data->dirx = 1;
		data->diry = 0;
		data->planex = 0;
		data->planey = -screen_ratio;
	}
	ft_init_dir_suite(data, screen_ratio);
}

void	init_raycasting2(t_raycasting *data, t_data *s)
{
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "My Cub3d !");
	if (data->mlx_win == NULL)
	{
		free(data->mlx_ptr);
		return ;
	}
	data->posx = s->player_y + 0.5;
	data->posy = s->player_x + 0.5;
	data->dirx = -1;
	data->diry = 0;
	data->planex = 0;
	data->planey = 0.66;
	data->time = 0;
	data->oldtime = 0;
	data->forward = -1;
	data->back = -1;
	data->left = -1;
	data->right = -1;
	data->rotate_left = -1;
	data->rotate_right = -1;
	data->s = s;
	ft_init_dir(data);
}

int	clear_window(t_raycasting *data)
{
	if (data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	if (data->mlx_ptr)
	{
		mlx_loop_end(data->mlx_ptr);
	}
	free_struct(data->s, data, 1);
	exit(0);
}

void	set_num_color(t_raycasting *data, int *color)
{
	if (data->rayside == 0)
	{
		if (data->raydirx < 0)
			*color = 0;
		else
			*color = 1;
	}
	else
	{
		if (data->raydiry < 0)
			*color = 2;
		else
			*color = 3;
	}
}
