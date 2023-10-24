/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:39:58 by itan              #+#    #+#             */
/*   Updated: 2023/10/25 01:01:57 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_ray	ray_init(t_vec3 origin, t_vec3 direction)
// {
// 	return ((t_ray){origin, direction, 1, });
// }

t_ray	ray_primary(t_cam *cam, t_offset offset)
{
	t_ray			ray;
	t_vec3			screen_center;
	float			x;
	float			y;
	float			div_min;
	int				pad;
	t_quaternion	rotation;

	if (cam->vp_width > cam->vp_height)
	{
		div_min = 1.0f / (float)cam->vp_height;
		pad = (cam->vp_width - cam->vp_height) * 0.5;
		x = ((offset.x - pad) * div_min - 0.5) * cam->fov;
		y = -((offset.y) * div_min - 0.5) * cam->fov;
	}
	else
	{
		div_min = 1.0f / (float)cam->vp_width;
		pad = (cam->vp_height - cam->vp_width) * 0.5;
		x = ((offset.x) * div_min - 0.5) * cam->fov;
		y = -((offset.y - pad) * div_min - 0.5) * cam->fov;
	}
	ray.origin = vec3_add(cam->origin, cam->position);
	screen_center = vec3_add(cam->origin, vec3_multiply(cam->direction, 1));
	ray.direction = vec3_add(screen_center, vec3_multiply(cam->right, -x));
	ray.direction = vec3_add(ray.direction, vec3_multiply(cam->up, y));
	quaternion_multiply(&cam->rotation_h, &cam->rotation_v, &rotation);
	ray.direction = vec3_apply_rot(ray.direction, rotation);
	return (ray);
}
