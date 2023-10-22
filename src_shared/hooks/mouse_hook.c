/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:44:19 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 13:16:43 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_opengl/mlx.h"
#include "minirt.h"
#include <stdio.h>

void select_object(t_offset xy, t_minirt *minirt)
{
	t_ray		ray;
	t_hit_info	info;

	ray = ray_primary(&minirt->cam, xy);
	info = intersect_list(minirt, &ray);
	minirt->selection.selected = info.object;
}

int	mouse_down_hook(int button, int x, int y, t_minirt *minirt)
{
	if (button == M_CLK_L && !minirt->moving)
		select_object((t_offset){.x = x, .y = y}, minirt);
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
	if (minirt->moving)
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
		minirt->mouse_events.prev_x = 300;
		minirt->mouse_events.prev_y = 300;
		mouse_move(minirt, 300, 300);
	}
	return (0);
}
