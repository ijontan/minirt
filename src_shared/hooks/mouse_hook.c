/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:44:19 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 20:37:23 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int	mouse_down_hook(int button, int x, int y, t_minirt *minirt)
{
	minirt->mouse_events.prev_x = x;
	minirt->mouse_events.prev_y = y;
	if (button == M_CLK_L)
		minirt->mouse_events.holding_m_left = true;
	else if (button == M_CLK_R)
		minirt->mouse_events.holding_m_right = true;
	else if (button == M_CLK_M)
		minirt->mouse_events.holding_m_middle = true;
	return (0);
}

int	mouse_up_hook(int button, int x, int y, t_minirt *minirt)
{
	(void)x;
	(void)y;
	if (button == M_CLK_L)
		minirt->mouse_events.holding_m_left = false;
	else if (button == M_CLK_R)
		minirt->mouse_events.holding_m_right = false;
	else if (button == M_CLK_M)
		minirt->mouse_events.holding_m_middle = false;
	return (0);
}

int	mouse_move_hook(int x, int y, t_minirt *minirt)
{
	t_quaternion	rotation;

	(void)y;
	if (!minirt->moving)
		return (0);
	if (minirt->mouse_events.holding_m_left)
	{
		quaternion_y_rotation(-0.01 * (x - minirt->mouse_events.prev_x),
			&rotation);
		quaternion_multiply(&minirt->cam.rotation, &rotation,
			&minirt->cam.rotation);
		quaternion_x_rotation(-(y - minirt->mouse_events.prev_y) * 0.01,
			&rotation);
		quaternion_multiply(&minirt->cam.rotation, &rotation,
			&minirt->cam.rotation);
		quaternion_normalize(&minirt->cam.rotation, &minirt->cam.rotation);
		minirt->mouse_events.prev_x = x;
		minirt->mouse_events.prev_y = y;
	}
	return (0);
}
