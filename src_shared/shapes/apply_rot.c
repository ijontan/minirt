/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:31:13 by itan              #+#    #+#             */
/*   Updated: 2023/11/03 15:38:03 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	apply_plane_rot(t_plane *plane, t_object *obj)
{
	t_quaternion	rot;

	quaternion_multiply(&obj->tmp_rotation, &obj->rotation, &rot);
	plane->rot_normal = vec3_normalize(vec3_apply_rot(plane->normal, rot));
}

static void	apply_cylinder_rot(t_cylinder *cylinder, t_object *obj)
{
	t_quaternion	rot;

	quaternion_multiply(&obj->tmp_rotation, &obj->rotation, &rot);
	cylinder->rot_axis = vec3_normalize(vec3_apply_rot(cylinder->norm_axis,
				rot));
}

static void	apply_cone_rot(t_cone *cone, t_object *obj)
{
	t_quaternion	rot;

	quaternion_multiply(&obj->tmp_rotation, &obj->rotation, &rot);
	cone->rot_axis = vec3_normalize(vec3_apply_rot(cone->norm_axis, rot));
}

void	apply_rot(void *object)
{
	t_object	*obj;
	void		*shape;

	obj = (t_object *)object;
	shape = obj->object;
	if (obj->type == PLANE)
		apply_plane_rot((t_plane *)shape, obj);
	if (obj->type == CYLINDER)
		apply_cylinder_rot((t_cylinder *)shape, obj);
	if (obj->type == CONE)
		apply_cone_rot((t_cone *)shape, obj);
}
