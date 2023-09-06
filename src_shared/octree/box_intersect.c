/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:25:10 by itan              #+#    #+#             */
/*   Updated: 2023/09/06 15:26:17 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static void	swap_float(float *a, float *b)
// {
// 	float	tmp;

// 	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// bool	box_intersect(t_bounding_box *box, t_ray *ray)
// {
// 	float	tmin;
// 	float	tmax;
// 	float	tmin_tmp;
// 	float	tmax_tmp;
// 	int		i;

// 	tmin = -INFINITY;
// 	tmax = INFINITY;
// 	i = -1;
// 	while (++i < 3)
// 	{
// 		tmin_tmp = (((float *)box->min)[i] - ((float *)ray->origin)[i])
// 			/ ray->dir[i];
// 		tmax_tmp = (((float *)box->max)[i] - ((float *)ray->origin)[i])
// 			/ ray->dir[i];
// 		if (tmin_tmp > tmax_tmp)
// 			swap_float(&tmin_tmp, &tmax_tmp);
// 		if (tmin_tmp > tmin)
// 			tmin = tmin_tmp;
// 		if (tmax_tmp < tmax)
// 			tmax = tmax_tmp;
// 		if (tmin > tmax)
// 			return (false);
// 	}
// 	return (true);
// }
