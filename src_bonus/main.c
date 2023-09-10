/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:09 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 00:24:38 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

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
					* minirt->cam.fov, ((float)y / 720 - 0.5)
					* minirt->cam.fov);
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
	t_vec3			offset;
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
			ray = ray_primary(&minirt->cam, (((float)x - 280.0f) / 720 - 0.5)
					* minirt->cam.fov, -(((float)y / 720 - 0.5))
					* minirt->cam.fov);
			while (++cycle < 20)
			{
				state = (unsigned int)((x + y * 1280 + cycle * 136274));
				offset.x = random_num(&state) - 0.5;
				offset.y = random_num(&state) - 0.5;
				offset.z = random_num(&state) - 0.5;
				offset = vec3_multiply(vec3_normalize(offset), 0.0002);
				ray.direction = vec3_add(ray.direction, offset);
				incoming_light = ray_tracing(ray, minirt, &state);
				color = color_add(color, incoming_light);
			}
			color = color_scale(color, 1 / (float)cycle);
			put_pixel(&minirt->image, x, y, color_revert(color).as_int);
			++x;
		}
		++y;
	}
}

static void	init_minirt(void)
{
	t_image		image;
	t_minirt	minirt;
	t_sphere	*sphere;
	double		x;
	t_plane		*plane;

	// mlx and win
	minirt.mlx = mlx_init();
	minirt.win = mlx_new_window(minirt.mlx, 1280, 720, "Hello world!");
	// images
	image.img = mlx_new_image(minirt.mlx, 1280, 720);
	image.buffer = mlx_get_data_addr(image.img, &image.pixel_bits,
			&image.line_bytes, &image.endian);
	minirt.image = image;
	minirt.objects = NULL;
	cam_init(&minirt.cam);
	for (size_t i = 0; i < 5; i++)
	{
		x = (double)i / 4;
		sphere = malloc(sizeof(t_sphere));
		sphere->center = vec3_new(bazier_curves_1d_linear(x, (double[2]){-100,
					100}),
									0,
									200);
		sphere->radius = 20 * x + 20;
		sphere->material.color = color_tween(color_correct_new(0, 1, 1, 0),
												color_correct_new(0, 0, 1, 1),
												x);
		sphere->material.specular_i = 0;
		sphere->material.reflective_i = 0;
		sphere->material.emission = color_correct_new(0, 0, 0, 0);
		sphere->material.emission_i = 0;
		add_object(&minirt.objects, sphere, 0);
	}
	{
		sphere = malloc(sizeof(t_sphere));
		sphere->center = vec3_new(0, -500, 200);
		sphere->radius = 300;
		sphere->material.color = color_correct_new(0, 0, 0, 0);
		sphere->material.specular_i = 0;
		sphere->material.reflective_i = 0;
		sphere->material.emission = color_correct_new(0, 1, 1, 1);
		sphere->material.emission_i = 1;
		add_object(&minirt.objects, sphere, 0);
	}
	{
		plane = malloc(sizeof(t_plane));
		plane->point_on_plane = vec3_new(0, 40, 200);
		plane->normalized_norm_vec = vec3_new(0, 1, 0);
		plane->material.color = color_correct_new(0, 1, 1, 1);
		plane->material.specular_i = 0;
		plane->material.reflective_i = 0;
		plane->material.emission = color_correct_new(0, 1, 1, 1);
		plane->material.emission_i = 1;
		add_object(&minirt.objects, plane, 2);
	}
	// {
	// 	plane = malloc(sizeof(t_plane));
	// 	plane->point_on_plane = vec3_new(0, -40, 200);
	// 	plane->normalized_norm_vec = vec3_new(0, -1, 0);
	// 	plane->material.color = color_correct_new(0, 1, 1, 1);
	// 	plane->material.specular_i = 1;
	// 	plane->material.reflective_i = 1;
	// 	plane->material.emission = color_correct_new(0, 0, 0, 0);
	// 	plane->material.emission_i = 0;
	// 	add_object(&minirt.objects, plane, 2);
	// }
	{
		plane = malloc(sizeof(t_plane));
		plane->point_on_plane = vec3_new(120, 0, 0);
		plane->normalized_norm_vec = vec3_new(1, 0, 0);
		plane->material.color = color_correct_new(0, 0, 0, 1);
		plane->material.specular_i = 0;
		plane->material.reflective_i = 0;
		plane->material.emission = color_correct_new(0, 0, 0, 0);
		plane->material.emission_i = 0;
		add_object(&minirt.objects, plane, 2);
	}
	{
		plane = malloc(sizeof(t_plane));
		plane->point_on_plane = vec3_new(-120, 0, 0);
		plane->normalized_norm_vec = vec3_new(-1, 0, 0);
		plane->material.color = color_correct_new(0, 1, 0, 0);
		plane->material.specular_i = 0;
		plane->material.reflective_i = 0;
		plane->material.emission = color_correct_new(0, 0, 0, 0);
		plane->material.emission_i = 0;
		add_object(&minirt.objects, plane, 2);
	}
	// {
	// 	plane = malloc(sizeof(t_plane));
	// 	plane->point_on_plane = vec3_new(0, 0, 400);
	// 	plane->normalized_norm_vec = vec3_new(0, 0, 1);
	// 	plane->material.color = color_correct_new(0, 0, 1, 0);
	// 	plane->material.specular_i = 0;
	// 	plane->material.emission = color_correct_new(0, 0, 0, 0);
	// 	plane->material.emission_i = 0;
	// 	add_object(&minirt.objects, plane, 2);
	// }
	// {
	// 	plane = malloc(sizeof(t_plane));
	// 	plane->point_on_plane = vec3_new(0, 0, -10);
	// 	plane->normalized_norm_vec = vec3_new(0, 0, 1);
	// 	plane->material.color = color_correct_new(0, 1, 1, 1);
	// 	plane->material.specular_i = 0;
	// 	plane->material.emission = color_correct_new(0, 0, 0, 0);
	// 	plane->material.emission_i = 0;
	// 	add_object(&minirt.objects, plane, 2);
	// }
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
	(void)ac;
	(void)av;
	init_minirt();
	return (0);
}
