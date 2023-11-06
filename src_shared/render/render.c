/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:11:04 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 14:08:32 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void	render_menu(t_minirt *minirt)
{
	int		i;
	int		j;

	j = -1;
	while (++j < WINDOW_HEIGHT)
	{
		i = -1;
		while (++i < MENU_WIDTH)
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

int	render(t_minirt *minirt, void (*draw_func)(t_minirt *minirt))
{
	minirt->image = create_image(minirt, (t_offset){.x = minirt->cam.vp_width,
			.y = minirt->cam.vp_height});
	ft_lstiter(minirt->objects, apply_rot);

	draw_func(minirt);

	if (minirt->render_status == FLOATING_MODE)
		render_cam_pos_overlay(minirt);
	render_menu(minirt);

	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->image.image, 0,
		0);

	if (minirt->render_status == FLOATING_MODE)
		put_cam_pos_str(minirt);
	put_menu_str(minirt);
	mlx_destroy_image(minirt->mlx, minirt->image.image);
	return (0);
}

/*
1. create image
2. function
3. put image to window
4. destroy
*/
