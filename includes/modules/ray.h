/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:32:18 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 14:45:21 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "cam.h"
# include "color.h"
# include "image.h"
# include "vec3.h"

/* ----------------------------------- ray ---------------------------------- */

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
	t_vec3		inverse_direction;
	float		intensity;
	t_color_c	color;
}				t_ray;

t_ray			ray_primary(t_cam *cam, t_offset offset);
#endif