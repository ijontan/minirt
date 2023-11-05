/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hollding_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:14:42 by itan              #+#    #+#             */
/*   Updated: 2023/11/05 22:18:32 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	keyup_numbers(int keycode, t_minirt *minirt)
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
}

void	keyup_arrows(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_UP)
		minirt->key_events.holding_up = false;
	else if (keycode == KEY_DOWN)
		minirt->key_events.holding_down = false;
	else if (keycode == KEY_LEFT)
		minirt->key_events.holding_left = false;
	else if (keycode == KEY_RIGHT)
		minirt->key_events.holding_right = false;
}

void	keyup_char(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_Q)
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
}

void	keyup_others(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_LSH)
		minirt->key_events.holding_lsh = false;
	else if (keycode == KEY_SP)
		minirt->key_events.holding_sp = false;
}

void	key_holding_up(int keycode, t_minirt *minirt)
{
	keyup_numbers(keycode, minirt);
	keyup_arrows(keycode, minirt);
	keyup_char(keycode, minirt);
	keyup_others(keycode, minirt);
}