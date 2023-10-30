/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:11:04 by rsoo              #+#    #+#             */
/*   Updated: 2023/10/30 23:38:40 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void render_loading_overlay(char *str, t_minirt *minirt)
{
	t_image	bg;
	int x;
	int y;

	bg = create_image(minirt, (t_offset){.x = OVERLAY_WIDTH, .y = OVERLAY_HEIGHT});
	y = OVERLAY_START_Y;
	while (++y < OVERLAY_END_Y)
	{
		x = OVERLAY_START_X;
		while (++x < OVERLAY_END_X)
			put_pixel(&bg, (t_offset){.x = x, .y = y}, 0x40ffffff);
	}
	printf("%s\n", str);
}

void	render_menu(t_minirt *minirt)
{
	int		i;
	int		j;
	t_image	bg;

	bg = create_image(minirt, (t_offset){.x = MENU_WIDTH, .y = WINDOW_HEIGHT});
	j = -1;
	while (++j < WINDOW_HEIGHT)
	{
		i = -1;
		while (++i < MENU_WIDTH)
			put_pixel(&bg, (t_offset){.x = i, .y = j}, 0x40ffffff);
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, bg.image, 0, 0);
	mlx_destroy_image(minirt->mlx, bg.image);
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
	mlx_string_put(minirt->mlx, minirt->win, 20, 180, FONT_COLOR, "esc: exit");
	i = -1;
	j = 1;

	mlx_string_put(minirt->mlx, minirt->win, MENU_START_X, SCENES_START_Y, FONT_COLOR, "Select a scene: ");
	while (++i < minirt->file_num)
		if (minirt->rt_files[i].name[0] != '.')
			mlx_string_put(minirt->mlx, minirt->win, 40, SCENES_START_Y + (20 * j++),
				FONT_COLOR, minirt->rt_files[i].name);
	// free(minirt->rt_files);
}

int	render(t_minirt *minirt, void (*draw_func)(t_minirt *minirt))
{
	// static bool	status;
	minirt->image = create_image(minirt, (t_offset){.x = minirt->cam.vp_width,
			.y = minirt->cam.vp_height});
	// mlx_clear_window(minirt->mlx, minirt->win);
	// if (!status)
	// {
	// ray_cast(minirt);
	// thread_init(minirt);
	// draw_scene(minirt);
	draw_func(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->image.image, 0,
		0);
	render_menu(minirt);
	// 	status = true;
	// }
	mlx_destroy_image(minirt->mlx, minirt->image.image);
	return (0);
}
