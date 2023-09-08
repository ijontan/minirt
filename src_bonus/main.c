/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:09 by itan              #+#    #+#             */
/*   Updated: 2023/09/08 20:44:31 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

static bool	check_min_requirements(t_parse parse_info)
{
	int	i;

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

void	gradient(t_image *image)
{
	int			x;
	int			y;
	t_color_c	start_color;
	t_color_c	end_color;
	t_color_c	color;
	double		opacity2;

	// double		opacity;
	start_color = color_correct((t_color)color_new(0, 0xf, 0xff, 0x00));
	end_color = color_correct((t_color)color_new(0, 0x00, 0xff, 0xff));
	color = color_tween(start_color, end_color, 0.5);
	y = 0;
	while (y < 720)
	{
		opacity2 = (double)y / (double)720;
		x = 0;
		while (x < 1280)
		{
			// opacity = (double)x / 1280;
			color = color_tween(start_color, end_color, opacity2);
			put_pixel(image, x, y, color_revert(color).as_int);
			x++;
		}
		y++;
	}
}

void	ray_cast(t_minirt *minirt)
{
	int			x;
	int			y;
	t_ray		ray;
	t_color_c	color;
	t_hit_info	hit_info;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			hit_info.material.color = color_correct_new(0, 0, 0, 0);
			ray = ray_primary(&minirt->cam, (((float)x - 280.0f) / 720 - 0.5)
				* minirt->cam.fov, ((float)y / 720 - 0.5) * minirt->cam.fov);
			hit_info = intersections(minirt, &ray);
			if (hit_info.hit)
			{
				color = hit_info.material.color;
				// color = phong_reflection(minirt, &hit_info);
				put_pixel(&minirt->image, x, y, color_revert(color).as_int);
			}
			x += 1;
		}
		y += 1;
	}
}

void	draw_scene(t_minirt *minirt)
{
	int				x;
	int				y;
	int				cycle;
	unsigned int	state;
	t_ray			ray;
	t_color_c		color;
	t_color_c		incoming_light;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			color = color_correct_new(0, 0, 0, 0);
			// incoming_light = color_correct_new(0, 0, 0, 0);
			// color = ray_tracing(&ray, minirt, &state);
			// incoming_light = ray_tracing(&ray, minirt, &state);
			// color = color_add(color, incoming_light);
			// incoming_light = ray_tracing(&ray, minirt, &state);
			// color = color_add(color, incoming_light);
			cycle = -1;
			state = (unsigned int)((x + y * 1280));
			while (++cycle < 50)
			{
				ray = ray_primary(&minirt->cam, (((float)x - 280.0f) / 720
						- 0.5) * minirt->cam.fov, ((float)y / 720 - 0.5)
					* minirt->cam.fov);
				incoming_light = ray_tracing(&ray, minirt, &state);
				color = color_add(color, incoming_light);
			}
			color = color_scale(color, 1 / (float)cycle);
			put_pixel(&minirt->image, x, y, color_revert(color).as_int);
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
	minirt.amb_light.material.emission_i = 0.01f;
	minirt.cam = p.camera;
	minirt.light_source = p.light_source;
	minirt.sphere = p.sphere;
	// minirt.sphere.center = vec3_new(-600, 0, 20);
	// minirt.sphere.radius = 100;
	minirt.sphere.material.emission_i = 0.1;
	minirt.sphere.material.emission = color_correct_new(0, 1, 1, 1);
	minirt.sphere.material.specular = color_correct_new(0, 1, 1, 1);
	minirt.sphere.material.specular_i = 0.001;
	minirt.sphere.material.shininess = 1.2;
	minirt.sphere.material.diffuse_i = 1;
	minirt.plane = p.plane;
	minirt.plane.material.emission_i = 0;
	minirt.plane.material.emission = color_correct_new(0, 0, 0, 0);
	minirt.plane.material.specular = color_correct_new(0, 1, 1, 1);
	minirt.plane.material.specular_i = 0.01;
	minirt.plane.material.shininess = 0.1;
	minirt.plane.material.diffuse_i = 0.1f;
	minirt.cylinder = p.cylinder;
	minirt.cylinder.material.emission_i = 0;
	minirt.cylinder.material.emission = color_correct_new(0, 1, 0, 0);
	minirt.cylinder.material.specular = color_correct_new(0, 1, 1, 1);
	minirt.cylinder.material.specular_i = 0.001;
	minirt.cylinder.material.shininess = 1;
	minirt.cylinder.material.diffuse_i = 0.1f;
	// rendering
	draw_scene(&minirt);
	printf("\e[0;32mRendering done!!! ~~\n\e[0m");
	// mlx rendering
	mlx_put_image_to_window(minirt.mlx, minirt.win, image.img, 0, 0);
	mlx_destroy_image(minirt.mlx, image.img);
	mlx_loop(minirt.mlx);
}

int	main(int ac, char **av)
{
	t_parse	parse_info;

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
