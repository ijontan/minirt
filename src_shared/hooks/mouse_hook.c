/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:44:19 by itan              #+#    #+#             */
/*   Updated: 2023/11/03 01:25:18 by itan             ###   ########.fr       */
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

int	mouse_down_hook(int button, int x, int y, t_minirt *minirt)
{
	if (button == M_CLK_L && !minirt->moving
		&& !minirt->selection.translation_plane)
		select_object((t_offset){.x = x, .y = y}, minirt);
	if (button == M_CLK_R && minirt->selection.translation_plane)
		init_rotation((t_offset){.x = x, .y = y}, minirt);
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
	if (button == M_CLK_R && minirt->selection.rotation_plane)
		stop_rotation(minirt);
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
	translate_objects(x, y, minirt);
	calc_rotation((t_offset){.x = x, .y = y}, minirt);
	rotate_cam(x, y, minirt);
	return (0);
}
