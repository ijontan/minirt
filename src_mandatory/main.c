/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:33 by itan              #+#    #+#             */
/*   Updated: 2023/09/13 09:49:21 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_pixel(t_minirt *minirt, t_hit_info hit_info, int x, int y)
{
	t_color_c	color;

	if (hit_info.hit)
	{
		color = hit_info.material.color;
		put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
				color_revert(color).as_int);
		return ;
	}
	color.r = minirt->amb_light.color.r * minirt->amb_light.ratio;
	color.g = minirt->amb_light.color.g * minirt->amb_light.ratio;
	color.b = minirt->amb_light.color.b * minirt->amb_light.ratio;
	put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
			color_revert(color).as_int);
}

/*
perfect reflection: vector that represents the reflection of an incident ray 
(d - 2(d.n)n) where d is the intersection vector and n is the surface normal

dot_prod: represents cos(theta), with range: 0.0 - 1.0

amb_color: the color of the object after ambient light is applied (object color
		* amb_light color)

- ambient: if the cos(theta) is < 0, meaning theta is obtuse,
	then apply the ambient light
- specular: if the cos(theta) is 0.5 < <= 1.0,
	color tween from obj color to a bright color
- diffuse: if the cos(theta) is <= 0.5, color tween from dark color to obj color

*/
void	calculate_lighting(t_minirt *minirt, t_hit_info *hit_info)
{
	t_vec3		perfect_reflection;
	t_vec3		intersect_to_light;
	float		dot_prod;
	t_color_c	amb_color;

	if (hit_info->obj_type != SPHERE)
		return ;
	perfect_reflection = vec3_subtract(hit_info->intersect_pt,
										vec3_multiply(hit_info->normal,
														vec3_dot(hit_info->intersect_pt,
																hit_info->normal)
																*
															2));
	perfect_reflection = vec3_normalize(perfect_reflection);
	intersect_to_light = vec3_normalize(vec3_subtract(minirt->light_source.position,
														hit_info->intersect_pt));
	dot_prod = vec3_dot(perfect_reflection, intersect_to_light);
	amb_color = color_multiply(hit_info->material.color,
								minirt->amb_light.color);
	if (dot_prod < 0)
	{
		hit_info->material.color = amb_color;
		return ;
	}
	if (dot_prod > 0.5 && dot_prod <= 1)
		hit_info->material.color = color_tween(color_correct_new(0, 0.6, 0.6,
					0.6), hit_info->material.color, (1 - dot_prod) * 10);
	else if (dot_prod <= 0.5)
	{
		hit_info->material.color = color_tween(color_correct_new(0, 0, 0, 0),
												hit_info->material.color,
												dot_prod);
		hit_info->material.color = color_add(hit_info->material.color,
												amb_color);
	}
}

void	ray_cast(t_minirt *minirt)
{
	int			x;
	int			y;
	t_ray		ray;
	t_hit_info	hit_info;

	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			// printf("x: %d, y: %d\n", x, y);
			hit_info.material.color = color_correct_new(0, 0, 0, 0);
			ray = ray_primary(&minirt->cam, (((float)x - 280.0f) / 720 - 0.5)
					* minirt->cam.fov, ((float)y / 720 - 0.5)
					* minirt->cam.fov);
			hit_info = intersections(minirt, &ray);
			// hit_info.material.color = phong_reflection(minirt, &hit_info);
			// calculate_lighting(minirt, &hit_info);
			set_pixel(minirt, hit_info, x, y);
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
	// minirt.sphere = p.objects;
	// minirt.plane = p.plane;
	// minirt.cylinder = p.cylinder;
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
	t_parse	parse_info;

	if (ac != 2)
		return (printf("\e[0;31mError: argument error\nExpected input format: ./minirt ~.rt\e[0m"));
	if (!parse_rt_file(av[1], &parse_info))
		return (1);
	printf("\e[0;32mParsing done!!! ~~\n\e[0m");
	init_minirt(parse_info);
	return (0);
}
