/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menus2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:24:54 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 21:27:29 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_obj_menu_str2(t_minirt *minirt)
{
	minirt->font_color = BLACK;
	if (minirt->selection.selected_material_field == SPECULAR_INTENSITY)
		minirt->font_color = GREEN;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, 120,
		minirt->font_color, "5: Specular Intensity");
	minirt->font_color = BLACK;
	if (minirt->selection.selected_material_field == REFLECTIVE_INTENSITY)
		minirt->font_color = GREEN;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, 140,
		minirt->font_color, "6: Reflective Intensity");
	minirt->font_color = BLACK;
	if (minirt->selection.selected_material_field == EMISSION_INTENSITY)
		minirt->font_color = GREEN;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, 160,
		minirt->font_color, "7: Emission Intensity");
	minirt->font_color = BLACK;
	if (minirt->selection.selected_material_field == SHININESS)
		minirt->font_color = GREEN;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 20, 180,
		minirt->font_color, "8: Shininess");
	minirt->font_color = BLACK;
}
