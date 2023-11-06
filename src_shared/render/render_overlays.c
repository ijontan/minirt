/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_overlays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:53:24 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 10:52:38 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void	render_loading_overlay(t_minirt *minirt)
{
	int		i;
	int		j;

	if (!minirt->loading_overlay.msg)
		return ;
	minirt->image = create_image(minirt, (t_offset){.x = minirt->cam.vp_width,
		.y = minirt->cam.vp_height});
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
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->image.image, 0, 0);
	mlx_destroy_image(minirt->mlx, minirt->image.image);
	mlx_string_put(minirt->mlx, minirt->win, minirt->loading_overlay.start_x + 10,
		OVERLAY_START_Y + 23, FONT_COLOR, minirt->loading_overlay.msg);
	printf("render loading overlay done\n");
}

void	render_cam_pos_overlay(t_minirt *minirt)
{
	int		i;
	int		j;

	minirt->cam_pos_overlay.msg = ft_strjoin("x: ", ft_itoa(minirt->cam.position.x));
	minirt->cam_pos_overlay.msg = ft_strjoin(minirt->cam_pos_overlay.msg, ", y: ");
	minirt->cam_pos_overlay.msg = ft_strjoin(minirt->cam_pos_overlay.msg, ft_itoa(minirt->cam.position.y));
	minirt->cam_pos_overlay.msg = ft_strjoin(minirt->cam_pos_overlay.msg, ", z: ");
	minirt->cam_pos_overlay.msg = ft_strjoin(minirt->cam_pos_overlay.msg, ft_itoa(minirt->cam.position.z));
	minirt->cam_pos_overlay.msg = ft_strjoin(minirt->cam_pos_overlay.msg, "\n");

	minirt->cam_pos_overlay.midpoint = (WINDOW_WIDTH + MENU_WIDTH) * 0.5;
	minirt->cam_pos_overlay.len = ft_strlen(minirt->cam_pos_overlay.msg) * CHAR_WIDTH + 20;
	minirt->cam_pos_overlay.start_x = minirt->cam_pos_overlay.midpoint - minirt->cam_pos_overlay.len * 0.5;
	minirt->cam_pos_overlay.end_x = minirt->cam_pos_overlay.midpoint + minirt->cam_pos_overlay.len * 0.5;
	j = OVERLAY_START_Y + 300;

	while (++j < OVERLAY_END_Y + 300)
	{
		i = minirt->cam_pos_overlay.start_x;
		while (++i < minirt->cam_pos_overlay.end_x)
			put_pixel(&minirt->image, (t_offset){.x = i, .y = j}, 0x40ffffff);
	}
	printf("render camera position overlay done\n");
}

void put_cam_pos_str(t_minirt *minirt)
{
	printf("%s", minirt->cam_pos_overlay.msg);
	mlx_string_put(minirt->mlx, minirt->win, minirt->cam_pos_overlay.start_x + 10,
		OVERLAY_START_Y + 23 + 300, FONT_COLOR, minirt->cam_pos_overlay.msg);

	free(minirt->cam_pos_overlay.msg);
}
