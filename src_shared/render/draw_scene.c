/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:57:08 by itan              #+#    #+#             */
/*   Updated: 2023/11/17 01:27:35 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculate_cycle(t_ray ray, t_minirt *minirt, t_offset xy)
{
	int				cycle;
	unsigned int	state;
	t_color_c		color;
	t_color_c		incoming_light;

	color = color_correct_new(0, 0, 0, 0);
	cycle = -1;
	state = (unsigned int)((xy.x + xy.y * WINDOW_WIDTH));
	while (++cycle < 20)
	{
		incoming_light = ray_tracing(ray, minirt, &state);
		color = color_add(color, incoming_light);
	}
	color = color_scale(color, 1 / (float)cycle);
	put_pixel(&minirt->image, xy, color_revert(color).as_int);
}

void	draw_scene(t_minirt *minirt)
{
	t_offset	xy;
	t_ray		ray;

	xy.y = 0;
	while (xy.y < WINDOW_HEIGHT)
	{
		xy.x = 0;
		while (xy.x < WINDOW_WIDTH)
		{
			ray = ray_primary(&minirt->cam, xy);
			calculate_cycle(ray, minirt, xy);
			++xy.x;
		}
		++xy.y;
	}
}
