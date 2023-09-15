/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:33 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 12:02:39 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	reflection(t_vec3 d_ray, t_vec3 normal)
{
	float	dot_prod;
	t_vec3	d_specular;

	dot_prod = vec3_dot(d_ray, normal) * 2;
	d_specular = vec3_multiply(normal, dot_prod);
	d_specular = vec3_subtract(d_ray, d_specular);
	d_specular = vec3_normalize(d_specular);
	if (vec3_dot(d_specular, normal) < 0.0f)
		d_specular = vec3_multiply(d_specular, -1.0f);
	return (d_specular);
}

t_color_c	get_color(t_minirt *rt, t_hit_info *hi)
{
	t_color_c	ret;
	t_color_c	tmp;
	t_pt_light	*pt_light;
	float		dot_prod;

	// t_vec3		reflected_ray;
	pt_light = (t_pt_light *)(rt->pt_lights->content);
	hi->pt_to_l = vec3_subtract(pt_light->position, hi->intersect_pt);
	hi->pt_to_cam = vec3_subtract(rt->cam.origin, hi->intersect_pt);
	hi->pt_to_l = vec3_normalize(hi->pt_to_l);
	hi->pt_to_cam = vec3_normalize(hi->pt_to_cam);
	dot_prod = vec3_dot(hi->pt_to_l, hi->normal);
	if (dot_prod < 0)
		dot_prod = 0;
	if (dot_prod > 1)
		dot_prod = 1;
	// printf("dot_prod: %f\n", dot_prod);
	tmp = color_scale(color_multiply(pt_light->material.color,
			hi->material.color), dot_prod);
	ret = tmp;
	dot_prod = vec3_dot(reflection(hi->pt_to_l, hi->normal), hi->pt_to_cam);
	if (dot_prod < 0)
		dot_prod = 0;
	if (dot_prod > 1)
		dot_prod = 1;
	tmp = color_scale(color_correct_new(0, 1, 1, 1), hi->material.specular_i
		* powf(dot_prod, hi->material.shininess));
	// tmp = color_scale(hi->material.specular, hi->material.specular_i
	// 	* powf(dot_prod, hi->material.shininess));
	ret = color_add(ret, tmp);
	tmp = rt->amb_light.color;
	tmp = color_scale(tmp, rt->amb_light.ratio);
	tmp = color_multiply(tmp, hi->material.color);
	ret = color_add(ret, tmp);
	// printf("ret: %f %f %f\n", ret.r, ret.g, ret.b);
	// hi->pt_to_l = vec3_subtract(pt_light->position,hi->intersect_pt);
	return (color_clamp(ret));
}

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

void	ray_cast(t_minirt *minirt)
{
	int			x;
	int			y;
	t_ray		ray;
	t_color_c	color;
	t_hit_info	hit_info;

	// printf("minirt->cam.origin: %f %f %f\n", minirt->cam.origin.x,
	// 		minirt->cam.origin.y, minirt->cam.origin.z);
	x = 0;
	while (x < 1280)
	{
		y = 0;
		while (y < 720)
		{
			ft_memset(&ray, 0, sizeof(t_ray));
			ray = ray_primary(&minirt->cam, (((float)x - 280.0f) / 720 - 0.5)
				* minirt->cam.fov, -(((float)y / 720 - 0.5)) * minirt->cam.fov);
			hit_info = intersect_list(minirt, &ray);
			color = color_correct_new(0, 0, 0, 0);
			if (hit_info.hit)
			{
				color = get_color(minirt, &hit_info);
				put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
					color_revert(color).as_int);
			}
			else
				put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
					color_revert(minirt->amb_light.color).as_int);
			++y;
		}
		++x;
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

	x = 0;
	while (x < 1280)
	{
		y = 0;
		while (y < 720)
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
				* minirt->cam.fov, -(((float)y / 720 - 0.5)) * minirt->cam.fov);
			while (++cycle < 10)
			{
				state = (unsigned int)((x + y * 1280 + cycle * 136274));
				offset.x = random_num(&state) - 0.5;
				offset.y = random_num(&state) - 0.5;
				offset.z = random_num(&state) - 0.5;
				offset = vec3_multiply(vec3_normalize(offset), 0.00015);
				ray.direction = vec3_add(ray.direction, offset);
				incoming_light = ray_tracing(ray, minirt, &state);
				color = color_add(color, incoming_light);
			}
			color = color_scale(color, 1 / (float)cycle);
			put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
				color_revert(color).as_int);
			++y;
		}
		++x;
	}
}

static void	init_minirt(t_parse p)
{
	t_image		image;
	t_minirt	minirt;

	// mlx and win
	ft_memset(&minirt, 0, sizeof(t_minirt));
	minirt.mlx = mlx_init();
	minirt.win = mlx_new_window(minirt.mlx, 1280, 720, "Hello world!");
	// images
	image.image = mlx_new_image(minirt.mlx, 1280, 720);
	image.buffer = mlx_get_data_addr(image.image, &image.pixel_bits,
			&image.line_bytes, &image.endian);
	minirt.image = image;

	// scene objects
	minirt.amb_light = p.amb_light;
	minirt.cam = p.camera;
	minirt.pt_lights = p.pt_lights;
	minirt.objects = p.objects;

	// rendering
	// ray_cast(&minirt);
	// draw_scene(&minirt);
	printf("\e[0;32mRendering done!!! ~~\n\e[0m");

	// loop hooks
	// render: found in the render dir
	mlx_loop_hook(minirt.mlx, render, &minirt);
	mlx_hook(minirt.win, 2, 1, key_down_hook, &minirt);
	mlx_hook(minirt.win, 17, 1, x_button_exit, &minirt);

	// mlx rendering
	mlx_put_image_to_window(minirt.mlx, minirt.win, image.image, 0, 0);
	mlx_destroy_image(minirt.mlx, image.image);
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
