/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:30:07 by ticouvre          #+#    #+#             */
/*   Updated: 2024/06/27 11:27:30 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# define WIDTH 2000
# define HEIGHT 1000
# define MOVE_SPEED 0.01
# define ROTATE_SPEED 0.33

# define ERROR_MALLOC 3

typedef struct s_data
{
	int			fd;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*tmp;
	char		**map;
	int			floor[3];
	int			ceiling[3];
	int			player_x;
	int			player_y;
	char		orientation;
}				t_data;

typedef struct s_texture
{
	int			tex_width;
	int			tex_height;
	void		*img_data;
	int			bpp;
	int			endian;
	int			size_line;
	char		*addr;
}				t_texture;

typedef struct s_raycasting
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	t_texture	textures[4];
	int			tex_width;
	int			tex_height;
	double		wallx;
	double		posy;
	double		posx;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		time;
	double		oldtime;
	double		movespeed;
	double		rotspeed;
	double		raycamerax;
	double		raydirx;
	double		raydiry;
	double		raydistx;
	double		raydisty;
	double		deltadistx;
	double		deltadisty;
	int			raymapx;
	int			raymapy;
	int			raystepx;
	int			raystepy;
	int			rayhit;
	int			rayside;
	double		raywallsize;
	int			raylineheight;
	int			raydrawstart;
	int			raydrawend;
	double		rayposx;
	double		rayposy;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			rotate_right;
	int			rotate_left;
	int			size_line;
	int			endian;
	int			bpp;
	char		*addr_img;
	double		step;
	t_data		*s;
}				t_raycasting;

// 					raycasting
int				clear_window(t_raycasting *data);
void			init_raycasting(t_raycasting *data, int x);
void			calculate_ray(t_raycasting *data);
int				raycasting(t_raycasting *data);
int				ft_key_press(int keycode, t_raycasting *data);
int				ft_key_release(int keycode, t_raycasting *data);
int				key_event(t_raycasting *data, t_data *s);
void			init(t_raycasting *data);
void			init_raycasting2(t_raycasting *data, t_data *s);
void			calculate_ray(t_raycasting *data);

//									check_file.c
int				check_line(char *str, t_data *s);
int				check_file(char *str, t_data *s);
int				get_line(char *str, t_data *s);

//									check_map.c
int				valid_map_condition(int x, int y, t_data *s);
int				valid_map_line(int *count, int x, int y, t_data *s);

int				valid_map(t_data *s);
int				check_map(t_data *s);
int				get_map(t_data *s);

//									check_texture.c
int				parse_texture(char *str, int i, int j, t_data *s);
int				parse_color(char *str, int i, int j, t_data *s);
int				get_color(char *str, int i, t_data *s);
int				check_texture(t_data *s, t_raycasting *ray);
int				get_texture(t_data *s, t_raycasting *ray);

//									utils.c
int				check_space_line(char *str);
int				get_map_line(char *line, int *empty_line, t_data *s);
int				parse_texture_line(char *str, int i, int j, t_data *s);
void			init_raycasting2(t_raycasting *data, t_data *s);
void			ft_init_dir(t_raycasting *data);
int				get_texture_line(t_data *s, t_raycasting *ray);
void			set_num_color(t_raycasting *data, int *color);
void			top_and_bottom(t_raycasting *data, int sky[3], int ground[3],
					int x);

//									main.c
int				free_struct(t_data *s, t_raycasting *ray, int img);
int				count_digit(char *str);

//									move
void			forward_and_back(t_raycasting *data, t_data *s);
void			left(t_raycasting *data, t_data *s);
void			right(t_raycasting *data, t_data *s);
void			rotate_left(t_raycasting *data);
void			rotate_right(t_raycasting *data);

#endif
