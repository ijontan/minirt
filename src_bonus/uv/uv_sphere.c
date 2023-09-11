/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 01:52:10 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 15:20:56 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define PI_DIV 0.31830988618
#define PI_DIV2 0.15915494309

t_vec3	uv_sphere(t_vec3 point, t_offset size)
{
	float	theta;
	float	phi;

	(void)size;
	theta = ft_acos(-point.y);
	phi = ft_atan2(-point.z, point.x) + M_PI;
	return (vec3_new(phi * PI_DIV2, theta * PI_DIV, 0));
}
