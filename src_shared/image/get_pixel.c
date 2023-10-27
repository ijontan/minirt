/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 03:25:34 by itan              #+#    #+#             */
/*   Updated: 2023/10/27 15:28:54 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	get_pixel(t_image *image, t_offset offset)
{
	char	*dst;

	if (offset.x < 0 || offset.x >= image->size.x || offset.y < 0
		|| offset.y >= image->size.y)
		return (0);
	dst = image->buffer + (offset.y * image->line_bytes + offset.x
			* (image->pixel_bits / 8));
	if (image->endian == 1)
		return (convert_endian(*(unsigned int *)dst));
	else
		return (*(unsigned int *)dst);
}

t_color_c	get_pixel_color(t_image *image, t_offset offset)
{
	t_color	color;

	color.as_int = get_pixel(image, offset);
	return (color_correct(color));
}

t_vec3	get_pixel_vec3(t_image *image, t_offset offset)
{
	t_color_c	color_c;
	t_vec3		vec3;

	color_c = get_pixel_color(image, offset);
	vec3.x = color_c.r;
	vec3.y = color_c.g;
	vec3.z = color_c.b;
	return (vec3_normalize(vec3));
}
