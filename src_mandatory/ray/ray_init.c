/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 02:39:58 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 11:57:23 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_init(t_vec3 origin, t_vec3 direction)
{
	return ((t_ray){origin, direction});
}

t_ray	ray_primary(t_cam *cam, float x, float y)
{
	t_ray	ray;
	t_vec3	screen_center;

	screen_center = vec3_add(cam->origin, vec3_multiply(cam->direction, 1));
	ray.origin = cam->origin;
	ray.direction = vec3_add(screen_center, vec3_new(x, y, 0));
	ray.direction = vec3_normalize(ray.direction);
	return (ray);
}
