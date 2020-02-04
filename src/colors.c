/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <bedavis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 10:52:40 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 15:49:08 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_colr(t_point point, t_point a, t_point b, t_point step)
{
	t_rgb	res;
	double	koef;

	if (point.color == b.color)
		return (point.color);
	if (step.x > step.y)
		koef = (double)(point.x - a.x) / (double)(b.x - a.x);
	else
		koef = (double)(point.y - a.y) / (double)(b.y - a.y);
	res.r = (int)((a.color >> 16 & 255) * (1 - koef) + (b.color >> 16 & 255) *
			koef);
	res.g = (int)((a.color >> 8 & 255) * (1 - koef) + (b.color >> 8 & 255) *
			koef);
	res.b = (int)((a.color >> 0 & 255) * (1 - koef) + (b.color >> 0 & 255) *
			koef);
	return ((res.b) | (res.g << 8) | (res.r << 16));
}
