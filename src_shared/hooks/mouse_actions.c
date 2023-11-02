/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:31:12 by itan              #+#    #+#             */
/*   Updated: 2023/11/02 15:54:56 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_objects(int x, int y, t_minirt *minirt)
{
	t_vec3		intersect;
	t_ray		ray;
	t_vec3		point;
	t_object	*object;

	if (!minirt->selection.translation_plane
		|| !minirt->mouse_events.holding_m_left)
		return ;
	ray = ray_primary(&minirt->cam, (t_offset){.x = x, .y = y});
	intersect = plane_intersect(minirt->selection.translation_plane, &ray);
	if (intersect.z <= 0 || intersect.x <= 0)
		return ;
	point = vec3_add(ray.origin, vec3_multiply(ray.direction, intersect.x));
	object = minirt->selection.selected;
	if (object->type == PLANE)
		((t_plane *)(object->object))->point_on_plane = point;
	else if (object->type == SPHERE)
		((t_sphere *)(object->object))->center = point;
	else if (object->type == CYLINDER)
		((t_cylinder *)(object->object))->center = point;
	else if (object->type == CONE)
		((t_cone *)(object->object))->tip = point;
	if (object->type == PLANE)
		object->bounding_box = get_plane_bound(object->object);
	else if (object->type == SPHERE)
		object->bounding_box = get_sphere_bound(object->object);
	else if (object->type == CYLINDER)
		object->bounding_box = get_cylinder_bound(object->object);
	else if (object->type == CONE)
		object->bounding_box = get_cone_bound(object->object);
}

// void rotate_objects(int x, int y, t_minirt*minirt)
// {

// }

void	rotate_cam(int x, int y, t_minirt *minirt)
{
	t_quaternion	rotation;

	if (!minirt->moving)
		return ;
	if (minirt->moving && minirt->mouse_events.prev_x != -1)
	{
		quaternion_y_rotation(-0.01 * (x - minirt->mouse_events.prev_x),
			&rotation);
		quaternion_multiply(&minirt->cam.rotation_h, &rotation,
			&minirt->cam.rotation_h);
		quaternion_x_rotation(-(y - minirt->mouse_events.prev_y) * 0.01,
			&rotation);
		quaternion_multiply(&minirt->cam.rotation_v, &rotation,
			&minirt->cam.rotation_v);
		quaternion_normalize(&minirt->cam.rotation_v, &minirt->cam.rotation_v);
		quaternion_normalize(&minirt->cam.rotation_h, &minirt->cam.rotation_h);
		minirt->mouse_events.prev_x = x;
		minirt->mouse_events.prev_y = y;
		// mouse_move(minirt, 300, 300);
	}
	if (minirt->mouse_events.prev_x == -1)
	{
		minirt->mouse_events.prev_x = x;
		minirt->mouse_events.prev_y = y;
	}
}
