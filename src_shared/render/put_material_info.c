/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_material_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:57:34 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/08 15:15:37 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_color_instructions(t_minirt *minirt)
{
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, MATERIAL_SECTION_START_Y + 20, minirt->font_color,
	"q = R value");
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, MATERIAL_SECTION_START_Y + 40, minirt->font_color,
	"w = G value");
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, MATERIAL_SECTION_START_Y + 60, minirt->font_color,
	"e = B value");
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y + 80, minirt->font_color,
	"hold (q / w / e) + (up / down):");
}

void	put_handle_material_str(t_minirt *minirt)
{
	if (minirt->selection.selected_material_field == MATERIAL_COLOR)
	{
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y, minirt->font_color,
	"Material Colour");
		put_color_instructions(minirt);
		minirt->msg = create_color_str_brac("RGB: ", minirt->selected_obj_material.color);
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y + 120, minirt->font_color,
	minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == EMISSION_COLOR)
	{
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y, minirt->font_color,
	"Emission Colour");
		put_color_instructions(minirt);
		minirt->msg = create_color_str_brac("RGB: ", minirt->selected_obj_material.emission);
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y + 120, minirt->font_color,
	minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == SPECULAR_COLOR)
	{
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y, minirt->font_color,
	"Specular Colour");
		put_color_instructions(minirt);	
		minirt->msg = create_color_str_brac("RGB: ", minirt->selected_obj_material.specular);
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y + 120, minirt->font_color,
	minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == DIFFUSE_INTENSITY)
	{
		minirt->msg = ft_strjoin("Diffuse Intensity: ", ft_ftoa(minirt->selected_obj_material.diffuse_i, 1));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y, minirt->font_color,
	minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == SPECULAR_INTENSITY)
	{
		minirt->msg = ft_strjoin("Specular Intensity: ", ft_ftoa(minirt->selected_obj_material.specular_i, 1));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y, minirt->font_color,
	minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == REFLECTIVE_INTENSITY)
	{
		minirt->msg = ft_strjoin("Reflective Intensity: ", ft_ftoa(minirt->selected_obj_material.reflective_i, 1));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y, minirt->font_color,
	minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == EMISSION_INTENSITY)
	{
		minirt->msg = ft_strjoin("Emission Intensity: ", ft_ftoa(minirt->selected_obj_material.emission_i, 1));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y, minirt->font_color,
	minirt->msg);
		free(minirt->msg);
	}
	else if (minirt->selection.selected_material_field == SHININESS)
	{
		minirt->msg = ft_strjoin("Shininess: ", ft_ftoa(minirt->selected_obj_material.shininess, 1));
		mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, MATERIAL_SECTION_START_Y, minirt->font_color,
	minirt->msg);
		free(minirt->msg);
	}
}