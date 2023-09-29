/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:54:03 by itan              #+#    #+#             */
/*   Updated: 2023/09/29 23:12:08 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief random number between 0 and 1, pcg random algorithm
 * 
 * @param state 
 * @return float 
 */
float	random_num(unsigned int *state)
{
	unsigned int	x;

	x = *state * 747796405 + 2891336453;
	x = ((x >> ((x >> 28) + 4)) ^ x) * 277803737;
	*state = (x >> 22) ^ x;
	return (*state / 4294967295.0f);
}

/**
 * @brief normally distributed random number
 * 
 * @param state 
 * @return float 
 */
float	normal_dist_random_num(unsigned int *state)
{
	float	u1;
	float	u2;
	float	r;

	u1 = random_num(state);
	u2 = random_num(state);
	r = ft_sqrt(-2.0 * log(u1)) * ft_cos(PI_2 * u2);
	return (r);
}
