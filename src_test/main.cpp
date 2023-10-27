
extern "C" {
	#include "minirt.h"
}
#include <chrono>
#include <iostream>
#include <map>
#include <string>

t_ht *ht_value = 0;
t_ht *ht_count = 0;
std::map<std::string, double>	m;
std::map<std::string, double>	m_count;

template <typename Ret, class... Args>
Ret	func_profile(std::string name,  Ret (*f)(...), Args... args)
{
	auto start = std::chrono::steady_clock::now();
	Ret ret = (*f)(args...);
	auto elapsed = std::chrono::steady_clock::now() - start;
	m[name] += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
	m_count[name] += 1;
	return (ret);
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

	// int			pixel_size;
	// int			i;
	// int			j;
	// pixel_size = 9;
	// printf("minirt->cam.origin: %f %f %f\n", minirt->cam.origin.x,
	// 		minirt->cam.origin.y, minirt->cam.origin.z);
	y = 0;
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			// if ((x % pixel_size != 0 || y % pixel_size != 0))
			// {
			// 	++x;
			// 	continue ;
			// }
			ft_memset(&ray, 0, sizeof(t_ray));
			ray = ray_primary(&minirt->cam, (t_offset){.x = x, .y = y});
			// hit_info = intersect_list(minirt, &ray);
			hit_info = func_profile<t_hit_info>("intersect_list", (t_hit_info (*)(...))&intersect_list, minirt, &ray);
			color = color_correct_new(0, 0, 0, 0);
			// color = func_profile<t_color_c>("color_correct_new", (t_color_c (*)(...))&color_correct_new, 0, 0, 0, 0);
			if (hit_info.hit)
			{
				color = get_color(minirt, &hit_info);
				// color = func_profile<t_color_c>("get_color", (t_color_c (*)(...))&get_color, minirt, &hit_info);
				put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
					color_revert(color).as_int);
			}
			else
				put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
					color_revert(minirt->amb_light.color).as_int);
			// i = -1;
			// while (minirt->moving && ++i < pixel_size && x + i < 1280)
			// {
			// 	j = -1;
			// 	while (++j < pixel_size && y + j < 720)
			// 	{
			// 		put_pixel(&minirt->image, (t_offset){.x = x + i, .y = y
			// 			+ j}, color_revert(color).as_int);
			// 	}
			// }
			++x;
		}
		++y;
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

	// t_vec3			offset;
	x = 0;
	while (x < 1280)
	{
		y = 0;
		while (y < 720)
		{
			printf("x: %d, y: %d\n", x, y);
			color = color_correct_new(0, 0, 0, 0);
			// incoming_light = color_correct_new(0, 0, 0, 0);
			// color = ray_tracing(&ray, minirt, &state);
			// incoming_light = ray_tracing(&ray, minirt, &state);
			// color = color_add(color, incoming_light);
			// incoming_light = ray_tracing(&ray, minirt, &state);
			// color = color_add(color, incoming_light);
			cycle = -1;
			ray = ray_primary(&minirt->cam, (t_offset){.x = x, .y = y});
			state = (unsigned int)((x + y * 1280));
			while (++cycle < 5)
			{
				// offset = vec3_multiply(random_vec3_hs(ray.direction, &state),
				// 	0.0005);
				// ray.direction = vec3_add(ray.direction, offset);
				// incoming_light = ray_tracing(ray, minirt, &state);
				incoming_light = func_profile<t_color_c>("ray_tracing", (t_color_c (*)(...))&ray_tracing, ray, minirt, &state);
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

void print_profiles(){
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		std::cout << it->first << "= total: " << it->second;
		std::cout << " calls: " << m_count[it->first];
		std::cout << " average: " << it->second / m_count[it->first] << '\n';
	}
}

void	init_minirt(t_parse p)
{
	t_minirt	minirt;

	// mlx and win
	ft_memset(&minirt, 0, sizeof(t_minirt));
	minirt.mlx = mlx_init();
	minirt.win = mlx_new_window(minirt.mlx, 1280, 720, "Hello world!");
	init_hooks(&minirt);
	minirt.pixel_size = 3;
	// scene objects
	minirt.amb_light = p.amb_light;
	minirt.cam = p.camera;
	minirt.pt_lights = p.pt_lights;
	minirt.objects = p.objects;
	// rendering
	// render(&minirt);
	// func_profile((auto (*)(...))&render, &minirt, &draw_scene);
	render(&minirt, &draw_scene);
	printf("\e[0;32mRendering done!!! ~~\n\e[0m");
	// loop hooks
	// render: found in the render dir
	// mlx_loop_hook(minirt.mlx, render, &minirt);
	// mlx_hook(minirt.win, 2, 1, key_down_hook, &minirt);
	// mlx_hook(minirt.win, 17, 1, x_button_exit, &minirt);
	// mlx rendering
	print_profiles();
	mlx_loop(minirt.mlx);
}

int	main(int ac, char *av[])
{
	t_parse	parse_info;

	ft_memset(&parse_info, 0, sizeof(t_parse));
	if (ac != 2)
		return (printf("\e[0;31mError: argument error\nExpected input format: ./minirt ~.rt\e[0m"));
	if (!parse_rt_file(av[1], &parse_info))
		return (1);
	printf("\e[0;32mParsing done!!! ~~\n\e[0m");
	init_minirt(parse_info);
	unsigned int state = 2;
	t_vec3 v = t_vec3{.x = 0, .y = 0, .z = 0};
	t_vec3 tmp;
	int n = 1000000;

	for (int i = 0; i < n; i++)
	{
		tmp = func_profile<t_vec3>("random_hs", (t_vec3 (*)(...))&random_vec3_hs, (t_vec3){.x=0, .y=0, .z=1}, &state);
		// std::cout << "tmp: " << tmp.x << " " << tmp.y << " " << tmp.z << '\n';
		v = vec3_add(v, tmp);
	}
	
	v = vec3_multiply(v, 1 / (float)n);
	std::cout << "v: " << v.x << " " << v.y << " " << v.z << '\n';
	print_profiles();
	(void)ac;
	(void)av;
	return (0);
}
