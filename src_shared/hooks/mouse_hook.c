/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:44:19 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 15:55:29 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int	mouse_down_hook(int button, int x, int y, t_minirt *minirt)
{
	(void)x;
	(void)y;
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
	// t_image			image;
	(void)y;
	if (!minirt->moving)
		return (0);
	if (minirt->mouse_events.prev_x == 0)
		minirt->mouse_events.prev_x = x;
	if (minirt->mouse_events.prev_y == 0)
		minirt->mouse_events.prev_y = y;
	if (minirt->mouse_events.holding_m_left)
	{
		quaternion_x_rotation((x - minirt->mouse_events.prev_x) * 0.01,
			&minirt->cam.rotation);
		quaternion_y_rotation((y - minirt->mouse_events.prev_y) * -0.01,
			&minirt->cam.rotation);
	}
	return (0);
}
