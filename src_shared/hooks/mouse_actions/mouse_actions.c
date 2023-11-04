/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:31:12 by itan              #+#    #+#             */
/*   Updated: 2023/11/03 17:13:01 by itan             ###   ########.fr       */
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
		((t_plane *)(object->object))->center = point;
	else if (object->type == SPHERE)
		((t_sphere *)(object->object))->center = point;
	else if (object->type == CYLINDER)
		((t_cylinder *)(object->object))->center = point;
	else if (object->type == CONE)
		((t_cone *)(object->object))->tip = point;
	minirt->selection.translation_plane->center = point;
	get_bound(object);
}

void	init_rotation(t_offset xy, t_minirt *minirt)
{
	t_ray		ray;
	t_vec3		intersect;
	t_vec3		point;
	t_bound_box	bb;
	float		len;

	ray = ray_primary(&minirt->cam, xy);
	intersect = plane_intersect(minirt->selection.translation_plane, &ray);
	if (intersect.z <= 0 && intersect.x <= 0)
		return ;
	point = vec3_add(ray.origin, vec3_multiply(ray.direction, intersect.x));
	minirt->selection.rotation_plane = malloc(sizeof(t_plane));
	ft_memcpy(minirt->selection.rotation_plane,
		minirt->selection.translation_plane, sizeof(t_plane));
	bb = minirt->selection.selected->bounding_box;
	len = vec3_length(vec3_subtract(bb.max, bb.min));
	minirt->selection.rotation_plane->r = len * 0.5;
	minirt->selection.rotation_start = vec3_normalize(vec3_subtract(point,
				minirt->selection.rotation_plane->center));
	minirt->selection.angle = 0;
}

void	stop_rotation(t_minirt *minirt)
{
	t_object	*selected;

	selected = minirt->selection.selected;
	free(minirt->selection.rotation_plane);
	minirt->selection.rotation_plane = NULL;
	minirt->selection.rotation_start = (t_vec3){0, 0, 0};
	quaternion_multiply(&selected->tmp_rotation, &selected->rotation,
		&selected->rotation);
	selected->tmp_rotation = quaternion_create_id();
	minirt->selection.angle = 0;
}

void	calc_rotation(t_offset xy, t_minirt *minirt)
{
	t_vec3	rotation_end;
	t_vec3	intersect;
	t_ray	ray;

	if (!minirt->selection.rotation_plane
		|| !minirt->selection.translation_plane)
		return ;
	ray = ray_primary(&minirt->cam, xy);
	intersect = plane_intersect(minirt->selection.translation_plane, &ray);
	if (intersect.z <= 0 && intersect.x <= 0)
		return ;
	rotation_end = vec3_normalize(vec3_subtract(vec3_add(ray.origin,
					vec3_multiply(ray.direction, intersect.x)),
				minirt->selection.rotation_plane->center));
	minirt->selection.angle = acosf(vec3_dot(minirt->selection.rotation_start,
				rotation_end));
	intersect = vec3_cross(minirt->selection.rotation_start, rotation_end);
	if (vec3_dot(minirt->selection.rotation_plane->rot_normal, intersect) > 0)
		minirt->selection.angle *= -1;
	intersect = minirt->selection.rotation_plane->rot_normal;
	quaternion_from_axis_angle((double [3]){intersect.x, intersect.y,
		intersect.z}, minirt->selection.angle,
		&minirt->selection.selected->tmp_rotation);
	ft_lstiter(minirt->objects, apply_rot);
	get_bound(minirt->selection.selected);
}

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
