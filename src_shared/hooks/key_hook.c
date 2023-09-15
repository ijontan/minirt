/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:48:41 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 15:42:09 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_down_hook(int keycode, t_minirt *minirt)
{
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
	else if (keycode == KEY_Q)
		minirt->key_events.holding_q = true;
	else if (keycode == KEY_E)
		minirt->key_events.holding_e = true;
	else if (keycode == KEY_SP)
		minirt->moving = !minirt->moving;
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
	else if (keycode == KEY_Q)
		minirt->key_events.holding_q = false;
	else if (keycode == KEY_E)
		minirt->key_events.holding_e = false;
	return (0);
}
