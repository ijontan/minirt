/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:01:48 by itan              #+#    #+#             */
/*   Updated: 2023/11/13 15:08:42 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_c	get_color_selection(t_minirt *rt, t_hit_info *hi)
{
	t_color_c	color;

	color = color_correct_new(0, 0, 0, 0);
	if (hi->hit)
		color = get_color(rt, hi);
	if (hi->hit_selection_plane)
		color = color_add(color, rt->selection.plane_color);
	if (hi->hit_rotation_plane)
		color = color_add(color, rt->selection.plane_color);
	color = color_clamp(color);
	return (color);
}

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
			if (!(xy.x % minirt->pixel_size == 0 && xy.y
					% minirt->pixel_size == 0))
				continue ;
			ray = ray_primary(&minirt->cam, xy);
			hit_info = intersect_list(minirt, &ray);
			color = get_color_selection(minirt, &hit_info);
			fill_pixel(&minirt->image, xy, minirt->pixel_size, color);
		}
	}
}
