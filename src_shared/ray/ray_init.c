/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:39:58 by itan              #+#    #+#             */
/*   Updated: 2023/09/15 16:05:42 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_ray	ray_init(t_vec3 origin, t_vec3 direction)
// {
// 	return ((t_ray){origin, direction, 1, });
// }

t_ray	ray_primary(t_cam *cam, t_offset offset)
{
	t_ray	ray;
	t_vec3	screen_center;
	float	x;
	float	y;
	float	div_min;
	int		pad;
	double	in[3];
	double	out[3];
	t_vec3	direction;

	if (cam->vp_width > cam->vp_height)
	{
		div_min = 1.0f / (float)cam->vp_height;
		pad = (cam->vp_width - cam->vp_height) * 0.5;
	}
	else
	{
		div_min = 1.0f / (float)cam->vp_width;
		pad = (cam->vp_height - cam->vp_width) * 0.5;
	}
	x = ((offset.x - pad * (cam->vp_width > cam->vp_height)) * div_min
		* cam->fov - 0.5);
	y = -((offset.y + pad * (cam->vp_width < cam->vp_height)) * div_min
		* cam->fov - 0.5);
	in[0] = (double)cam->direction.x;
	in[1] = (double)cam->direction.y;
	in[2] = (double)cam->direction.z;
	quaternion_rotate(&cam->rotation, in, out);
	direction.x = (float)out[0];
	direction.y = (float)out[1];
	direction.z = (float)out[2];
	direction = vec3_normalize(direction);
	screen_center = vec3_add(cam->origin, vec3_multiply(direction, 1));
	ray.origin = vec3_add(cam->origin, cam->position);
	ray.direction = vec3_add(screen_center, vec3_new(x, y, 0));
	ray.direction = vec3_normalize(ray.direction);
	return (ray);
}
