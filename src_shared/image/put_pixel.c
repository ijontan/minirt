/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:20:25 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 15:06:33 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	convert_endian(unsigned int color)
{
	t_color	tmp;
	t_rgba	rgba;

	tmp.as_int = color;
	rgba = tmp.rgba;
	tmp.rgba = (t_rgba){rgba.a, rgba.r, rgba.g, rgba.b};
	return (tmp.as_int);
}
// for (unsigned char *ptr = &color; ptr < &color + 1; ptr++)
// 	printf("[%x]", *ptr);

/**
 * @brief put pixel in image buffer
 * 
 * @param image 
 * @param x 
 * @param y 
 * @param color 
 */
void	put_pixel(t_image *image, t_offset offset, unsigned int color)
{
	char	*dst;

	dst = image->buffer + (offset.y * image->line_bytes + offset.x
			* (image->pixel_bits / 8));
	if (image->endian == 1)
		*(unsigned int *)dst = convert_endian(color);
	else
		*(unsigned int *)dst = color;
}
