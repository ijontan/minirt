/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:09 by itan              #+#    #+#             */
/*   Updated: 2023/09/12 00:10:12 by itan             ###   ########.fr       */
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
			put_pixel(image, (t_offset){.x = x, .y = y},
					color_revert(color).as_int);
			x++;
		}
		y++;
	}
}

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
	float		dot_prod;

	// t_vec3		reflected_ray;
	hi->pt_to_l = vec3_subtract(rt->light_source.position, hi->intersect_pt);
	hi->pt_to_cam = vec3_subtract(rt->cam.origin, hi->intersect_pt);
	hi->pt_to_l = vec3_normalize(hi->pt_to_l);
	hi->pt_to_cam = vec3_normalize(hi->pt_to_cam);
	dot_prod = vec3_dot(hi->pt_to_l, hi->normal);
	if (dot_prod < 0)
		dot_prod = 0;
	if (dot_prod > 1)
		dot_prod = 1;
	// printf("dot_prod: %f\n", dot_prod);
	tmp = color_scale(color_multiply(rt->light_source.material.color,
										hi->material.color),
						dot_prod);
	ret = tmp;
	// dot_prod = vec3_dot(reflection(hi->pt_to_l, hi->normal), hi->pt_to_cam);
	// if (dot_prod < 0)
	// 	dot_prod = 0;
	// if (dot_prod > 1)
	// 	dot_prod = 1;
	// tmp = color_scale(material.specular, material.specular_i * powf(dot_prod,
	// 			material.shininess));
	// ret = color_add(ret, tmp);
	tmp = rt->amb_light.color;
	tmp = color_scale(tmp, rt->amb_light.ratio);
	tmp = color_multiply(tmp, hi->material.color);
	ret = color_add(ret, tmp);
	printf("ret: %f %f %f\n", ret.r, ret.g, ret.b);
	// hi->pt_to_l = vec3_subtract(rt->light_source.position,hi->intersect_pt);
	return (color_clamp(ret));
}

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
					* minirt->cam.fov, -(((float)y / 720 - 0.5))
					* minirt->cam.fov);
			hit_info = intersect_list(minirt, &ray);
			color = color_correct_new(0, 0, 0, 0);
			if (hit_info.hit)
			{
				color = hit_info.material.color;
				color = get_color(minirt, &hit_info);
				put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
						color_revert(color).as_int);
			}
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
					* minirt->cam.fov, -(((float)y / 720 - 0.5))
					* minirt->cam.fov);
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

static void	init_minirt(void)
{
	t_image		image;
	t_minirt	minirt;
	t_sphere	*sphere;
	double		x;
	t_plane		*plane;

	// mlx and win
	ft_memset(&minirt, 0, sizeof(t_minirt));
	minirt.mlx = mlx_init();
	minirt.win = mlx_new_window(minirt.mlx, 1280, 720, "Hello world!");
	// images
	image.img = mlx_new_image(minirt.mlx, 1280, 720);
	image.buffer = mlx_get_data_addr(image.img, &image.pixel_bits,
			&image.line_bytes, &image.endian);
	minirt.image = image;
	cam_init(&minirt.cam);
	minirt.light_source.position = vec3_new(0, 50, 200);
	minirt.light_source.material.color = color_correct_new(0, 1, 1, 1);
	minirt.light_source.ratio = 0.1;
	minirt.amb_light.color = color_correct_new(0, 1, 1, 1);
	minirt.amb_light.ratio = 0.1;
	minirt.objects = NULL;
	for (size_t i = 0; i < 5; i++)
	{
		x = (double)i / 4;
		sphere = malloc(sizeof(t_sphere));
		sphere->center = vec3_new(bazier_curves_1d_linear(x, (double[2]){-100,
					100}),
									0,
									200);
		sphere->radius = 20 * x + 20;
		ft_memset(&sphere->material, 0, sizeof(t_material));
		sphere->material.color = color_tween(color_correct_new(0, 1, 1, 0),
												color_correct_new(0, 0, 1, 1),
												x);
		// sphere->material.color = color_correct_new(0, 1, 1, 1);
		sphere->material.specular_i = 1;
		sphere->material.specular = color_correct_new(0, 1, 1, 1);
		sphere->material.reflective_i = 1;
		sphere->material.emission = color_correct_new(0, 0, 0, 0);
		sphere->material.emission_i = 0;
		sphere->material.diffuse_i = 1;
		sphere->material.shininess = 30;
		add_object(&minirt.objects, sphere, 0);
	}
	// {
	// 	sphere = malloc(sizeof(t_sphere));
	// 	sphere->center = vec3_new(0, 300, 200);
	// 	sphere->radius = 60;
	// 	sphere->material.color = color_correct_new(0, 0, 0, 0);
	// 	sphere->material.specular_i = 0;
	// 	sphere->material.reflective_i = 0;
	// 	sphere->material.emission = color_correct_new(0, 1, 1, 1);
	// 	sphere->material.emission_i = 1;
	// 	add_object(&minirt.objects, sphere, 0);
	// }
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
	{
		plane = malloc(sizeof(t_plane));
		plane->point_on_plane = vec3_new(0, -40, 200);
		plane->normalized_norm_vec = vec3_new(0, -1, 0);
		plane->material.color = color_correct_new(0, 1, 1, 1);
		plane->material.specular_i = 0;
		plane->material.reflective_i = 0;
		plane->material.emission = color_correct_new(0, 0, 0, 0);
		plane->material.emission_i = 0;
		add_object(&minirt.objects, plane, 2);
	}
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
