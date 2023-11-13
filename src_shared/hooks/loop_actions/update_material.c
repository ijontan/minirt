/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 01:42:37 by itan              #+#    #+#             */
/*   Updated: 2023/11/10 19:19:41 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_material	*get_material_ref(t_object *object)
{
	if (object->type == SPHERE)
		return (&((t_sphere *)object->object)->material);
	else if (object->type == PLANE)
		return (&((t_plane *)object->object)->material);
	else if (object->type == CYLINDER)
		return (&((t_cylinder *)object->object)->material);
	else if (object->type == CONE)
		return (&((t_cone *)object->object)->material);
	return (NULL);
}

static void	update_fields(t_minirt *minirt, t_material *material,
		t_key_events key_events)
{
	if (minirt->selection.selected_material_field == MATERIAL_COLOR)
		update_color(&material->color, key_events);
	if (minirt->selection.selected_material_field == EMISSION_COLOR)
		update_color(&material->emission, key_events);
	if (minirt->selection.selected_material_field == SPECULAR_COLOR)
		update_color(&material->specular, key_events);
	if (minirt->selection.selected_material_field == DIFFUSE_INTENSITY)
		update_value(&material->diffuse_i, key_events, (t_vec3){.x = 0.01,
			.y = 0, .z = 1});
	if (minirt->selection.selected_material_field == SPECULAR_INTENSITY)
		update_value(&material->specular_i, key_events, (t_vec3){.x = 0.01,
			.y = 0, .z = 1});
	if (minirt->selection.selected_material_field == REFLECTIVE_INTENSITY)
		update_value(&material->reflective_i, key_events, (t_vec3){.x = 0.01,
			.y = 0, .z = 1});
	if (minirt->selection.selected_material_field == SHININESS)
		update_value(&material->shininess, key_events, (t_vec3){.x = 0.5,
			.y = 7, .z = 120});
	if (minirt->selection.selected_material_field == EMISSION_INTENSITY)
		update_value(&material->emission_i, key_events, (t_vec3){.x = 0.01,
			.y = 0, .z = 1});
}

void	update_selected_material(t_minirt *minirt)
{
	t_object		*object;
	t_material		*material;
	t_key_events	key_events;

	key_events = minirt->key_events;
	if ((!key_events.holding_down && !key_events.holding_up))
		return ;
	object = minirt->selection.selected;
	if (!object)
		return ;
	update_object(minirt);
	material = get_material_ref(object);
	if (!material)
		return ;
	if (minirt->selection.selected_material_field)
		update_fields(minirt, material, key_events);
	minirt->selected_obj_material = *material;
	render(minirt, &thread_init);
}
