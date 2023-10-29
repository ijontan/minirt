/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:28:03 by itan              #+#    #+#             */
/*   Updated: 2023/10/29 19:09:50 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOUNDING_BOX_H
# define BOUNDING_BOX_H

# include "ray.h"
# include "vec3.h"
/* ------------------------------ bounding box ------------------------------ */

typedef struct s_bound_box
{
	t_vec3			min;
	t_vec3			max;
}					t_bound_box;

typedef struct s_object
{
	void			*object;
	unsigned char	type;
	t_bound_box		bounding_box;
}					t_object;

t_bound_box			bound_box_new(t_vec3 min, t_vec3 max);
t_bound_box			bound_box_expand(t_bound_box box, t_vec3 point);
bool				bound_box_intersect(t_bound_box box, t_ray ray);

#endif