/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:11:10 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 17:49:17 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "../material.h"
# include "../ray.h"
# include "../vec3.h"

typedef struct s_cone
{
	t_vec3		tip;
	t_vec3		norm_axis;
	t_vec3		rot_axis;
	float		diameter;
	float		height;
	float		radius;
	float		angle;
	float		cos_squared;
	float		cos;
	t_material	material;
}				t_cone;

t_vec3			cone_intersect(t_cone *cone, t_ray *ray);
t_vec3			cone_normal(t_cone *cone, t_vec3 point, float type);

#endif
