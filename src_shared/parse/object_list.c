/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:22:28 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 22:55:58 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bound_box	get_sphere_bound(t_sphere *sphere)
{
	t_bound_box	bound_box;

	bound_box.min = vec3_subtract(sphere->center, vec3_new(sphere->radius,
			sphere->radius, sphere->radius));
	bound_box.max = vec3_add(sphere->center, vec3_new(sphere->radius,
			sphere->radius, sphere->radius));
	return (bound_box);
}

t_bound_box	get_plane_bound(t_plane *plane)
{
	t_bound_box	bound_box;

	(void)plane;
	bound_box.min = vec3_new(-INFINITY, -INFINITY, -INFINITY);
	bound_box.max = vec3_new(INFINITY, INFINITY, INFINITY);
	return (bound_box);
}

t_bound_box	get_cylinder_bound(t_cylinder *cylinder)
{
	t_bound_box	bound_box;
	t_vec3		vec3;

	vec3 = vec3_multiply(cylinder->normalized_axis, cylinder->height * 0.5
		+ cylinder->radius * 2);
	bound_box.min = vec3_subtract(cylinder->center, vec3);
	bound_box.max = vec3_add(cylinder->center, vec3);
	bound_box.min = vec3_new(-INFINITY, -INFINITY, -INFINITY);
	bound_box.max = vec3_new(INFINITY, INFINITY, INFINITY);
	return (bound_box);
}

void	add_object(t_list **objects, void *object, unsigned char type)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		return ;
	obj->object = object;
	obj->type = type;
	if (type == SPHERE)
		obj->bounding_box = get_sphere_bound(object);
	else if (type == PLANE)
		obj->bounding_box = get_plane_bound(object);
	else if (type == CYLINDER)
		obj->bounding_box = get_cylinder_bound(object);
	ft_lstadd_front(objects, ft_lstnew(obj));
}

/*
do something

typedef void	(*t_ft)(void *);

eg1:
void	funtion(void *objects)
{
	t_object	*obj;
	const t_ft	fun_ptr[3];

	fun_ptr[3] = {&ft_example, &ft_example, &ft_example};
	obj = objects;
	fun_ptr[obj->type](obj->object);
}

use
ft_lstiter(objects, funtion);

eg2:
void	function(t_list *objects)
{
	t_object	*obj;
	const t_ft	fun_ptr[3];

	fun_ptr[3] = {&ft_example, &ft_example, &ft_example};
	while (objects)
	{
		obj = objects->content;
		fun_ptr[obj->type](obj->object);
		objects = objects->next;
	}
}
*/
