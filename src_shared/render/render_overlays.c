/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_overlays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:53:24 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 18:21:08 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void	render_loading_overlay(t_minirt *minirt)
{
	int	i;
	int	j;

	minirt->loading_overlay.msg = "Rendering current scene";
	minirt->loading_overlay.midpoint = (WINDOW_WIDTH + MENU_WIDTH) * 0.5;
	minirt->loading_overlay.len = ft_strlen(minirt->loading_overlay.msg)
		* CHAR_WIDTH + 20;
	minirt->loading_overlay.start_x = minirt->loading_overlay.midpoint
		- minirt->loading_overlay.len * 0.5;
	minirt->loading_overlay.end_x = minirt->loading_overlay.midpoint
		+ minirt->loading_overlay.len * 0.5;
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
	t_offset	xy;
	char		*tmp;

	minirt->cam_pos_overlay.msg = create_vec3_str("Camera position: ",
			minirt->cam.position);
	minirt->cam_pos_overlay.msg = ft_append(minirt->cam_pos_overlay.msg,
			" | Pixel size: ");
	tmp = ft_itoa(minirt->pixel_size);
	minirt->cam_pos_overlay.msg = ft_append(minirt->cam_pos_overlay.msg, tmp);
	free(tmp);
	if (minirt->selection.selected)
		minirt->cam_pos_overlay.midpoint = WINDOW_WIDTH * 0.5;
	else
		minirt->cam_pos_overlay.midpoint = (WINDOW_WIDTH + MENU_WIDTH) * 0.5;
	minirt->cam_pos_overlay.len = ft_strlen(minirt->cam_pos_overlay.msg)
		* CHAR_WIDTH + 20;
	minirt->cam_pos_overlay.start_x = minirt->cam_pos_overlay.midpoint
		- minirt->cam_pos_overlay.len * 0.5;
	minirt->cam_pos_overlay.end_x = minirt->cam_pos_overlay.midpoint
		+ minirt->cam_pos_overlay.len * 0.5;
	xy.y = CAM_POS_OVERLAY_START_Y;
	while (++xy.y < CAM_POS_OVERLAY_END_Y)
	{
		xy.x = minirt->cam_pos_overlay.start_x;
		while (++xy.x < minirt->cam_pos_overlay.end_x)
			put_pixel(&minirt->image, xy, 0x00ffffff);
	}
}

void	put_overlay_str(t_minirt *minirt, int start_x, int start_y, char *str)
{
	mlx_string_put(minirt->mlx, minirt->win, start_x + 10, start_y + 23,
		FONT_COLOR, str);
}
