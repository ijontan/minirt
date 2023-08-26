/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:09 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 03:50:10 by itan             ###   ########.fr       */
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

	// double	opacity;
	y = 0;
	start_color = color_correct((t_color)color_new(0, 0xff, 0xff, 0xff));
	end_color = color_correct((t_color)color_new(0, 0xff, 0xff, 0xff));
	color = color_tween(start_color, end_color, 0.5);
	while (y < 720)
	{
		x = 0;
		opacity2 = (double)y / (double)720;
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

void	draw_scene(t_image *image, t_cam *cam, t_sphere *sphere)
{
	int			x;
	int			y;
	t_color_c	color;
	t_ray		ray;

	// t_vec3		point;
	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			ray = ray_primary(cam, ((float)x - 280.0f) / 720 - 0.5, (float)y
					/ 720 - 0.5);
			color = sphere->color;
			// point = sphere_intersect(sphere, ray);
			// if (point.x != 0 || point.y != 0 || point.z != 0)
			if (sphere_intersect(sphere, ray))
				put_pixel(image, x, y, color_revert(color).as_int);
			x++;
		}
		y++;
	}
}

int	main(int ac, char const **av)
{
	void		*mlx;
	void		*win;
	t_image		image;
	t_cam		cam;
	t_sphere	sphere;

	sphere = sphere_new(vec3_new(0, 0, 5), 1,
			color_correct((t_color)color_new(0, 0xff, 0, 0)));
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
	gradient(&image);
	draw_scene(&image, &cam, &sphere);
	mlx_put_image_to_window(mlx, win, image.img, 0, 0);
	mlx_destroy_image(mlx, image.img);
	mlx_loop(mlx);
	return (0);
}
