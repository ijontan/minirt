/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_animations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:29 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 13:35:11 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	reset_cam_end(t_minirt *rt)
{
	rt->render_status = RESET_CAM_DONE;
}

void	reset_cam_animation(t_minirt *minirt)
{
	static t_animations	a;
	static t_vec3		hv;
	static t_vec3		start;

	if (a.frame == 0)
	{
		start = minirt->cam.position;
		hv = (t_vec3){minirt->cam.pitch, minirt->cam.yaw, 0};
		a.frame_max = (vec3_length(start)) / 10 + 10;
	}
	handle_animation(minirt, &a, NULL, (t_a_func)reset_cam_end);
	minirt->cam.position.x = (float)bazier_curves_1d_quadratic(a.t,
			(double [3]){start.x, (start.x), 0});
	minirt->cam.position.y = (float)bazier_curves_1d_quadratic(a.t,
			(double [3]){start.y, (start.y), 0});
	minirt->cam.position.z = (float)bazier_curves_1d_quadratic(a.t,
			(double [3]){start.z, (start.z), 0});
	minirt->cam.yaw = (float)bazier_curves_1d_quadratic(a.t, (double [3]){hv.y,
			hv.y, 0});
	minirt->cam.pitch = (float)bazier_curves_1d_quadratic(a.t, (double [3]){
			hv.x, hv.x, 0});
	render(minirt, &thread_init);
}
