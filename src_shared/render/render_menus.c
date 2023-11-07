/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:27:15 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/07 09:51:08 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void	render_menu(t_minirt *minirt, int start_x, int end_x, int end_y)
{
	int		i;
	int		j;

	j = -1;
	while (++j < end_y)
	{
		i = start_x - 1;
		while (++i < end_x)
			put_pixel(&minirt->image, (t_offset){.x = i, .y = j}, 0x40ffffff);
	}
}

void put_menu_str(t_minirt *minirt)
{
	int i;
	int j;
	
	i = -1;
	j = 1;
	mlx_string_put(minirt->mlx, minirt->win, 20, 20, FONT_COLOR,
		"w: move forward");
	mlx_string_put(minirt->mlx, minirt->win, 20, 40, FONT_COLOR,
		"s: move backward");
	mlx_string_put(minirt->mlx, minirt->win, 20, 60, FONT_COLOR,
		"a: move left");
	mlx_string_put(minirt->mlx, minirt->win, 20, 80, FONT_COLOR,
		"d: move right");
	mlx_string_put(minirt->mlx, minirt->win, 20, 100, FONT_COLOR,
		"space: move up");
	mlx_string_put(minirt->mlx, minirt->win, 20, 120, FONT_COLOR,
		"shift: move down");
	mlx_string_put(minirt->mlx, minirt->win, 20, 140, FONT_COLOR,
		"r: render scene");
	mlx_string_put(minirt->mlx, minirt->win, 20, 160, FONT_COLOR,
		"f: toggle mode (flying / edit)");
	mlx_string_put(minirt->mlx, minirt->win, 20, 180, FONT_COLOR,
		"o: reset camera position");
	mlx_string_put(minirt->mlx, minirt->win, 20, 200, FONT_COLOR,
		"up: increase pixel size");
	mlx_string_put(minirt->mlx, minirt->win, 20, 220, FONT_COLOR,
		"down: decrease pixel size");
	mlx_string_put(minirt->mlx, minirt->win, 20, 240, FONT_COLOR, "esc: exit");
	mlx_string_put(minirt->mlx, minirt->win, MENU_START_X, SCENES_START_Y,
		FONT_COLOR, "Select a scene: ");
	while (++i < minirt->file_num)
		if (minirt->rt_files[i].name[0] != '.')
			mlx_string_put(minirt->mlx, minirt->win, 40, SCENES_START_Y + (20
					* j++), FONT_COLOR, minirt->rt_files[i].name);
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

