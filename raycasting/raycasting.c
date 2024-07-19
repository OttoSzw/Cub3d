/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oszwalbe <oszwalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:21:20 by oszwalbe          #+#    #+#             */
/*   Updated: 2024/06/26 18:29:14 by oszwalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting(t_raycasting *data, int x)
{
	data->raycamerax = 2.0 * (x / (double)WIDTH) - 1.0;
	data->raydirx = data->dirx + data->planex * data->raycamerax;
	data->raydiry = data->diry + data->planey * data->raycamerax;
	data->raydistx = 0;
	data->raydisty = 0;
	data->deltadistx = fabs(1 / data->raydirx);
	data->deltadisty = fabs(1 / data->raydiry);
	data->raymapx = (int)data->posx;
	data->raymapy = (int)data->posy;
	data->raystepx = 0;
	data->raystepy = 0;
	data->rayhit = 0;
	data->rayside = 0;
	data->raywallsize = 0;
	data->raylineheight = 0;
	data->raydrawstart = 0;
	data->raydrawend = 0;
	data->movespeed = 0.08;
	data->rotspeed = 0.08;
	data->wallx = 0;
	data->rayposx = (double)data->posx;
	data->rayposy = (double)data->posy;
}

void	drawtexture2(t_raycasting *data, int *texture_x, t_texture *texture,
		double *tpos)
{
	*texture_x = (int)(data->wallx * (double)(texture->tex_width));
	if ((data->rayside == 0 && data->raydirx > 0) || (data->rayside == 1
			&& data->raydiry < 0))
		*texture_x = texture->tex_width - *(texture_x) - 1;
	data->addr_img = mlx_get_data_addr(data->img, &data->bpp, &data->size_line,
			&data->endian);
	data->step = 1.0 * texture->tex_height / data->raylineheight;
	*tpos = (data->raydrawstart - HEIGHT / 2 + data->raylineheight / 2)
		* data->step;
}

void	drawtexture(t_raycasting *data, t_texture *texture, int x)
{
	int		start;
	int		end;
	int		texture_x;
	int		texture_y;
	double	texpos;

	texture_x = 0;
	start = data->raydrawstart;
	end = data->raydrawend;
	drawtexture2(data, &texture_x, texture, &texpos);
	while (start < end)
	{
		texture_y = (int)texpos & (texture->tex_height - 1);
		texpos += data->step;
		data->addr_img[(start * data->size_line) + x * 4
			+ 0] = texture->addr[(texture_y * texture->size_line) + texture_x
			* 4 + 0];
		data->addr_img[(start * data->size_line) + x * 4
			+ 1] = texture->addr[(texture_y * texture->size_line) + texture_x
			* 4 + 1];
		data->addr_img[(start * data->size_line) + x * 4
			+ 2] = texture->addr[(texture_y * texture->size_line) + texture_x
			* 4 + 2];
		start++;
	}
}

int	raycasting(t_raycasting *data)
{
	int	x;
	int	color;

	x = 0;
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	top_and_bottom(data, data->s->ceiling, data->s->floor, 0);
	x = 0;
	while (x < WIDTH)
	{
		init_raycasting(data, x);
		calculate_ray(data);
		set_num_color(data, &color);
		drawtexture(data, &data->textures[color], x);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img);
	key_event(data, data->s);
	return (0);
}
