/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <bedavis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:45:16 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 15:47:21 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_usage2(t_fdf *fdf, void *mlx, void *win, int y)
{
	char *s;

	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Change projection: 'P'");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR,
			"Colorize, if it's not: 'C'");
	mlx_string_put(mlx, win, 5, y += 40, TEXT_COLOR,
			"----------------------------------------------");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR2,
			"Current Shift_X: ");
	s = ft_itoa(fdf->camera->x_shift);
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR2, s);
	ft_strdel(&s);
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR2, "Current Shift_Y: ");
	s = ft_itoa(fdf->camera->y_shift);
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR2, s);
	ft_strdel(&s);
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR2, "Current Zoom X: ");
	s = ft_itoa(fdf->camera->zoom);
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR2, s);
	ft_strdel(&s);
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR2, "Current Z-factor: ");
	s = ft_itoa((int)(fdf->camera->z_factor));
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR2, s);
	ft_strdel(&s);
}

void		print_usage(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = fdf->mlx_ptr;
	win = fdf->win_ptr;
	mlx_string_put(mlx, win, 65, y += 20, TEXT_COLOR, "Fdf's usage:");
	mlx_string_put(mlx, win, 15, y += 50, TEXT_COLOR,
			"Zoom: Scroll or '+' / '-'");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR,
			"Move: Arrows(Left, Right, Up, Down)");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Change Z: '<' / '>'");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR,
			"Alpha projection +/- '2'/'8'");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR,
			"Betta projection +/- '4'/'6'");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Gamma increase '1' '3'");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Gamma decrease '7' '9'");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR,
			"Use mouse Left button for changing projection");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR,
			"Use mouse Right button for moving");
	print_usage2(fdf, mlx, win, y);
}
