/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:33 by itan              #+#    #+#             */
/*   Updated: 2023/10/27 04:39:54 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	list_iter(t_list *lst, t_minirt *rt, void (*f)(t_minirt *, void *))
{
	while (lst)
	{
		f(rt, lst->content);
		lst = lst->next;
	}
}

void	load_texture(t_minirt *rt, void *content)
{
	t_object	*obj;
	t_material	*mt;
	t_image		*img;

	obj = (t_object *)content;
	if (obj->type == SPHERE)
		mt = &((t_sphere *)obj->object)->material;
	else if (obj->type == PLANE)
		mt = &((t_plane *)obj->object)->material;
	else if (obj->type == CYLINDER)
		mt = &((t_cylinder *)obj->object)->material;
	else
		return ;
	if (mt->texture_path)
	{
		img = ft_calloc(1, sizeof(t_image));
		*img = load_image(rt, "rt_files/textures/earth.xpm");
		mt->texture = img;
	}
	if (mt->norm_map_path)
	{
		img = ft_calloc(1, sizeof(t_image));
		*img = load_image(rt, "rt_files/textures/earth_norm.xpm");
		mt->norm_map = img;
	}
}

void	init_minirt(t_parse p)
{
	t_minirt	minirt;

	ft_memset(&minirt, 0, sizeof(t_minirt));
	minirt.mlx = mlx_init();
	minirt.win = mlx_new_window(minirt.mlx, 1280, 720, "Hello world!");
	init_hooks(&minirt);
	minirt.pixel_size = 3;
	minirt.amb_light = p.amb_light;
	minirt.cam = p.camera;
	minirt.pt_lights = p.pt_lights;
	minirt.objects = p.objects;
	minirt.outline_color = color_correct_new(0, 1, 1, 0);
	list_iter(minirt.objects, &minirt, &load_texture);
	render(&minirt, &ray_cast);
	printf("\e[0;32mRendering done!!! ~~\n\e[0m");
	mlx_loop(minirt.mlx);
}

int	main(int ac, char **av)
{
	t_parse	parse_info;

	ft_memset(&parse_info, 0, sizeof(t_parse));
	if (ac != 2)
		return (printf("\e[0;31mError: argument error\nExpected input format: ./minirt ~.rt\e[0m"));
	if (!parse_rt_file(av[1], &parse_info))
		return (1);
	printf("\e[0;32mParsing done!!! ~~\n\e[0m");
	init_minirt(parse_info);
	(void)ac;
	(void)av;
	return (0);
}
