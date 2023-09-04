/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:04:12 by itan              #+#    #+#             */
/*   Updated: 2023/08/28 16:21:17 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	loop_hook(t_minirt *minirt)
{
	// t_image	image;
	if (!minirt->key_events.holding_m_left)
		return (0);
	// image.img = mlx_new_image(minirt->mlx, 1280, 720);
	// image.buffer = mlx_get_data_addr(image.img, &image.pixel_bits,
	// 	&image.line_bytes, &image.endian);
	// draw_scene(&image, &minirt->cam, minirt->sphere);
	// mlx_put_image_to_window(minirt->mlx, minirt->win, image.img, 0, 0);
	// mlx_destroy_image(minirt->mlx, image.img);
	return (0);
}
