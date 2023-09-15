/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:04:12 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 09:38:43 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	loop_hook(t_minirt *minirt)
{
	// t_image	image;
	if (!minirt->key_events.holding_m_left)
		return (0);
	// image.image = mlx_new_image(minirt->mlx, 1280, 720);
	// image.buffer = mlx_get_data_buffer(image.image, &image.pixel_bits,
	// 	&image.line_bytes, &image.endian);
	// draw_scene(&image, &minirt->cam, minirt->sphere);
	// mlx_put_image_to_window(minirt->mlx, minirt->win, image.image, 0, 0);
	// mlx_destroy_image(minirt->mlx, image.image);
	return (0);
}
