/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:57:08 by itan              #+#    #+#             */
/*   Updated: 2023/10/26 15:01:00 by itan             ###   ########.fr       */
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
	while (y < 720)
	{
		x = 0;
		while (x < 1280)
		{
			color = color_correct_new(0, 0, 0, 0);
			cycle = -1;
			ray = ray_primary(&minirt->cam, (t_offset){.x = x, .y = y});
			state = (unsigned int)((x + y * 1280));
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
