/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:22:28 by itan              #+#    #+#             */
/*   Updated: 2023/11/03 17:09:43 by itan             ###   ########.fr       */
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
	t_vec3		a;
	t_vec3		vec3;
	t_vec3		tmp;

	a = vec3_multiply(cylinder->rot_axis, cylinder->height * 0.5);
	vec3.x = cylinder->radius * sqrt(1 - cylinder->rot_axis.x
			* cylinder->rot_axis.x);
	vec3.y = cylinder->radius * sqrt(1 - cylinder->rot_axis.y
			* cylinder->rot_axis.y);
	vec3.z = cylinder->radius * sqrt(1 - cylinder->rot_axis.z
			* cylinder->rot_axis.z);
	bound_box.min = cylinder->center;
	bound_box.max = cylinder->center;
	tmp = vec3_subtract(cylinder->center, vec3_add(a, vec3));
	bound_box = bound_box_expand(bound_box, tmp);
	tmp = vec3_add(cylinder->center, vec3_add(a, vec3));
	bound_box = bound_box_expand(bound_box, tmp);
	tmp = vec3_subtract(cylinder->center, vec3_subtract(a, vec3));
	bound_box = bound_box_expand(bound_box, tmp);
	tmp = vec3_add(cylinder->center, vec3_subtract(a, vec3));
	bound_box = bound_box_expand(bound_box, tmp);
	return (bound_box);
}
// bound_box.min = vec3_new(-INFINITY, -INFINITY, -INFINITY);
// bound_box.max = vec3_new(INFINITY, INFINITY, INFINITY);

t_bound_box	get_cone_bound(t_cone *cone)
{
	t_bound_box	bound_box;
	t_vec3		a;
	t_vec3		vec3;
	t_vec3		tmp;

	a = vec3_multiply(cone->rot_axis, cone->height);
	vec3.x = cone->radius * sqrt(1 - cone->rot_axis.x * cone->rot_axis.x);
	vec3.y = cone->radius * sqrt(1 - cone->rot_axis.y * cone->rot_axis.y);
	vec3.z = cone->radius * sqrt(1 - cone->rot_axis.z * cone->rot_axis.z);
	bound_box.min = cone->tip;
	bound_box.max = cone->tip;
	tmp = vec3_add(cone->tip, vec3_add(a, vec3));
	bound_box = bound_box_expand(bound_box, tmp);
	tmp = vec3_add(cone->tip, vec3_subtract(a, vec3));
	bound_box = bound_box_expand(bound_box, tmp);
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
	obj->rotation = quaternion_create_id();
	obj->tmp_rotation = quaternion_create_id();
	get_bound(obj);
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
