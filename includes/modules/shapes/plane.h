/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:35:41 by itan              #+#    #+#             */
/*   Updated: 2023/11/03 01:38:16 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "../material.h"
# include "../ray.h"
# include "../vec3.h"

typedef struct s_plane
{
	t_vec3		center;
	t_vec3		normal;
	t_vec3		rot_normal;
	t_material	material;
	float		r;
}				t_plane;

t_plane			plane_new(t_vec3 point, t_vec3 dir, t_material material);
t_vec3			disk_intersect(t_plane *plane, t_ray *ray);
t_vec3			plane_intersect(t_plane *plane, t_ray *ray);
t_vec3			sc_interesect(t_plane *plane, t_ray *ray, t_vec3 start,
					float angle);

#endif