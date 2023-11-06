/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_overlays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:53:24 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 18:14:52 by rsoo             ###   ########.fr       */
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

	minirt->cam_pos_overlay.msg = create_vec3_str("Camera position: ", minirt->cam.position);

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
}

void put_cam_pos_str(t_minirt *minirt)
{
	mlx_string_put(minirt->mlx, minirt->win, minirt->cam_pos_overlay.start_x + 10,
		OVERLAY_START_Y + 23 + 300, FONT_COLOR, minirt->cam_pos_overlay.msg);

	free(minirt->cam_pos_overlay.msg);
}

void	render_obj_menu(t_minirt *minirt)
{
	int		i;
	int		j;

	j = -1;
	while (++j < WINDOW_HEIGHT)
	{
		i = WINDOW_WIDTH - MENU_WIDTH;
		while (++i < WINDOW_WIDTH)
			put_pixel(&minirt->image, (t_offset){.x = i, .y = j}, 0x00ffffff);
	}
}

void put_obj_menu_str(t_minirt *minirt)
{
	const int obj[4] = {SPHERE, PLANE, CYLINDER, CONE};
	void (*put_obj_func_ptr[4])(t_minirt *minirt) = {
		&put_sphere_info,
		&put_plane_info,
		&put_cylinder_info,
		&put_cone_info
	};
	int i;

	i = -1;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 20, FONT_COLOR,
		"Edit material properties: ");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 40, FONT_COLOR,
		"1: Material Colour");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 60, FONT_COLOR,
		"2: Emission Colour");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 80, FONT_COLOR,
		"3: Specular Colour");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 100, FONT_COLOR,
		"4: Diffuse Intensity");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 120, FONT_COLOR,
		"5: Specular Intensity");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 140, FONT_COLOR,
		"6: Reflective Intensity");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 160, FONT_COLOR,
		"7: Emission Intensity");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 180, FONT_COLOR,
		"8: Shininess");
	while (++i < 4)
	{
		if (minirt->selection.selected->type == obj[i])
		{
			(*put_obj_func_ptr[i])(minirt);
			return ;
		}
	}
}
