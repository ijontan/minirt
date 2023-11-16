/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:39:58 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 17:24:05 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_ray	ray_init(t_vec3 origin, t_vec3 direction)
// {
// 	return ((t_ray){origin, direction, 1, });
// }

t_vec3	get_raydirection(t_cam *cam, t_vec3 xy_dm)
{
	t_vec3			screen_center;
	t_vec3			ray_direction;
	t_quaternion	yaw;
	t_quaternion	pitch;
	t_quaternion	rotation;

	screen_center = vec3_add(cam->origin, vec3_multiply(cam->direction, 1));
	ray_direction = vec3_add(screen_center, vec3_multiply(cam->right,
				-xy_dm.x));
	ray_direction = vec3_add(ray_direction, vec3_multiply(cam->up, xy_dm.y));
	quaternion_y_rotation(cam->yaw, &yaw);
	quaternion_x_rotation(cam->pitch, &pitch);
	quaternion_multiply(&yaw, &pitch, &rotation);
	quaternion_normalize(&rotation, &rotation);
	ray_direction = vec3_apply_rot(ray_direction, rotation);
	ray_direction = vec3_normalize(ray_direction);
	return (ray_direction);
}

t_ray	ray_primary(t_cam *cam, t_offset offset)
{
	t_ray	ray;
	t_vec3	xy_dm;
	int		pad;

	ft_bzero(&ray, sizeof(t_ray));
	if (cam->vp_width > cam->vp_height)
	{
		xy_dm.z = 1.0f / (float)cam->vp_height;
		pad = (cam->vp_width - cam->vp_height) * 0.5;
		xy_dm.x = ((offset.x - pad) * xy_dm.z - 0.5) * cam->fov;
		xy_dm.y = -((offset.y) * xy_dm.z - 0.5) * cam->fov;
	}
	else
	{
		xy_dm.z = 1.0f / (float)cam->vp_width;
		pad = (cam->vp_height - cam->vp_width) * 0.5;
		xy_dm.x = ((offset.x) * xy_dm.z - 0.5) * cam->fov;
		xy_dm.y = -((offset.y - pad) * xy_dm.z - 0.5) * cam->fov;
	}
	ray.origin = vec3_add(cam->origin, cam->position);
	ray.direction = get_raydirection(cam, xy_dm);
	return (ray);
}
