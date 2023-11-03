/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:01:48 by itan              #+#    #+#             */
/*   Updated: 2023/10/31 16:31:32 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_cast(t_minirt *minirt)
{
	t_offset	xy;
	t_ray		ray;
	t_color_c	color;
	t_hit_info	hit_info;

	xy.y = -1;
	while (++xy.y < WINDOW_HEIGHT)
	{
		xy.x = -1;
		while (++xy.x < WINDOW_WIDTH)
		{
			ray = ray_primary(&minirt->cam, xy);
			hit_info = intersect_list(minirt, &ray);
			color = color_correct_new(0, 0, 0, 0);
			if (hit_info.hit)
				color = get_color(minirt, &hit_info);
			// else
			// 	color = color_scale(minirt->amb_light.color,
			// 			minirt->amb_light.ratio);
			put_pixel(&minirt->image, xy, color_revert(color).as_int);
		}
	}
}
