/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:11:04 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/07 09:52:52 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_menu_and_overlays(t_minirt *minirt)
{
	if (minirt->render_status == RENDER_CURRENT_SCENE)
		render_loading_overlay(minirt);
	if (minirt->selection.selected)
		render_menu(minirt, WINDOW_WIDTH - MENU_WIDTH, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_cam_pos_overlay(minirt);
	render_menu(minirt, 0, MENU_WIDTH, WINDOW_HEIGHT);
}

void	put_strings(t_minirt *minirt)
{
	if (minirt->render_status == RENDER_CURRENT_SCENE)
		put_overlay_str(minirt, minirt->loading_overlay.start_x, OVERLAY_START_Y, "Rendering current scene");
	if (minirt->selection.selected)
		put_obj_menu_str(minirt);
	put_overlay_str(minirt, minirt->cam_pos_overlay.start_x, CAM_POS_OVERLAY_START_Y, minirt->cam_pos_overlay.msg);
	free(minirt->cam_pos_overlay.msg);
	put_menu_str(minirt);
	// put_handle_material_str(minirt);
}

int	render(t_minirt *minirt, void (*draw_func)(t_minirt *minirt))
{
	minirt->image = create_image(minirt, (t_offset){.x = minirt->cam.vp_width,
			.y = minirt->cam.vp_height});
	ft_lstiter(minirt->objects, apply_rot);

	draw_func(minirt);
	
	render_menu_and_overlays(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->image.image, 0,
		0);
	put_strings(minirt);
	mlx_destroy_image(minirt->mlx, minirt->image.image);
	return (0);
}
