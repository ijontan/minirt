/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_holding_down.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:07:04 by itan              #+#    #+#             */
/*   Updated: 2023/11/05 22:12:12 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	keydown_numbers(int keycode, t_minirt *minirt)
{
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
}

void	keydown_arrows(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_UP)
		minirt->key_events.holding_up = true;
	else if (keycode == KEY_DOWN)
		minirt->key_events.holding_down = true;
	else if (keycode == KEY_LEFT)
		minirt->key_events.holding_left = true;
	else if (keycode == KEY_RIGHT)
		minirt->key_events.holding_right = true;
}

void	keydown_char(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_Q)
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
	else if (keycode == KEY_Z)
		minirt->key_events.holding_z = true;
	else if (keycode == KEY_X)
		minirt->key_events.holding_x = true;
	else if (keycode == KEY_C)
		minirt->key_events.holding_c = true;
}

void	keydown_others(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_LSH)
		minirt->key_events.holding_lsh = true;
	else if (keycode == KEY_SP)
		minirt->key_events.holding_sp = true;
	else if (keycode == KEY_R)
	{
		minirt->render_status = RENDER_CURRENT_SCENE;
		minirt->overlay_msg = "Rendering current scene";
		render_loading_overlay(minirt);
	}
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
}

void	key_holding_down(int keycode, t_minirt *minirt)
{
	keydown_numbers(keycode, minirt);
	keydown_arrows(keycode, minirt);
	keydown_char(keycode, minirt);
	keydown_others(keycode, minirt);
}
