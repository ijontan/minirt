/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:11:10 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 13:16:33 by rsoo             ###   ########.fr       */
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
	t_material	material;
}				t_cone;

t_vec3			cone_intersect(t_cone *cone, t_ray *ray);
t_vec3			cone_normal(t_cone *cone, t_vec3 point, float type);

#endif
