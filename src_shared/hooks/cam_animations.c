/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_animations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:29 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/10 15:30:20 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	reset_cam_animation(t_minirt *minirt)
{
	static unsigned int	frame;
	float				t;
	static t_vec3		start;
	static float		h;
	static float		v;

	t = (float)frame / 50;
	if (frame == 0)
	{
		start = minirt->cam.position;
		h = minirt->cam.pitch;
		v = minirt->cam.yaw;
	}
	if (frame > 50)
	{
		frame = 0;
		minirt->render_status = RESET_CAM_DONE;
		return ;
	}
	minirt->cam.position.x = (float)bazier_curves_1d_quadratic(t,
			(double[3]){start.x, (start.x), 0});
	minirt->cam.position.y = (float)bazier_curves_1d_quadratic(t,
			(double[3]){start.y, (start.y), 0});
	minirt->cam.position.z = (float)bazier_curves_1d_quadratic(t,
			(double[3]){start.z, (start.z), 0});
	frame++;
	minirt->cam.yaw = (float)bazier_curves_1d_quadratic(t, (double[3]){v, v,
			0});
	minirt->cam.pitch = (float)bazier_curves_1d_quadratic(t, (double[3]){h, h,
			0});
	// printf("position: %f %f %f", )
	render(minirt, &thread_init);
}
