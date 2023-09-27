/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:08:10 by itan              #+#    #+#             */
/*   Updated: 2023/09/27 15:08:19 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	reflection(t_vec3 d_ray, t_vec3 normal)
{
	float	dot_prod;
	t_vec3	d_specular;

	dot_prod = vec3_dot(d_ray, normal) * 2;
	d_specular = vec3_multiply(normal, dot_prod);
	d_specular = vec3_subtract(d_ray, d_specular);
	d_specular = vec3_normalize(d_specular);
	if (vec3_dot(d_specular, normal) < 0.0f)
		d_specular = vec3_multiply(d_specular, -1.0f);
	return (d_specular);
}
