/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:34:34 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 14:49:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "../material.h"
# include "../ray.h"
# include "../vec3.h"

typedef struct s_sphere
{
	t_vec3		center;
	float		radius;
	t_color_c	color;
	t_material	material;
}				t_sphere;

t_sphere		sphere_new(t_vec3 center, float radius, t_material material);
t_vec3			sphere_normal(t_sphere *sphere, t_vec3 point);
t_vec3			sphere_intersect(t_sphere *sphere, t_ray *ray);

#endif