/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oszwalbe <oszwalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:56:39 by oszwalbe          #+#    #+#             */
/*   Updated: 2024/06/26 18:35:49 by oszwalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bottom_suite(char *addr_img, int size_line, int ground_color[3])
{
	int	x;
	int	y;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			addr_img[(y * size_line) + x * 4 + 0] = ground_color[2];
			addr_img[(y * size_line) + x * 4 + 1] = ground_color[1];
			addr_img[(y * size_line) + x * 4 + 2] = ground_color[0];
			x++;
		}
		y++;
	}
}

void	top_and_bottom(t_raycasting *data, int sky[3], int ground[3], int x)
{
	int		y;
	int		size_line;
	int		bpp;
	int		endian;
	char	*addr_img;

	y = 0;
	addr_img = mlx_get_data_addr(data->img, &bpp, &size_line, &endian);
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			addr_img[(y * size_line) + x * 4 + 0] = sky[2];
			addr_img[(y * size_line) + x * 4 + 1] = sky[1];
			addr_img[(y * size_line) + x * 4 + 2] = sky[0];
			x++;
		}
		y++;
	}
	bottom_suite(addr_img, size_line, ground);
}

void	suite_calculate2(t_raycasting *data)
{
	if (data->rayside == 0)
	{
		data->raywallsize = (data->raymapx - data->posx + (1 - data->raystepx)
				/ 2) / data->raydirx;
		data->wallx = data->posy + data->raywallsize * data->raydiry;
	}
	else
	{
		data->raywallsize = (data->raymapy - data->posy + (1 - data->raystepy)
				/ 2) / data->raydiry;
		data->wallx = data->posx + data->raywallsize * data->raydirx;
	}
	data->wallx -= floor(data->wallx);
	data->raylineheight = (int)(HEIGHT / data->raywallsize);
	data->raydrawstart = -data->raylineheight / 2 + HEIGHT / 2;
	if (data->raydrawstart < 0)
		data->raydrawstart = 0;
	data->raydrawend = data->raylineheight / 2 + HEIGHT / 2;
	if (data->raydrawend >= HEIGHT || data->raydrawend < 0)
		data->raydrawend = HEIGHT - 1;
}

void	suite_calculate(t_raycasting *data)
{
	while (data->rayhit == 0)
	{
		if (data->raydistx < data->raydisty)
		{
			data->raydistx += data->deltadistx;
			data->raymapx += data->raystepx;
			data->rayside = 0;
		}
		else
		{
			data->raydisty += data->deltadisty;
			data->raymapy += data->raystepy;
			data->rayside = 1;
		}
		if (data->s->map[data->raymapx][data->raymapy] > '0')
			data->rayhit = 1;
	}
	suite_calculate2(data);
}

void	calculate_ray(t_raycasting *data)
{
	if (data->raydirx < 0)
	{
		data->raystepx = -1;
		data->raydistx = (data->posx - data->raymapx) * data->deltadistx;
	}
	else
	{
		data->raystepx = 1;
		data->raydistx = (data->raymapx + 1.0 - data->posx) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->raystepy = -1;
		data->raydisty = (data->posy - data->raymapy) * data->deltadisty;
	}
	else
	{
		data->raystepy = 1;
		data->raydisty = (data->raymapy + 1.0 - data->posy) * data->deltadisty;
	}
	suite_calculate(data);
}
