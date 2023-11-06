/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_animations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:22:29 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 14:02:16 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void reset_cam_animation(t_minirt *minirt)
{
	static unsigned int frame;
	float				t;
	static t_vec3 start;
	static t_quaternion h;
	static t_quaternion v;
	static t_quaternion e;
	
	t = (float)frame / 50;
	if (frame == 0)
	{
		start = minirt->cam.position;
		h = minirt->cam.rotation_h;
		v = minirt->cam.rotation_v;
		e = quaternion_create_id();
	}
	if (frame > 50)
	{
		frame = 0;
		minirt->render_status = RESET_CAM_DONE;
		return ;
	}
	minirt->cam.position.x = (float)bazier_curves_1d_quadratic(t, (double [3]){
		start.x, (start.x) , 0
	});
	minirt->cam.position.y = (float)bazier_curves_1d_quadratic(t, (double [3]){
		start.y, (start.y) , 0
	});
	minirt->cam.position.z = (float)bazier_curves_1d_quadratic(t, (double [3]){
		start.z, (start.z) , 0
	});
	frame++;
	quaternion_slerp(&h,&e,t, &minirt->cam.rotation_h);
	quaternion_slerp(&v,&e,t, &minirt->cam.rotation_v);
	// printf("position: %f %f %f", )
	render(minirt, &thread_init);
}
