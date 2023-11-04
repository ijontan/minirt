/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:48:41 by itan              #+#    #+#             */
/*   Updated: 2023/11/05 02:17:50 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	x_button_exit(int keycode, t_minirt *minirt)
{
	(void)keycode;
	(void)minirt;
	exit(EXIT_SUCCESS);
}

void	select_material_field(int keycode, t_minirt *minirt)
{
	t_selections	*selection;

	selection = &minirt->selection;
	if (keycode == KEY_1)
		selection->selected_material_field = MATERIAL_COLOR;
	else if (keycode == KEY_2)
		selection->selected_material_field = EMISSION_COLOR;
	else if (keycode == KEY_3)
		selection->selected_material_field = SPECULAR_COLOR;
	else if (keycode == KEY_4)
		selection->selected_material_field = DIFFUSE_INTENSITY;
	else if (keycode == KEY_5)
		selection->selected_material_field = SPECULAR_INTENSITY;
	else if (keycode == KEY_6)
		selection->selected_material_field = REFLECTIVE_INTENSITY;
	else if (keycode == KEY_7)
		selection->selected_material_field = EMISSION_INTENSITY;
	else if (keycode == KEY_8)
		selection->selected_material_field = SHININESS;
	else if (keycode == KEY_9)
		selection->selected_material_field = NOT_SELECTED;
	else if (keycode == KEY_0)
		selection->selected_material_field = NOT_SELECTED;
}

int	key_down_hook(int keycode, t_minirt *minirt)
{
	if (!minirt->moving && !minirt->selection.translation_plane)
		select_material_field(keycode, minirt);
	else
		minirt->selection.selected_material_field = NOT_SELECTED;
	update_selected_material(keycode, minirt);
	if (keycode == KEY_ESC)
	{
		free_minirt(minirt);
		exit(EXIT_SUCCESS);
	}
	if (keycode == KEY_UP && !minirt->selection.selected_material_field)
	{
		minirt->pixel_size += 1;
		render(minirt, &thread_init);
	}
	else if (keycode == KEY_DOWN && minirt->pixel_size > 1
		&& !minirt->selection.selected_material_field)
	{
		minirt->pixel_size -= 1;
		render(minirt, &thread_init);
	}
	if (keycode == KEY_1)
		minirt->key_events.holding_1 = true;
	else if (keycode == KEY_2)
		minirt->key_events.holding_2 = true;
	else if (keycode == KEY_3)
		minirt->key_events.holding_3 = true;
	else if (keycode == KEY_4)
		minirt->key_events.holding_4 = true;
	else if (keycode == KEY_5)
		minirt->key_events.holding_5 = true;
	else if (keycode == KEY_6)
		minirt->key_events.holding_6 = true;
	else if (keycode == KEY_7)
		minirt->key_events.holding_7 = true;
	else if (keycode == KEY_8)
		minirt->key_events.holding_8 = true;
	else if (keycode == KEY_9)
		minirt->key_events.holding_9 = true;
	else if (keycode == KEY_0)
		minirt->key_events.holding_0 = true;
	else if (keycode == KEY_UP)
		minirt->key_events.holding_up = true;
	else if (keycode == KEY_DOWN)
		minirt->key_events.holding_down = true;
	else if (keycode == KEY_LEFT)
		minirt->key_events.holding_left = true;
	else if (keycode == KEY_RIGHT)
		minirt->key_events.holding_right = true;
	else if (keycode == KEY_Q)
		minirt->key_events.holding_q = true;
	else if (keycode == KEY_E)
		minirt->key_events.holding_e = true;
	else if (keycode == KEY_W)
		minirt->key_events.holding_w = true;
	else if (keycode == KEY_S)
		minirt->key_events.holding_s = true;
	else if (keycode == KEY_A)
		minirt->key_events.holding_a = true;
	else if (keycode == KEY_D)
		minirt->key_events.holding_d = true;
	else if (keycode == KEY_R)
	{
		minirt->render_status = RENDER_CURRENT_SCENE;
		minirt->overlay_msg = "Rendering current scene";
		render_loading_overlay(minirt);
	}
	else if (keycode == KEY_Z)
		minirt->key_events.holding_z = true;
	else if (keycode == KEY_X)
		minirt->key_events.holding_x = true;
	else if (keycode == KEY_C)
		minirt->key_events.holding_c = true;
	else if (keycode == KEY_LSH)
		minirt->key_events.holding_lsh = true;
	else if (keycode == KEY_SP)
		minirt->key_events.holding_sp = true;
	else if (keycode == KEY_F)
	{
		minirt->moving = !minirt->moving;
		minirt->selection.selected = NULL;
		if (minirt->moving)
		{
			minirt->mouse_events.prev_x = -1;
			// minirt->mouse_events.prev_y = 300;
			mouse_move(minirt, minirt->cam.vp_width * 0.5, minirt->cam.vp_height
				* 0.5);
			mouse_hide(minirt);
		}
		else
		{
			minirt->mouse_events.prev_x = -1;
			mouse_show(minirt);
		}
	}
	return (0);
}

int	key_up_hook(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_1)
		minirt->key_events.holding_1 = false;
	else if (keycode == KEY_2)
		minirt->key_events.holding_2 = false;
	else if (keycode == KEY_3)
		minirt->key_events.holding_3 = false;
	else if (keycode == KEY_4)
		minirt->key_events.holding_4 = false;
	else if (keycode == KEY_5)
		minirt->key_events.holding_5 = false;
	else if (keycode == KEY_6)
		minirt->key_events.holding_6 = false;
	else if (keycode == KEY_7)
		minirt->key_events.holding_7 = false;
	else if (keycode == KEY_8)
		minirt->key_events.holding_8 = false;
	else if (keycode == KEY_9)
		minirt->key_events.holding_9 = false;
	else if (keycode == KEY_0)
		minirt->key_events.holding_0 = false;
	else if (keycode == KEY_UP)
		minirt->key_events.holding_up = false;
	else if (keycode == KEY_DOWN)
		minirt->key_events.holding_down = false;
	else if (keycode == KEY_LEFT)
		minirt->key_events.holding_left = false;
	else if (keycode == KEY_RIGHT)
		minirt->key_events.holding_right = false;
	else if (keycode == KEY_Q)
		minirt->key_events.holding_q = false;
	else if (keycode == KEY_E)
		minirt->key_events.holding_e = false;
	else if (keycode == KEY_W)
		minirt->key_events.holding_w = false;
	else if (keycode == KEY_S)
		minirt->key_events.holding_s = false;
	else if (keycode == KEY_A)
		minirt->key_events.holding_a = false;
	else if (keycode == KEY_D)
		minirt->key_events.holding_d = false;
	else if (keycode == KEY_Z)
		minirt->key_events.holding_z = false;
	else if (keycode == KEY_X)
		minirt->key_events.holding_x = false;
	else if (keycode == KEY_C)
		minirt->key_events.holding_c = false;
	else if (keycode == KEY_LSH)
		minirt->key_events.holding_lsh = false;
	else if (keycode == KEY_SP)
		minirt->key_events.holding_sp = false;
	return (0);
}
