/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:37:08 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 17:36:57 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "shapes/cone.h"
# include "shapes/cylinder.h"
# include "shapes/plane.h"
# include "shapes/sphere.h"

void	apply_rot(void *object);
void	swap_if_greater(float *a, float *b);
t_vec3	calc_t(float a, float b, float rt_dis);

#endif