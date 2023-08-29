/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:09 by itan              #+#    #+#             */
/*   Updated: 2023/08/29 15:48:44 by itan             ###   ########.fr       */
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
	start_color = color_correct((t_color)color_new(0, 0xff, 0x00, 0x00));
	end_color = color_correct((t_color)color_new(0, 0x00, 0x00, 0xff));
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
	int				x;
	int				y;
	int				cycle;
	unsigned int	state;
	t_ray			ray;
	t_color_c		color;
	t_color_c		incoming_light;
	t_hit_info		hit_info;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			cycle = 0;
			hit_info.material.color = color_correct_new(0, 0, 0, 0);
			ray = ray_primary(&minirt->cam, (((float)x - 280.0f) / 720 - 0.5)
				* minirt->cam.fov, ((float)y / 720 - 0.5) * minirt->cam.fov);
			incoming_light = color_correct_new(0, 0, 0, 0);
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
			cycle = 0;
			color = color_correct_new(0, 0, 0, 0);
			ray = ray_primary(&minirt->cam, (((float)x - 280.0f) / 720 - 0.5)
				* minirt->cam.fov, ((float)y / 720 - 0.5) * minirt->cam.fov);
			incoming_light = color_correct_new(0, 0, 0, 0);
			color = ray_tracing(&ray, minirt, &state);
			// while (++cycle < 2)
			// {
			// 	state = (unsigned int)((x + y * 1280) + cycle);
			// 	incoming_light = ray_tracing(&ray, minirt, &state);
			// 	color = color_multiply(color, incoming_light);
			// 	// color.a /= 2;
			// 	// color.r /= 2;
			// 	// color.g /= 2;
			// 	// color.b /= 2;
			// }
			// color = color_scale(color, 1.0f / (cycle + 1));
			put_pixel(&minirt->image, x, y, color_revert(color).as_int);
			x += 1;
		}
		y += 1;
	}
}

int	main(int ac, char const **av)
{
	void		*mlx;
	void		*win;
	t_image		image;
	t_cam		cam;
	t_sphere	sphere[10];
	t_color_c	start_color;
	t_color_c	end_color;
	t_material	material;
	t_light		light;
	t_minirt	minirt;

	end_color = color_correct((t_color)color_new(0, 0xff, 0, 0xff));
	start_color = color_correct((t_color)color_new(0, 0, 0xff, 0xff));
	for (size_t i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			material.emission_i = 1;
			material.color = color_correct_new(0, 0, 0, 0);
			material.emission = color_correct_new(0, 1, 1, 1);
			sphere[i] = sphere_new(vec3_new(0, 200, 200), 100.0f, material);
		}
		else if (i == 3)
		{
			material.emission_i = 0;
			material.color = color_correct_new(0, 1, 0.7, 0.5);
			material.emission = color_correct_new(0, 0, 0, 0);
			sphere[i] = sphere_new(vec3_new(0, -106, 50), 100.0f, material);
		}
		else
		{
			material.emission_i = 0;
			material.color = color_tween(start_color, end_color, (float)(10.0f
					+ i) / 19);
			material.emission = material.color;
			sphere[i] = sphere_new(vec3_new(-20.0f + i * 5, 0, 50), 2.0f
				+ (float)i / 3, material);
		}
	}
	minirt.cylinder->center = vec3_new(5, 0, 50);
	minirt.cylinder->radius = 5;
	minirt.cylinder->height = 3;
	minirt.cylinder->normalized_axis = vec3_normalize(vec3_new(2, 1, 0));
	material.emission_i = 0;
	material.color = color_correct_new(0, 1, 0, 0.8);
	material.emission = color_correct_new(0, 0, 0, 0);
	minirt.cylinder->material = material;
	// t_sphere	sphere;
	(void)ac;
	(void)av;
	cam_init(&cam);
	// sphere.center = vec3_new(0, 0, 5);
	// sphere.radius = 1;
	// sphere.color.rgba = color_new(0xff, 0, 0, 0xff);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1280, 720, "Hello world!");
	image.img = mlx_new_image(mlx, 1280, 720);
	image.buffer = mlx_get_data_addr(image.img, &image.pixel_bits,
		&image.line_bytes, &image.endian);
	light.color = color_correct((t_color)color_new(0, 0xff, 0xff, 0xff));
	light.origin = vec3_new(0, 5, 1);
	light.intensity = 1;
	minirt.image = image;
	minirt.mlx = mlx;
	minirt.win = win;
	minirt.cam = cam;
	minirt.key_events = (t_key_events){};
	minirt.mouse_events = (t_mouse_events){};
	minirt.light = light;
	for (size_t i = 0; i < 4; i++)
		minirt.sphere[i] = sphere[i];
	gradient(&minirt.image);
	draw_scene(&minirt);
	ft_printf("done");
	// mlx_hook(win, 2, 1L << 0, key_down_hook, &minirt);
	// mlx_hook(win, 3, 1L << 1, key_up_hook, &minirt);
	// mlx_hook(win, 4, 1L << 2, mouse_down_hook, &minirt);
	// mlx_hook(win, 5, 1L << 3, mouse_up_hook, &minirt);
	// mlx_hook(win, 6, 1L << 6, mouse_move_hook, &minirt);
	// mlx_loop_hook(mlx, loop_hook, &minirt);
	mlx_put_image_to_window(mlx, win, image.img, 0, 0);
	mlx_destroy_image(mlx, image.img);
	mlx_loop(mlx);
	return (0);
}
