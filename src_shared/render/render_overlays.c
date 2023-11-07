/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_overlays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:53:24 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/07 09:45:20 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void	render_loading_overlay(t_minirt *minirt)
{
	int		i;
	int		j;

	minirt->loading_overlay.len = ft_strlen(minirt->loading_overlay.msg) * CHAR_WIDTH + 20;
	minirt->loading_overlay.start_x = MID_X - minirt->loading_overlay.len * 0.5;
	minirt->loading_overlay.end_x = MID_X + minirt->loading_overlay.len * 0.5;
	j = OVERLAY_START_Y;
	while (++j < OVERLAY_END_Y)
	{
		i = minirt->loading_overlay.start_x;
		while (++i < minirt->loading_overlay.end_x)
			put_pixel(&minirt->image, (t_offset){.x = i, .y = j}, 0x00ffffff);
	}
}

void	render_cam_pos_overlay(t_minirt *minirt)
{
	int		i;
	int		j;

	minirt->cam_pos_overlay.msg = create_vec3_str("Camera position: ", minirt->cam.position);

	if (minirt->selection.selected)
		minirt->cam_pos_overlay.midpoint = WINDOW_WIDTH * 0.5;
	else
		minirt->cam_pos_overlay.midpoint = (WINDOW_WIDTH + MENU_WIDTH) * 0.5;
	minirt->cam_pos_overlay.len = ft_strlen(minirt->cam_pos_overlay.msg) * CHAR_WIDTH + 20;
	minirt->cam_pos_overlay.start_x = minirt->cam_pos_overlay.midpoint - minirt->cam_pos_overlay.len * 0.5;
	minirt->cam_pos_overlay.end_x = minirt->cam_pos_overlay.midpoint + minirt->cam_pos_overlay.len * 0.5;
	j = CAM_POS_OVERLAY_START_Y;
	while (++j < CAM_POS_OVERLAY_END_Y)
	{
		i = minirt->cam_pos_overlay.start_x;
		while (++i < minirt->cam_pos_overlay.end_x)
			put_pixel(&minirt->image, (t_offset){.x = i, .y = j}, 0x00ffffff);
	}
}

void put_overlay_str(t_minirt *minirt, int start_x, int start_y, char *str)
{
	mlx_string_put(minirt->mlx, minirt->win, start_x + 10,
		start_y + 23, FONT_COLOR, str);
}
