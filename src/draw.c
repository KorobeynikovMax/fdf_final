/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <bedavis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:52:00 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 16:01:28 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	my_abs(t_point a, t_point b)
{
	t_point		step;

	if ((b.x - a.x) < 0)
		step.x = a.x - b.x;
	else
		step.x = b.x - a.x;
	if ((b.y - a.y) < 0)
		step.y = a.y - b.y;
	else
		step.y = b.y - a.y;
	return (step);
}

static void		put_pixel(int x, int y, int color, t_fdf *fdf)
{
	int			i;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		i = (x * fdf->bpp / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

/*
** Bresenham's line algorithm
*/

void			draw_line(t_point a, t_point b, t_fdf *fdf)
{
	t_point		step;
	t_point		point;
	t_point		sign;
	t_point		error;

	step = my_abs(a, b);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	error.x = step.x - step.y;
	point = a;
	while ((point.x != b.x) || (point.y != b.y))
	{
		put_pixel(point.x, point.y, get_colr(point, a, b, step), fdf);
		error.y = error.x * 2;
		if (error.y > -step.y)
		{
			error.x = error.x - step.y;
			point.x += sign.x;
		}
		if (error.y < step.x)
		{
			error.x = error.x + step.x;
			point.y += sign.y;
		}
	}
}

void			draw(t_map *map, t_fdf *fdf)
{
	int			x;
	int			y;

	y = 0;
	ft_bzero(fdf->data_addr, WIN_WIDTH * WIN_HEIGHT * (fdf->bpp / 8));
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
				draw_line(p3d(make_point(x, y, map), fdf), p3d(make_point(x +
				1, y, map), fdf), fdf);
			if (y < map->height - 1)
				draw_line(p3d(make_point(x, y, map), fdf), p3d(make_point(x, y
				+ 1, map), fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	print_usage(fdf);
}
