/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:04:12 by itan              #+#    #+#             */
/*   Updated: 2023/09/19 13:12:06 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	loop_hook(t_minirt *minirt)
{
	if (!minirt->moving)
		return (0);
	if (minirt->key_events.holding_w)
		minirt->cam.position = vec3_add(minirt->cam.position,
			vec3_multiply(vec3_apply_rot(minirt->cam.direction,
					minirt->cam.rotation), 2));
	if (minirt->key_events.holding_s)
		minirt->cam.position = vec3_subtract(minirt->cam.position,
			vec3_multiply(vec3_apply_rot(minirt->cam.direction,
					minirt->cam.rotation), 2));
	if (minirt->key_events.holding_a)
		minirt->cam.position = vec3_add(minirt->cam.position,
			vec3_multiply(vec3_apply_rot(minirt->cam.right,
					minirt->cam.rotation), 2));
	if (minirt->key_events.holding_d)
		minirt->cam.position = vec3_subtract(minirt->cam.position,
			vec3_multiply(vec3_apply_rot(minirt->cam.right,
					minirt->cam.rotation), 2));
	if (minirt->key_events.holding_q)
		minirt->cam.position = vec3_subtract(minirt->cam.position,
			vec3_multiply(vec3_apply_rot(minirt->cam.up, minirt->cam.rotation),
				2));
	if (minirt->key_events.holding_e)
		minirt->cam.position = vec3_add(minirt->cam.position,
			vec3_multiply(vec3_apply_rot(minirt->cam.up, minirt->cam.rotation),
				2));
	// ray_cast(minirt);
	thread_init(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->image.img, 0, 0);
	// if (!minirt->key_events.holding_m_left)
	// 	return (0);
	// image.img = mlx_new_image(minirt->mlx, 1280, 720);
	// image.buffer = mlx_get_data_addr(image.img, &image.pixel_bits,
	// 	&image.line_bytes, &image.endian);
	// draw_scene(&image, &minirt->cam, minirt->sphere);
	// mlx_put_image_to_window(minirt->mlx, minirt->win, image.image, 0, 0);
	// mlx_destroy_image(minirt->mlx, image.image);
	return (0);
}
