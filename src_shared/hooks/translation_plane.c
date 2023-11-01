/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:13:01 by itan              #+#    #+#             */
/*   Updated: 2023/11/02 00:30:06 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_translation_plane(t_minirt *rt)
{
	t_plane	*plane;

	if ((!rt->key_events.holding_z && !rt->key_events.holding_x
			&& !rt->key_events.holding_c) || !rt->selection.selected
		|| rt->selection.translation_plane)
		return ;
	ft_printf("Adding translation plane: %x\n",
		rt->selection.translation_plane);
	plane = ft_calloc(1, sizeof(t_plane));
	if (rt->selection.selected->type == PLANE)
		plane->point_on_plane = ((t_plane *)(rt->selection.selected->object))->point_on_plane;
	else if (rt->selection.selected->type == SPHERE)
		plane->point_on_plane = ((t_sphere *)(rt->selection.selected->object))->center;
	else if (rt->selection.selected->type == CYLINDER)
		plane->point_on_plane = ((t_cylinder *)(rt->selection.selected->object))->center;
	else if (rt->selection.selected->type == CONE)
		plane->point_on_plane = ((t_cone *)(rt->selection.selected->object))->tip;
	if (rt->key_events.holding_z)
		plane->normalized_norm_vec = (t_vec3){.x = 0, .y = 1, .z = 0};
	else if (rt->key_events.holding_x)
		plane->normalized_norm_vec = (t_vec3){.x = 0, .y = 0, .z = 1};
	else if (rt->key_events.holding_c)
		plane->normalized_norm_vec = (t_vec3){.x = 1, .y = 0, .z = 0};
	rt->selection.translation_plane = plane;
	render(rt, &thread_init);
}

void	remove_translation_plane(t_minirt *rt)
{
	if (!rt->selection.translation_plane || rt->key_events.holding_z
		|| rt->key_events.holding_x || rt->key_events.holding_c)
		return ;
	ft_printf("Removing translation plane: %x\n",
		rt->selection.translation_plane);
	free(rt->selection.translation_plane);
	rt->selection.translation_plane = NULL;
	render(rt, &thread_init);
}
