/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 03:20:00 by itan              #+#    #+#             */
/*   Updated: 2023/11/17 16:11:13 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_image	load_image(t_minirt *rt, char *path)
{
	t_image	img;

	img.image = mlx_xpm_file_to_image(rt->mlx, path, &img.size.x, &img.size.y);
	if (!img.image)
	{
		printf("\e[0;31mError\nInvalid texture path: %s\e[0m\n", path);
		return (img);
	}
	img.buffer = mlx_get_data_addr(img.image, &img.pixel_bits, &img.line_bytes,
			&img.endian);
	return (img);
}
