/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:45:05 by itan              #+#    #+#             */
/*   Updated: 2023/10/27 18:34:59 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_image	create_image(t_minirt *rt, t_offset size)
{
	t_image	img;

	img.image = mlx_new_image(rt->mlx, size.x, size.y);
	img.buffer = mlx_get_data_addr(img.image, &img.pixel_bits, &img.line_bytes,
			&img.endian);
	return (img);
}
