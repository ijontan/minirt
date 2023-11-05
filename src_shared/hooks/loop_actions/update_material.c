/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 01:42:37 by itan              #+#    #+#             */
/*   Updated: 2023/11/05 22:02:57 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	update_color(t_color_c *color, t_key_events key_events)
{
	if (key_events.holding_q && key_events.holding_up)
		color->r += 0.01;
	if (key_events.holding_w && key_events.holding_up)
		color->g += 0.01;
	if (key_events.holding_e && key_events.holding_up)
		color->b += 0.01;
	if (key_events.holding_q && key_events.holding_down)
		color->r -= 0.01;
	if (key_events.holding_w && key_events.holding_down)
		color->g -= 0.01;
	if (key_events.holding_e && key_events.holding_down)
		color->b -= 0.01;
	*color = color_clamp(*color);
}

static void	update_value(float *value, t_key_events key_events, t_vec3 step)
{
	if (key_events.holding_up)
		*value += step.x;
	if (key_events.holding_down)
		*value -= step.x;
	if (*value < step.y)
		*value = step.y;
	else if (*value > step.z)
		*value = step.z;
}

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
			.y = 1, .z = 50});
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
	if (!minirt->selection.selected_material_field || (!key_events.holding_down
			&& !key_events.holding_up))
		return ;
	object = minirt->selection.selected;
	if (!object)
		return ;
	material = get_material_ref(object);
	if (!material)
		return ;
	update_fields(minirt, material, key_events);
	render(minirt, &thread_init);
}
