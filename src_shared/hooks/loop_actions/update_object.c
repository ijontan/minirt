/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:54:45 by itan              #+#    #+#             */
/*   Updated: 2023/11/10 14:45:26 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_sphere(t_minirt *rt, t_key_events key_events)
{
	t_sphere	*sphere;

	sphere = rt->selection.selected->object;
	if (key_events.holding_v)
		update_value(&sphere->radius, key_events, (t_vec3){.x = 1, .y = 1,
			.z = 2000});
	else
		return ;
	rt->selection.selected->bounding_box = get_sphere_bound(sphere);
}

void	update_cylinder(t_minirt *rt, t_key_events key_events)
{
	t_cylinder	*cylinder;

	cylinder = rt->selection.selected->object;
	if (key_events.holding_v)
		update_value(&cylinder->radius, key_events, (t_vec3){.x = 1, .y = 1,
			.z = 2000});
	else if (key_events.holding_b)
		update_value(&cylinder->height, key_events, (t_vec3){.x = 1, .y = 1,
			.z = 2000});
	else
		return ;
	rt->selection.selected->bounding_box = get_cylinder_bound(cylinder);
}

void	update_cone(t_minirt *rt, t_key_events key_events)
{
	t_cone	*cone;

	cone = rt->selection.selected->object;
	if (key_events.holding_v)
		update_value(&cone->radius, key_events, (t_vec3){.x = 1, .y = 1,
			.z = 2000});
	else if (key_events.holding_b)
		update_value(&cone->height, key_events, (t_vec3){.x = 1, .y = 1,
			.z = 2000});
	else if (key_events.holding_n)
		update_value(&cone->diameter, key_events, (t_vec3){.x = 1, .y = 1,
			.z = 2000});
	else
		return ;
	cone->angle = atan(cone->radius / cone->height);
	cone->cos_squared = ft_power(cos(cone->angle), 2);
	rt->selection.selected->bounding_box = get_cone_bound(cone);
}

void	update_object(t_minirt *rt)
{
	t_key_events	key_events;

	key_events = rt->key_events;
	if (rt->selection.selected->type == SPHERE)
		update_sphere(rt, key_events);
	else if (rt->selection.selected->type == CYLINDER)
		update_cylinder(rt, key_events);
	else if (rt->selection.selected->type == CONE)
		update_cone(rt, key_events);
}
