/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:30:23 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 17:35:41 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	swap_if_greater(float *a, float *b)
{
	float	tmp;

	if (*a > *b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

t_vec3	calc_t(float a, float b, float rt_dis)
{
	t_vec3	t;

	t.z = 1.0f / (2.0f * a);
	t.x = (-b + rt_dis) * t.z;
	t.y = (-b - rt_dis) * t.z;
	t.z = 2;
	return (t);
}
