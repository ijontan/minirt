/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:20:25 by itan              #+#    #+#             */
/*   Updated: 2023/08/25 23:05:54 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	convert_endian(unsigned int color)
{
	t_color	tmp;

	tmp = *(t_color *)&color;
	return ((unsigned int)(unsigned char[4]){tmp.b, tmp.g, tmp.r, tmp.a});
}

void	put_pixel(t_image *image, int x, int y, unsigned int color)
{
	char *dst;

	dst = image->buffer + (y * image->line_bytes + x * (image->pixel_bits / 8));
	if (image->endian == 1)
		*(unsigned int *)dst = convert_endian(color);
	else
		*(unsigned int *)dst = color;
}