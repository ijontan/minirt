/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:33 by itan              #+#    #+#             */
/*   Updated: 2023/09/04 17:16:54 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Checks if all objects are present:
- ambient lighting
- camera
- lighting
- sphere
- plane
- cylinder
*/
static bool check_min_requirements(t_parse parse_info)
{	
	int i;

	i = -1;
	while (++i < 6)
	{
		if (!parse_info.mand_flag[i])
		{
			printf("\e[0;31mError: Missing Object: ");
			if (i == 0)
				printf("Ambient lighting required\e[0m");
			else if (i == 1)
				printf("Camera required\e[0m");
			else if (i == 2)
				printf("Lighting required\e[0m");
			else if (i == 3)
				printf("A sphere required\e[0m");
			else if (i == 4)
				printf("A plane required\e[0m");
			else if (i == 5)
				printf("A cylinder required\e[0m");
			return (false);
		}
	}
	return (true);
}

void	ray_cast(t_minirt *minirt)
{
	int				x;
	int				y;
	unsigned int	state;
	t_ray			ray;
	t_color_c		color;
	t_hit_info		hit_info;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			hit_info.material.color = color_correct_new(0, 0, 0, 0);
			ray = ray_primary(&minirt->cam, (((float)x - 280.0f) / 720 - 0.5)
				* minirt->cam.fov, ((float)y / 720 - 0.5) * minirt->cam.fov);
			hit_info = intersections(minirt, &ray, &state);
			if (hit_info.hit)
			{
				color = hit_info.material.color;
				put_pixel(&minirt->image, x, y, color_revert(color).as_int);
			}
			x += 1;
		}
		y += 1;
	}
}

static void	init_minirt(t_parse p)
{
	t_image		image;
	t_minirt	minirt;
	
	// mlx and win
	minirt.mlx = mlx_init();
	minirt.win = mlx_new_window(minirt.mlx, 1280, 720, "Hello world!");

	// images
	image.img = mlx_new_image(minirt.mlx, 1280, 720);
	image.buffer = mlx_get_data_addr(image.img, &image.pixel_bits,
		&image.line_bytes, &image.endian);
	minirt.image = image;

	// scene objects
	minirt.amb_light = p.amb_light;
	minirt.cam = p.camera;
	minirt.light_source = p.light_source;
	minirt.sphere = p.sphere;
	minirt.plane = p.plane;
	minirt.cylinder = p.cylinder;
	
	// rendering
	ray_cast(&minirt);
	printf("\e[0;32mRendering done!!! ~~\n\e[0m");

	// mlx rendering
	mlx_put_image_to_window(minirt.mlx, minirt.win, image.img, 0, 0);
	mlx_destroy_image(minirt.mlx, image.img);
	mlx_loop(minirt.mlx);
}

int	main(int ac, char **av)
{
	t_parse parse_info;

	if (ac != 2)
		return (printf("\e[0;31mError: argument error\nExpected input format: ./minirt ~.rt\e[0m"));
	if (!parse_rt_file(av[1], &parse_info))
		return (1);
	if (!check_min_requirements(parse_info))
		return (1);
	printf("\e[0;32mParsing done!!! ~~\n\e[0m");
	init_minirt(parse_info);
	return (0);
}
