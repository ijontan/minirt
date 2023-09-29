/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:45:05 by itan              #+#    #+#             */
/*   Updated: 2023/09/29 21:49:13 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_image create_image(t_minirt *rt)
{
	t_image img;

	img.image = mlx_new_image(rt->mlx, rt->cam.vp_width, rt->cam.vp_height);
	img.buffer = mlx_get_data_addr(img.image, &img.pixel_bits,
							  &img.line_bytes, &img.endian);
	return (img);
}
