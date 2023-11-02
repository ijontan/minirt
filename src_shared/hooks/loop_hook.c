/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:04:12 by itan              #+#    #+#             */
/*   Updated: 2023/11/02 14:55:01 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	transforms(t_vec3 position, t_vec3 direction,
		t_quaternion rotation, float speed)
{
	t_vec3	ret;

	ret = vec3_apply_rot(direction, rotation);
	ret = vec3_multiply(ret, speed);
	ret = vec3_add(position, ret);
	return (ret);
}

int	loop_hook(t_minirt *minirt)
{
	add_translation_plane(minirt);
	remove_translation_plane(minirt);
	if (minirt->selection.translation_plane)
		render(minirt, &thread_init);
	if (!minirt->moving)
		return (0);
	if (minirt->key_events.holding_w)
		minirt->cam.position = transforms(minirt->cam.position,
				minirt->cam.direction, minirt->cam.rotation_h, 2);
	if (minirt->key_events.holding_s)
		minirt->cam.position = transforms(minirt->cam.position,
				minirt->cam.direction, minirt->cam.rotation_h, -2);
	if (minirt->key_events.holding_a)
		minirt->cam.position = transforms(minirt->cam.position,
				minirt->cam.right, minirt->cam.rotation_h, 2);
	if (minirt->key_events.holding_d)
		minirt->cam.position = transforms(minirt->cam.position,
				minirt->cam.right, minirt->cam.rotation_h, -2);
	if (minirt->key_events.holding_lsh)
		minirt->cam.position = transforms(minirt->cam.position, minirt->cam.up,
				minirt->cam.rotation_h, -2);
	if (minirt->key_events.holding_sp)
		minirt->cam.position = transforms(minirt->cam.position, minirt->cam.up,
				minirt->cam.rotation_h, 2);
	// ray_cast(minirt);
	// thread_init(minirt);
	// mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->image.image, 0,
	// 	0);
	render(minirt, &thread_init);
	// render(minirt, &ray_cast);
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
