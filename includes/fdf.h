/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:07:30 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 16:44:03 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"
# include "key_map.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TEXT_COLOR 0xF3AF3D
# define TEXT_COLOR2 0xEAEAEA

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_list_z
{
	int				z;
	int				color;
	struct s_list_z	*next;
}					t_list_z;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct		s_map
{
	int				width;
	int				height;
	int				*arr_coord;
	int				*arr_color;
	int				z_min;
	int				z_max;
	int				is_colored;
	int				c_press;
}					t_map;

typedef	enum
{
	ISO,
	PARALLEL
}	t_projection;

typedef struct		s_camera
{
	t_projection	projection;
	int				zoom;
	double			alpha;
	double			beta;
	double			gamma;
	double			z_factor;
	int				x_shift;
	int				y_shift;
}					t_camera;

typedef struct		s_mouse
{
	int				is_pressedl;
	int				is_pressedr;
	int				x0;
	int				x1;
	int				y0;
	int				y1;
}					t_mouse;

typedef struct		s_fdf
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_addr;
	int				bpp;
	int				size_line;
	int				endian;
	t_camera		*camera;
	t_map			*map;
	t_mouse			*mouse;
}					t_fdf;

int					key_press(int key, t_fdf *fdf);
void				fdf_exit(char *reason);
void				read_file(int fd, t_list_z **coordinates, t_map *map);
void				list_put(t_list_z **coordinates, t_list_z *new);
t_list_z			*list_get(t_list_z **coordinates);
int					ft_atoihex(char *str);
void				make_arrays(t_list_z **cordinates, t_map *map);
void				draw_line(t_point a, t_point b, t_fdf *fdf);
void				draw(t_map *map, t_fdf *fdf);
void				print_usage(t_fdf *fdf);
void				init_camera(t_fdf *fdf);
t_point				make_point(int x, int y, t_map *map);
void				hooks(t_fdf *fdf);
int					mouse_press(int key, int x, int y, t_fdf *fdf);
int					mouse_release(int key, int x, int y, t_fdf *fdf);
int					mouse_move(int x, int y, t_fdf *fdf);
int					x_close(t_fdf *fdf);
void				isomet(int *x, int *y, int z);
t_point				p3d(t_point p, t_fdf *fdf);
int					get_colr(t_point point, t_point a, t_point b, t_point step);
int					check_number(char *str);

#endif
