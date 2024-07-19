/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oszwalbe <oszwalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:42:20 by oszwalbe          #+#    #+#             */
/*   Updated: 2024/06/26 15:49:00 by oszwalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forward_and_back(t_raycasting *data, t_data *s)
{
	if (data->forward == 1)
	{
		if (s->map[(int)(data->posx + (data->dirx * data->movespeed
					* 2))][(int)(data->posy)] == '0')
			data->posx += data->dirx * data->movespeed;
		if (s->map[(int)(data->posx)][(int)(data->posy + (data->diry
					* data->movespeed * 2))] == '0')
			data->posy += data->diry * data->movespeed;
	}
	if (data->back == 1)
	{
		if (s->map[(int)(data->posx - (data->dirx * data->movespeed
					* 2))][(int)(data->posy)] == '0')
			data->posx -= data->dirx * data->movespeed;
		if (s->map[(int)(data->posx)][(int)(data->posy - (data->diry
					* data->movespeed * 2))] == '0')
			data->posy -= data->diry * data->movespeed;
	}
}

void	left(t_raycasting *data, t_data *s)
{
	if (s->map[(int)(data->posx - data->diry * (data->movespeed
				* 2))][(int)data->posy] == '0')
		data->posx -= data->diry * data->movespeed;
	if (s->map[(int)data->posx][(int)(data->posy + data->dirx
		* (data->movespeed * 2))] == '0')
		data->posy += data->dirx * data->movespeed;
}

void	right(t_raycasting *data, t_data *s)
{
	if (s->map[(int)(data->posx + data->diry * (data->movespeed
				* 2))][(int)data->posy] == '0')
		data->posx += data->diry * data->movespeed;
	if (s->map[(int)data->posx][(int)(data->posy - data->dirx
		* (data->movespeed * 2))] == '0')
		data->posy -= data->dirx * data->movespeed;
}

void	rotate_left(t_raycasting *data)
{
	double	oldplanx;
	double	olddirx;

	oldplanx = data->planex;
	olddirx = data->dirx;
	data->dirx = data->dirx * cos(data->rotspeed / 2) - data->diry
		* sin(data->rotspeed / 2);
	data->diry = olddirx * sin(data->rotspeed / 2) + data->diry
		* cos(data->rotspeed / 2);
	data->planex = data->planex * cos(data->rotspeed / 2) - data->planey
		* sin(data->rotspeed / 2);
	data->planey = oldplanx * sin(data->rotspeed / 2) + data->planey
		* cos(data->rotspeed / 2);
}

void	rotate_right(t_raycasting *data)
{
	double	oldplanx;
	double	olddirx;

	oldplanx = data->planex;
	olddirx = data->dirx;
	data->dirx = data->dirx * cos(-data->rotspeed / 2) - data->diry
		* sin(-data->rotspeed / 2);
	data->diry = olddirx * sin(-data->rotspeed / 2) + data->diry
		* cos(-data->rotspeed / 2);
	data->planex = data->planex * cos(-data->rotspeed / 2) - data->planey
		* sin(-data->rotspeed / 2);
	data->planey = oldplanx * sin(-data->rotspeed / 2) + data->planey
		* cos(-data->rotspeed / 2);
}
