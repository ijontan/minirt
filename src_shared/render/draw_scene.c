/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:57:08 by itan              #+#    #+#             */
/*   Updated: 2023/10/31 16:34:13 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_scene(t_minirt *minirt)
{
	int				x;
	int				y;
	int				cycle;
	unsigned int	state;
	t_ray			ray;
	t_color_c		color;
	t_color_c		incoming_light;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color = color_correct_new(0, 0, 0, 0);
			cycle = -1;
			ray = ray_primary(&minirt->cam, (t_offset){.x = x, .y = y});
			state = (unsigned int)((x + y * WINDOW_WIDTH));
			while (++cycle < 10)
			{
				incoming_light = ray_tracing(ray, minirt, &state);
				color = color_add(color, incoming_light);
			}
			color = color_scale(color, 1 / (float)cycle);
			put_pixel(&minirt->image, (t_offset){.x = x, .y = y},
				color_revert(color).as_int);
			++x;
		}
		++y;
	}
}
