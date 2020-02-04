/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedavis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:14:57 by bedavis           #+#    #+#             */
/*   Updated: 2020/02/04 15:20:03 by bedavis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			init_map(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->arr_coord = NULL;
	map->arr_color = NULL;
	map->z_min = 0;
	map->z_max = 1;
	map->is_colored = 0;
	map->c_press = 0;
}

void			init_fdf(t_fdf *fdf, t_map *map)
{
	if (!(fdf->mlx_ptr = mlx_init()))
		fdf_exit("error: fdf initialization.");
	if (!(fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"bedavis' FDF")))
		fdf_exit("error: fdf initialization.");
	if (!(fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		fdf_exit("error: fdf initialization.");
	fdf->data_addr = mlx_get_data_addr(fdf->img_ptr, &(fdf->bpp),
			&(fdf->size_line), &(fdf->endian));
	fdf->map = map;
	if (!(fdf->mouse = (t_mouse *)ft_memalloc(sizeof(t_mouse))))
		fdf_exit("error: fdf initialization, mouse.");
}

void			init_camera(t_fdf *fdf)
{
	t_camera *camera;

	if (!(camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
		fdf_exit("error: camera initialization.");
	camera->zoom = WIN_HEIGHT / fdf->map->height / 4;
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->z_factor = 1;
	camera->x_shift = 500;
	camera->y_shift = 300;
	camera->projection = ISO;
	fdf->camera = camera;
}

int				main(int argc, char **argv)
{
	int			fd;
	t_fdf		*fdf;
	t_map		*map;
	t_list_z	*listz;

	listz = NULL;
	if (argc != 2)
		fdf_exit("USAGE: ./fdf MAP_FILE.fdf");
	if (!(fd = open(argv[1], O_RDONLY)))
		fdf_exit("error: invalid file.");
	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		fdf_exit("error: can't initialize map.");
	init_map(map);
	read_file(fd, &listz, map);
	if (!(fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
		fdf_exit("error: fdf initialization.");
	init_fdf(fdf, map);
	make_arrays(&listz, map);
	init_camera(fdf);
	draw(map, fdf);
	hooks(fdf);
	mlx_loop(fdf->mlx_ptr);
	close(fd);
	return (0);
}
