/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:09 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 14:32:46 by itan             ###   ########.fr       */
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
	double		opacity;

	// double		opacity2;
	x = 0;
	start_color = color_correct((t_color)color_new(0, 0xff, 0, 0xff));
	end_color = color_correct((t_color)color_new(0, 0, 0xff, 0xff));
	color = color_tween(start_color, end_color, 0.5);
	while (x < 1280)
	{
		y = 0;
		opacity = (double)x / 1280;
		while (y < 720)
		{
			// opacity2 = (double)y / (double)720;
			color = color_tween(start_color, end_color, opacity);
			put_pixel(image, x, y, color_revert(color).as_int);
			y++;
		}
		x++;
	}
}

void	ray_cast(t_image *image, t_cam *cam, t_sphere *sphere, t_offset offset)
{
	int			i;
	t_ray		ray;
	t_color_c	color;
	t_vec3		prev_intersect;
	t_vec3		intersect;

	prev_intersect = vec3_new(0, 0, 0);
	ray = ray_primary(cam, (((float)offset.x - 280.0f) / 720 - 0.5) * cam->fov,
		((float)offset.y / 720 - 0.5) * cam->fov);
	i = -1;
	while (++i < 10)
	{
		intersect = sphere_intersect(sphere + i, ray);
		// if (sphere_intersect(sphere, ray))
		if (intersect.z > 0)
		{
			if (prev_intersect.z == 0 || intersect.x < prev_intersect.x)
			{
				color = sphere[i].color;
				put_pixel(image, offset.x, offset.y,
					color_revert(color).as_int);
				prev_intersect = intersect;
			}
		}
	}
}

void	draw_scene(t_image *image, t_cam *cam, t_sphere *sphere)
{
	int	x;
	int	y;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			ray_cast(image, cam, sphere, (t_offset){x, y});
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
	t_sphere	sphere[10];
	t_color_c	start_color;
	t_color_c	end_color;
	t_color_c	color;

	end_color = color_correct((t_color)color_new(0, 0xff, 0, 0xff));
	start_color = color_correct((t_color)color_new(0, 0, 0xff, 0xff));
	for (size_t i = 0; i < 10; i++)
	{
		color = color_tween(start_color, end_color, (float)(10.0f + i) / 19);
		sphere[i] = sphere_new(vec3_new(-4.0f + i, 0, 5), 1, color);
	}
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
	draw_scene(&image, &cam, sphere);
	mlx_put_image_to_window(mlx, win, image.img, 0, 0);
	mlx_destroy_image(mlx, image.img);
	mlx_loop(mlx);
	return (0);
}
