/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 01:42:37 by itan              #+#    #+#             */
/*   Updated: 2023/11/05 02:12:19 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	update_color(t_color_c *color, int keycode, t_key_events key_events)
{
	if (key_events.holding_q && keycode == KEY_UP)
		color->r += 0.01;
	if (key_events.holding_w && keycode == KEY_UP)
		color->g += 0.01;
	if (key_events.holding_e && keycode == KEY_UP)
		color->b += 0.01;
	if (key_events.holding_q && keycode == KEY_DOWN)
		color->r -= 0.01;
	if (key_events.holding_w && keycode == KEY_DOWN)
		color->g -= 0.01;
	if (key_events.holding_e && keycode == KEY_DOWN)
		color->b -= 0.01;
	*color = color_clamp(*color);
}

static void	update_value(float *value, int keycode, t_vec3 step)
{
	if (keycode == KEY_UP)
		*value += step.x;
	if (keycode == KEY_DOWN)
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

static void	update_fields(t_minirt *minirt, t_material *material, int keycode,
		t_key_events key_events)
{
	if (minirt->selection.selected_material_field == MATERIAL_COLOR)
		update_color(&material->color, keycode, key_events);
	if (minirt->selection.selected_material_field == EMISSION_COLOR)
		update_color(&material->emission, keycode, key_events);
	if (minirt->selection.selected_material_field == SPECULAR_COLOR)
		update_color(&material->specular, keycode, key_events);
	if (minirt->selection.selected_material_field == DIFFUSE_INTENSITY)
		update_value(&material->diffuse_i, keycode, (t_vec3){.x = 0.01, .y = 0,
			.z = 1});
	if (minirt->selection.selected_material_field == SPECULAR_INTENSITY)
		update_value(&material->specular_i, keycode, (t_vec3){.x = 0.01, .y = 0,
			.z = 1});
	if (minirt->selection.selected_material_field == REFLECTIVE_INTENSITY)
		update_value(&material->reflective_i, keycode, (t_vec3){.x = 0.01,
			.y = 0, .z = 1});
	if (minirt->selection.selected_material_field == SHININESS)
		update_value(&material->shininess, keycode, (t_vec3){.x = 0.5, .y = 1,
			.z = 50});
	if (minirt->selection.selected_material_field == EMISSION_INTENSITY)
		update_value(&material->emission_i, keycode, (t_vec3){.x = 0.01, .y = 0,
			.z = 1});
}

void	update_selected_material(int keycode, t_minirt *minirt)
{
	t_object		*object;
	t_material		*material;
	t_key_events	key_events;

	if (!minirt->selection.selected_material_field)
		return ;
	object = minirt->selection.selected;
	key_events = minirt->key_events;
	if (!object)
		return ;
	material = get_material_ref(object);
	if (!material)
		return ;
	update_fields(minirt, material, keycode, key_events);
	render(minirt, thread_init);
}
