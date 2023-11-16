/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_object_info2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:55:22 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 21:57:18 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void	put_cylinder_info2(t_minirt *minirt)
{
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 340, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 380, FONT_COLOR,
		"Edit radius: v + up / down");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 400, FONT_COLOR,
		"Edit height: b + up / down");
}
