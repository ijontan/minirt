/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:44:19 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 21:33:10 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

int	mouse_down_hook(int button, int x, int y, t_minirt *minirt)
{
	(void)x;
	(void)y;
	if (button == M_CLK_L)
	{
		ft_printf("mouse down left\n");
		minirt->key_events.holding_m_left = true;
	}
	else if (button == M_CLK_R)
		minirt->key_events.holding_m_right = true;
	else if (button == M_CLK_M)
		minirt->key_events.holding_m_middle = true;
	return (0);
}

int	mouse_up_hook(int button, int x, int y, t_minirt *minirt)
{
	(void)x;
	(void)y;
	if (button == M_CLK_L)
	{
		ft_printf("mouse up left\n");
		minirt->key_events.holding_m_left = false;
	}
	else if (button == M_CLK_R)
		minirt->key_events.holding_m_right = false;
	else if (button == M_CLK_M)
		minirt->key_events.holding_m_middle = false;
	return (0);
}

int	mouse_move_hook(int x, int y, t_minirt *minirt)
{
	t_quaternion	q;
	double			in[3];
	double			out[3];
	t_image			image;

	(void)y;
	if (minirt->mouse_events.prev_x == 0)
		minirt->mouse_events.prev_x = x;
	if (minirt->key_events.holding_m_left)
	{
		q = quaternion_create_id();
		quaternion_y_rotation((minirt->mouse_events.prev_x - x) / 200, &q);
		quaternion_normalize(&q, &q);
		minirt->mouse_events.prev_x = x;
		in[0] = (double)minirt->cam.direction.x;
		in[1] = (double)minirt->cam.direction.y;
		in[2] = (double)minirt->cam.direction.z;
		quaternion_rotate(&q, in, out);
		minirt->cam.direction.x = (float)out[0];
		minirt->cam.direction.y = (float)out[1];
		minirt->cam.direction.z = (float)out[2];
		// quaternion_x_rotation((minirt->mouse_events.prev_y - y) / 600, &q);
		// quaternion_normalize(&q, &q);
		// minirt->mouse_events.prev_y = y;
		// in[0] = (double)minirt->cam.direction.x;
		// in[1] = (double)minirt->cam.direction.y;
		// in[2] = (double)minirt->cam.direction.z;
		// quaternion_rotate(&q, in, out);
		// minirt->cam.direction.x = (float)out[0];
		// minirt->cam.direction.y = (float)out[1];
		// minirt->cam.direction.z = (float)out[2];
		image.img = mlx_new_image(minirt->mlx, 1280, 720);
		image.buffer = mlx_get_data_addr(image.img, &image.pixel_bits,
			&image.line_bytes, &image.endian);
		draw_scene(&image, &minirt->cam, minirt->sphere);
		mlx_put_image_to_window(minirt->mlx, minirt->win, image.img, 0, 0);
		mlx_destroy_image(minirt->mlx, image.img);
	}
	return (0);
}
