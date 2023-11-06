/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:44:19 by itan              #+#    #+#             */
/*   Updated: 2023/11/06 16:56:00 by rsoo             ###   ########.fr       */
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

int	in_rt_file_position(int x, int y, t_minirt *minirt)
{
	int	i;

	i = -1;
	while (++i < minirt->file_num)
		if (minirt->rt_files[i].top_left.y <= y
			&& y <= minirt->rt_files[i].bottom_right.y
			&& minirt->rt_files[i].top_left.x <= x
			&& x <= minirt->rt_files[i].bottom_right.x)
			return (i);
	return (-1);
}

int	mouse_down_hook(int button, int x, int y, t_minirt *minirt)
{
	if (button == M_CLK_L && !minirt->moving
		&& !minirt->selection.translation_plane)
		select_object((t_offset){.x = x, .y = y}, minirt);
	if (button == M_CLK_R && minirt->selection.translation_plane)
		init_rotation((t_offset){.x = x, .y = y}, minirt);
	if (button == M_CLK_L && x < MENU_WIDTH)
	{
		minirt->file_ind = in_rt_file_position(x, y, minirt);
		if (minirt->file_ind > -1)
		{
			minirt->render_status = RENDER_START_ANIMATION;
			minirt->rt_file_path = minirt->rt_files[minirt->file_ind].name;
			// minirt->loading_overlay.msg = ft_strjoin("Rendering ",
			// 		minirt->rt_file_path);
			free(minirt->loading_overlay.msg);
		}
	}
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
