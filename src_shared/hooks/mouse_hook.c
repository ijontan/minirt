/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:44:19 by itan              #+#    #+#             */
/*   Updated: 2023/11/03 10:22:27 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_opengl/mlx.h"
#include "minirt.h"
#include <stdio.h>

void	select_object(t_offset xy, t_minirt *minirt)
{
	t_ray		ray;
	t_hit_info	info;

	ray = ray_primary(&minirt->cam, xy);
	info = intersect_list(minirt, &ray);
	minirt->selection.selected = info.object;
	render(minirt, &thread_init);
}

int in_rt_file_position(int x, int y, t_minirt *minirt)
{
	int i;

	i = -1;
	while (++i < minirt->file_num)
		if (minirt->rt_files[i].top_left.y <= y && \
			y <= minirt->rt_files[i].bottom_right.y && \
			minirt->rt_files[i].top_left.x <= x && \
			x <= minirt->rt_files[i].bottom_right.x)
			return i;
	return -1;
}

int	mouse_down_hook(int button, int x, int y, t_minirt *minirt)
{
	if (button == M_CLK_L && !minirt->moving)
		select_object((t_offset){.x = x, .y = y}, minirt);
	if (button == M_CLK_L && x < MENU_WIDTH)
	{
		minirt->file_ind = in_rt_file_position(x, y, minirt);
		if (minirt->file_ind > -1)
		{
			minirt->render_status = RENDER_NEW_SCENE;
			minirt->rt_file_path = minirt->rt_files[minirt->file_ind].name;
			render_loading_overlay(minirt);
		}
	}
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
	if (minirt->moving && minirt->mouse_events.prev_x != -1)
	{
		quaternion_y_rotation(-0.01 * (x - minirt->mouse_events.prev_x),
			&rotation);
		quaternion_multiply(&minirt->cam.rotation_h, &rotation,
			&minirt->cam.rotation_h);
		quaternion_x_rotation(-(y - minirt->mouse_events.prev_y) * 0.01,
			&rotation);
		quaternion_multiply(&minirt->cam.rotation_v, &rotation,
			&minirt->cam.rotation_v);
		quaternion_normalize(&minirt->cam.rotation_v, &minirt->cam.rotation_v);
		quaternion_normalize(&minirt->cam.rotation_h, &minirt->cam.rotation_h);
		minirt->mouse_events.prev_x = x;
		minirt->mouse_events.prev_y = y;
		// mouse_move(minirt, 300, 300);
	}
	if (minirt->mouse_events.prev_x == -1)
	{
		minirt->mouse_events.prev_x = x;
		minirt->mouse_events.prev_y = y;
	}
	return (0);
}
