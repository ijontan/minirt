/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:36:37 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 14:48:42 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "../material.h"
# include "../ray.h"
# include "../vec3.h"

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		normalized_axis;
	float		radius;
	float		height;
	t_material	material;
}				t_cylinder;

t_vec3			cylinder_intersect(t_cylinder *cylinder, t_ray *ray);
t_vec3			cylinder_normal(t_cylinder *cylinder, t_vec3 point, float type);

#endif