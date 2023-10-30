/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 01:52:10 by itan              #+#    #+#             */
/*   Updated: 2023/10/30 16:12:25 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define PI_DIV 0.31830988618
#define PI_DIV2 0.15915494309

t_offset	uv_sphere(t_vec3 point, t_offset size)
{
	float	theta;
	float	phi;

	theta = acos(-point.y);
	phi = atan2(-point.z, point.x) + M_PI;
	return ((t_offset){.x = (int)(size.x * (1 - phi * PI_DIV2)),
		.y = (int)(size.y * (1 - theta * PI_DIV))});
}
