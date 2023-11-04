/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:48:41 by itan              #+#    #+#             */
/*   Updated: 2023/11/04 12:01:09 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	x_button_exit(int keycode, t_minirt *minirt)
{
	(void)keycode;
	(void)minirt;
	exit(EXIT_SUCCESS);
}

int	key_down_hook(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_ESC)
	{
		free_minirt(minirt);
		exit(EXIT_SUCCESS);
	}
	if (keycode == KEY_UP)
	{
		minirt->pixel_size += 1;
		render(minirt, &thread_init);
	}
	else if (keycode == KEY_DOWN && minirt->pixel_size > 1)
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
