/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:13:01 by itan              #+#    #+#             */
/*   Updated: 2023/11/02 14:54:35 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_trnslt_pl_pt(t_minirt *rt)
{
	t_vec3	ret;

	ret = (t_vec3){.x = 0, .y = 0, .z = 0};
	if (rt->selection.selected->type == PLANE)
		ret = ((t_plane *)(rt->selection.selected->object))->point_on_plane;
	else if (rt->selection.selected->type == SPHERE)
		ret = ((t_sphere *)(rt->selection.selected->object))->center;
	else if (rt->selection.selected->type == CYLINDER)
		ret = ((t_cylinder *)(rt->selection.selected->object))->center;
	else if (rt->selection.selected->type == CONE)
		ret = ((t_cone *)(rt->selection.selected->object))->tip;
	return (ret);
}

void	add_translation_plane(t_minirt *rt)
{
	t_plane	*plane;
	t_vec3	value;

	value = (t_vec3){.x = 1, .y = 1, .z = 1};
	if ((!rt->key_events.holding_z && !rt->key_events.holding_x
			&& !rt->key_events.holding_c) || !rt->selection.selected
		|| rt->selection.translation_plane)
		return ;
	plane = ft_calloc(1, sizeof(t_plane));
	plane->point_on_plane = get_trnslt_pl_pt(rt);
	if (plane->point_on_plane.x < rt->cam.origin.x + rt->cam.position.x)
		value.x = -1;
	if (plane->point_on_plane.y < rt->cam.origin.y + rt->cam.position.y)
		value.y = -1;
	if (plane->point_on_plane.z < rt->cam.origin.x + rt->cam.position.z)
		value.z = -1;
	if (rt->key_events.holding_z)
		plane->normalized_norm_vec = (t_vec3){.x = 0, .y = value.y, .z = 0};
	else if (rt->key_events.holding_x)
		plane->normalized_norm_vec = (t_vec3){.x = 0, .y = 0, .z = value.z};
	else if (rt->key_events.holding_c)
		plane->normalized_norm_vec = (t_vec3){.x = value.x, .y = 0, .z = 0};
	rt->selection.translation_plane = plane;
}

void	remove_translation_plane(t_minirt *rt)
{
	if (!rt->selection.translation_plane || rt->key_events.holding_z
		|| rt->key_events.holding_x || rt->key_events.holding_c)
		return ;
	free(rt->selection.translation_plane);
	rt->selection.translation_plane = NULL;
	render(rt, &thread_init);
}
