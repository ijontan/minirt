/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:48:41 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 18:28:31 by itan             ###   ########.fr       */
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
