/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:37:28 by itan              #+#    #+#             */
/*   Updated: 2023/11/13 15:08:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_pixel(t_image *image, t_offset xy, int size, t_color_c color)
{
	int				i;
	int				j;
	unsigned int	color_int;

	color_int = color_revert(color).as_int;
	i = -1;
	while (++i < size && xy.x + i < WINDOW_WIDTH)
	{
		j = -1;
		while (++j < size && xy.y + j < WINDOW_HEIGHT)
			put_pixel(image, (t_offset){.x = xy.x + i, .y = xy.y + j},
				color_int);
	}
}
