/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:01:48 by itan              #+#    #+#             */
/*   Updated: 2023/11/04 12:25:12 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_cast(t_minirt *minirt)
{
	t_offset	xy;
	t_ray		ray;
	t_color_c	color;
	t_hit_info	hit_info;
	int			pixel_size;
	int			i;
	int			j;

	pixel_size = minirt->pixel_size;
	xy.y = -1;
	while (++xy.y < WINDOW_HEIGHT)
	{
		xy.x = -1;
		while (++xy.x < WINDOW_WIDTH)
		{
			if ((xy.x % pixel_size != 0 || xy.y % pixel_size != 0))
			{
				++xy.x;
				continue ;
			}
			ray = ray_primary(&minirt->cam, xy);
			hit_info = intersect_list(minirt, &ray);
			color = color_correct_new(0, 0, 0, 0);
			if (hit_info.hit)
				color = get_color(minirt, &hit_info);
			if (hit_info.hit_selection_plane)
				color = color_add(color, minirt->selection.plane_color);
			if (hit_info.hit_rotation_plane)
				color = color_add(color, minirt->selection.plane_color);
			color = color_clamp(color);
			put_pixel(&minirt->image, xy, color_revert(color).as_int);
			i = -1;
			while (++i < pixel_size && xy.x + i < WINDOW_WIDTH)
			{
				j = -1;
				while (++j < pixel_size && xy.y + j < WINDOW_HEIGHT)
				{
					put_pixel(&minirt->image, (t_offset){.x = xy.x + i,
						.y = xy.y + j}, color_revert(color).as_int);
				}
			}
		}
	}
}
