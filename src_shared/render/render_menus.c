/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:27:15 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 21:45:44 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void	render_menu(t_minirt *minirt, int start_x, int end_x, int end_y)
{
	int	i;
	int	j;

	j = -1;
	while (++j < end_y)
	{
		i = start_x - 1;
		while (++i < end_x)
			put_pixel(&minirt->image, (t_offset){.x = i, .y = j}, 0x00ffffff);
	}
}

void	put_file_str(t_minirt *minirt)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	mlx_string_put(minirt->mlx, minirt->win, MENU_START_X, SCENES_START_Y,
		FONT_COLOR, "Select a scene: ");
	while (++i < minirt->file_num)
	{
		if (minirt->rt_files[i].name[0] != '.')
		{
			if (!ft_strcmp(minirt->rt_files[i].name, minirt->rt_file_path))
				minirt->font_color = GREEN;
			mlx_string_put(minirt->mlx, minirt->win, 40, SCENES_START_Y + (20
					* j++), minirt->font_color, minirt->rt_files[i].name);
			minirt->font_color = BLACK;
		}
	}
}

void	put_menu_str(t_minirt *minirt)
{
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
	put_file_str(minirt);
}

void	put_selected_obj_info(t_minirt *minirt)
{
	const int	obj[4] = {SPHERE, PLANE, CYLINDER, CONE};
	void	(*put_obj_func_ptr[4])(t_minirt *minirt);
	int			i;

	i = -1;
	put_obj_func_ptr[0] = &put_sphere_info;
	put_obj_func_ptr[1] = &put_plane_info;
	put_obj_func_ptr[2] = &put_cylinder_info;
	put_obj_func_ptr[3] = &put_cone_info;
	while (++i < 4)
	{
		if (minirt->selection.selected->type == obj[i])
		{
			(*put_obj_func_ptr[i])(minirt);
			return ;
		}
	}
}

void	put_obj_menu_str(t_minirt *minirt)
{
	minirt->font_color = BLACK;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 20,
		minirt->font_color, "Edit material properties: ");
	if (minirt->selection.selected_material_field == MATERIAL_COLOR)
		minirt->font_color = GREEN;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, 40,
		minirt->font_color, "1: Material Colour");
	minirt->font_color = BLACK;
	if (minirt->selection.selected_material_field == EMISSION_COLOR)
		minirt->font_color = GREEN;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, 60,
		minirt->font_color, "2: Emission Colour");
	minirt->font_color = BLACK;
	if (minirt->selection.selected_material_field == SPECULAR_COLOR)
		minirt->font_color = GREEN;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, 80,
		minirt->font_color, "3: Specular Colour");
	minirt->font_color = BLACK;
	if (minirt->selection.selected_material_field == DIFFUSE_INTENSITY)
		minirt->font_color = GREEN;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, 100,
		minirt->font_color, "4: Diffuse Intensity");
	put_obj_menu_str2(minirt);
	put_selected_obj_info(minirt);
}
