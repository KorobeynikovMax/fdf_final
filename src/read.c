/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:02:34 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 15:32:47 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			free_str_split(char **arr)
{
	size_t			i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static t_list_z		*new_elem(char *s, t_map *map)
{
	t_list_z		*coord;
	char			**parts;

	if (!(coord = (t_list_z *)ft_memalloc(sizeof(t_list_z))))
		fdf_exit("error: memory allocation for map reading.");
	if (!(parts = ft_strsplit(s, ',')))
		fdf_exit("error: splitting coordinates, while reading.");
	if (!check_number(parts[0]))
		fdf_exit("error: wrong map.");
	coord->z = ft_atoi(parts[0]);
	map->z_max = (coord->z > map->z_max) ? coord->z : map->z_max;
	map->z_min = (coord->z < map->z_min) ? coord->z : map->z_min;
	if (parts[1])
	{
		coord->color = ft_atoihex(parts[1]);
		map->is_colored = 1;
	}
	else
		coord->color = -1;
	coord->next = NULL;
	free_str_split(parts);
	return (coord);
}

static void			parse_line(char **coord_line, t_list_z **coordinates,
								t_map *map)
{
	int				width;

	width = 0;
	while (*coord_line)
	{
		list_put(coordinates, new_elem(*(coord_line++), map));
		width++;
	}
	if (map->height == 0)
		map->width = width;
	else if (map->width != width)
		fdf_exit("error: wrong map.");
}

void				read_file(int fd, t_list_z **coordinates, t_map *map)
{
	char			*line;
	int				r;
	char			**coord_line;

	line = NULL;
	while ((r = ft_get_next_line(fd, &line)) == 1)
	{
		if (!(coord_line = ft_strsplit(line, ' ')))
			fdf_exit("error: map reading.");
		parse_line(coord_line, coordinates, map);
		free_str_split(coord_line);
		ft_strdel(&line);
		map->height++;
	}
	if ((r == -1) || (!(*coordinates)))
		fdf_exit("error: map reading.");
}
