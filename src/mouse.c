/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <bedavis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:44:24 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 12:40:09 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "key_map.h"

int			mouse_press(int key, int x, int y, t_fdf *fdf)
{
	x = y;
	if (key == MOUSE_SCROLL_UP)
		fdf->camera->zoom++;
	if (key == MOUSE_SCROLL_DOWN && fdf->camera->zoom > 1)
		fdf->camera->zoom--;
	if (key == MOUSE_LEFT_BUTTON)
		fdf->mouse->is_pressedl = 1;
	else if (key == MOUSE_RIGHT_BUTTON)
		fdf->mouse->is_pressedr = 1;
	draw(fdf->map, fdf);
	return (0);
}

int			mouse_release(int key, int x, int y, t_fdf *fdf)
{
	x = y;
	(void)key;
	if (fdf->mouse->is_pressedl)
		fdf->mouse->is_pressedl = 0;
	else if (fdf->mouse->is_pressedr)
		fdf->mouse->is_pressedr = 0;
	return (0);
}

int			mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->mouse->x0 = fdf->mouse->x1;
	fdf->mouse->y0 = fdf->mouse->y1;
	fdf->mouse->x1 = x;
	fdf->mouse->y1 = y;
	if (fdf->mouse->is_pressedl)
	{
		fdf->camera->beta += (x - fdf->mouse->x0) * 0.003;
		fdf->camera->alpha += (y - fdf->mouse->y0) * 0.003;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	else if (fdf->mouse->is_pressedr)
	{
		fdf->camera->x_shift += x - fdf->mouse->x0;
		fdf->camera->y_shift += y - fdf->mouse->y0;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	return (0);
}
