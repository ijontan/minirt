/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:48:41 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 20:28:24 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_material_field(int keycode, t_minirt *minirt)
{
	t_selections	*selection;

	selection = &minirt->selection;
	if (keycode == KEY_1)
		selection->selected_material_field = MATERIAL_COLOR;
	else if (keycode == KEY_2)
		selection->selected_material_field = EMISSION_COLOR;
	else if (keycode == KEY_3)
		selection->selected_material_field = SPECULAR_COLOR;
	else if (keycode == KEY_4)
		selection->selected_material_field = DIFFUSE_INTENSITY;
	else if (keycode == KEY_5)
		selection->selected_material_field = SPECULAR_INTENSITY;
	else if (keycode == KEY_6)
		selection->selected_material_field = REFLECTIVE_INTENSITY;
	else if (keycode == KEY_7)
		selection->selected_material_field = EMISSION_INTENSITY;
	else if (keycode == KEY_8)
		selection->selected_material_field = SHININESS;
	else if (keycode == KEY_9)
		selection->selected_material_field = NOT_SELECTED;
	else if (keycode == KEY_0)
		selection->selected_material_field = NOT_SELECTED;
}

void	key_holding_down(int keycode, t_minirt *minirt)
{
	keydown_numbers(keycode, minirt);
	keydown_otherkeys(keycode, minirt);
	keydown_arrows(keycode, minirt);
	keydown_char(keycode, minirt);
	keydown_others(keycode, minirt);
}

int	key_down_hook(int keycode, t_minirt *minirt)
{
	if (!minirt->moving && !minirt->selection.translation_plane)
		select_material_field(keycode, minirt);
	else
		minirt->selection.selected_material_field = NOT_SELECTED;
	if (keycode == KEY_ESC)
	{
		free_minirt(minirt);
		exit(EXIT_SUCCESS);
	}
	if (keycode == KEY_UP && !minirt->selection.selected)
	{
		minirt->pixel_size += 1;
		render(minirt, &thread_init);
	}
	else if (keycode == KEY_DOWN && minirt->pixel_size > 1
		&& !minirt->selection.selected)
	{
		minirt->pixel_size -= 1;
		render(minirt, &thread_init);
	}
	key_holding_down(keycode, minirt);
	return (0);
}

int	key_up_hook(int keycode, t_minirt *minirt)
{
	keyup_numbers(keycode, minirt);
	keyup_otherkeys(keycode, minirt);
	keyup_arrows(keycode, minirt);
	keyup_char(keycode, minirt);
	keyup_others(keycode, minirt);
	return (0);
}
