/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oszwalbe <oszwalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:59:02 by oszwalbe          #+#    #+#             */
/*   Updated: 2024/06/26 17:07:43 by oszwalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_digit(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			count++;
		i++;
	}
	return (count);
}

int	ft_key_press(int keycode, t_raycasting *data)
{
	if (keycode == XK_w)
		data->forward = 1;
	if (keycode == XK_Escape)
		clear_window(data);
	else if (keycode == XK_s)
		data->back = 1;
	else if (keycode == XK_a)
		data->left = 1;
	else if (keycode == XK_d)
		data->right = 1;
	else if (keycode == XK_Left)
		data->rotate_left = 1;
	else if (keycode == XK_Right)
		data->rotate_right = 1;
	return (1);
}

int	ft_key_release(int keycode, t_raycasting *data)
{
	if (keycode == XK_w)
		data->forward = 0;
	else if (keycode == XK_s)
		data->back = 0;
	else if (keycode == XK_a)
		data->left = 0;
	else if (keycode == XK_d)
		data->right = 0;
	else if (keycode == XK_Left)
		data->rotate_left = 0;
	else if (keycode == XK_Right)
		data->rotate_right = 0;
	return (1);
}

int	key_event(t_raycasting *data, t_data *s)
{
	forward_and_back(data, s);
	if (data->left == 1)
		left(data, s);
	if (data->right == 1)
		right(data, s);
	if (data->rotate_left == 1)
		rotate_left(data);
	if (data->rotate_right == 1)
		rotate_right(data);
	return (0);
}

void	init(t_raycasting *data)
{
	int	i;

	i = 0;
	while (i < 4)
		data->textures[i++].img_data = NULL;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return ;
}
