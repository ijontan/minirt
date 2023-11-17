/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_material_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:57:34 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/17 14:21:27 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_color_instructions(t_minirt *minirt)
{
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, MAT_START_Y + 20,
		minirt->font_color, "q = R value");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, MAT_START_Y + 40,
		minirt->font_color, "w = G value");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, MAT_START_Y + 60,
		minirt->font_color, "e = B value");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y + 80,
		minirt->font_color, "hold (q / w / e) + (up / down):");
}

void	put_handle_material_str2(t_minirt *minirt)
{
	if (minirt->selection.selected_material_field == SPECULAR_COLOR)
	{
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y,
			minirt->font_color, "Specular Colour");
		put_color_instructions(minirt);
		minirt->msg = create_color_str_brac("RGB: ",
				minirt->selected_obj_material.specular);
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y + 120,
			minirt->font_color, minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == DIFFUSE_INTENSITY)
	{
		append_num_to_str(&minirt->msg, "Diffuse Intensity: ",
			ft_ftoa(minirt->selected_obj_material.diffuse_i, 2));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y,
			minirt->font_color, minirt->msg);
		free(minirt->msg);
	}
}

void	put_handle_material_str3(t_minirt *minirt)
{
	if (minirt->selection.selected_material_field == SPECULAR_INTENSITY)
	{
		append_num_to_str(&minirt->msg, "Specular Intensity: ",
			ft_ftoa(minirt->selected_obj_material.specular_i, 2));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y,
			minirt->font_color, minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == REFLECTIVE_INTENSITY)
	{
		append_num_to_str(&minirt->msg, "Reflective Intensity: ",
			ft_ftoa(minirt->selected_obj_material.reflective_i, 2));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y,
			minirt->font_color, minirt->msg);
		free(minirt->msg);
	}
}

void	put_handle_material_str4(t_minirt *minirt)
{
	if (minirt->selection.selected_material_field == EMISSION_INTENSITY)
	{
		append_num_to_str(&minirt->msg, "Emission Intensity: ",
			ft_ftoa(minirt->selected_obj_material.emission_i, 2));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y,
			minirt->font_color, minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == SHININESS)
	{
		append_num_to_str(&minirt->msg, "Shininess: ",
			ft_ftoa(minirt->selected_obj_material.shininess, 1));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y,
			minirt->font_color, minirt->msg);
		free(minirt->msg);
	}
}

void	put_handle_material_str(t_minirt *minirt)
{
	if (minirt->selection.selected_material_field == MATERIAL_COLOR)
	{
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y,
			minirt->font_color, "Material Colour");
		put_color_instructions(minirt);
		minirt->msg = create_color_str_brac("RGB: ",
				minirt->selected_obj_material.color);
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y + 120,
			minirt->font_color, minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == EMISSION_COLOR)
	{
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y,
			minirt->font_color, "Emission Colour");
		put_color_instructions(minirt);
		minirt->msg = create_color_str_brac("RGB: ",
				minirt->selected_obj_material.emission);
		mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, MAT_START_Y + 120,
			minirt->font_color, minirt->msg);
		free(minirt->msg);
	}
	put_handle_material_str2(minirt);
	put_handle_material_str3(minirt);
	put_handle_material_str4(minirt);
}
