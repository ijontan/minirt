/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 03:20:00 by itan              #+#    #+#             */
/*   Updated: 2023/10/27 04:28:20 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_image	load_image(t_minirt *rt, char *path)
{
	t_image	img;

	img.image = mlx_xpm_file_to_image(rt->mlx, path, &img.size.x, &img.size.y);
	img.buffer = mlx_get_data_addr(img.image, &img.pixel_bits, &img.line_bytes,
			&img.endian);
	return (img);
}
