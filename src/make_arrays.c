/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arrays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <bedavis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:02:00 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 15:31:58 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			make_arrays(t_list_z **cordinates, t_map *map)
{
	t_list_z	*coord;
	size_t		i;
	size_t		arr_size;

	arr_size = map->width * map->height * sizeof(int);
	if (!(map->arr_coord = (int *)ft_memalloc(arr_size)))
		fdf_exit("error: coordinates creation.");
	if (!(map->arr_color = (int *)ft_memalloc(arr_size)))
		fdf_exit("error: coordinates creation.");
	i = map->width * map->height - 1;
	while ((coord = list_get(cordinates)))
	{
		map->arr_coord[i] = coord->z;
		map->arr_color[i] = coord->color;
		if (coord->z > map->z_max)
			map->z_max = coord->z;
		if (coord->z < map->z_min)
			map->z_min = coord->z;
		i--;
		free(coord);
	}
}

static int		simple_grad(double x)
{
	if (x <= 0.1)
		return (139);
	if (x <= 0.2)
		return (255);
	if (x <= 0.3)
		return (49151);
	if (x <= 0.4)
		return (11591910);
	if (x <= 0.5)
		return (25600);
	if (x <= 0.6)
		return (3329330);
	if (x <= 0.7)
		return (15787660);
	if (x <= 0.8)
		return (12433259);
	if (x <= 0.9)
		return (12092939);
	return (9127187);
}

t_point			make_point(int x, int y, t_map *map)
{
	t_point		new;
	int			i;

	i = y * map->width + x;
	new.x = x;
	new.y = y;
	new.z = map->arr_coord[i];
	if (map->is_colored == 1)
		new.color = map->arr_color[i];
	else if (!map->c_press)
		new.color = 16777215;
	else
		new.color = simple_grad((double)(new.z - map->z_min) / (double)
		(map->z_max - map->z_min));
	return (new);
}
