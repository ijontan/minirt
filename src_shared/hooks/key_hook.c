/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:48:41 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 11:33:53 by rsoo             ###   ########.fr       */
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
		mlx_destroy_window(minirt->mlx, minirt->win);
		minirt->win = NULL;
		exit(EXIT_SUCCESS);
	}
	if (keycode == KEY_1)
		minirt->key_events.holding_1 = true;
	else if (keycode == KEY_2)
		minirt->key_events.holding_2 = true;
	else if (keycode == KEY_3)
		minirt->key_events.holding_3 = true;
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
	return (0);
}
