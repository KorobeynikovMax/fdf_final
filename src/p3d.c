/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <bedavis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 09:57:10 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 14:46:18 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		isomet(int *x, int *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

static void	rotate_x(int *y, int *z, double alpha)
{
	int y0;

	y0 = *y;
	*y = y0 * cos(alpha) + *z * sin(alpha);
	*z = -y0 * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double beta)
{
	int x0;

	x0 = *x;
	*x = x0 * cos(beta) + *z * sin(beta);
	*z = -x0 * sin(beta) + *z * cos(beta);
}

static void	rotate_z(int *x, int *y, double gamma)
{
	int x0;
	int y0;

	x0 = *x;
	y0 = *y;
	*x = x0 * cos(gamma) - y0 * sin(gamma);
	*y = x0 * sin(gamma) + y0 * cos(gamma);
}

t_point		p3d(t_point p, t_fdf *fdf)
{
	p.x *= fdf->camera->zoom;
	p.y *= fdf->camera->zoom;
	p.z *= (int)(fdf->camera->zoom * fdf->camera->z_factor);
	p.x -= (fdf->map->width * fdf->camera->zoom) / 8;
	p.y -= (fdf->map->height * fdf->camera->zoom) / 8;
	rotate_x(&p.y, &p.z, fdf->camera->alpha);
	rotate_y(&p.x, &p.z, fdf->camera->beta);
	rotate_z(&p.x, &p.y, fdf->camera->gamma);
	if (fdf->camera->projection == ISO)
		isomet(&p.x, &p.y, p.z);
	p.x += (WIN_WIDTH) / 8 + fdf->camera->x_shift;
	p.y += (WIN_HEIGHT + fdf->map->height * fdf->camera->zoom) / 8 +
			fdf->camera->y_shift;
	return (p);
}
