/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_show.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:35:13 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 13:44:08 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#if defined(__APPLE__)

void	mouse_show(t_minirt *minirt)
{
	(void)minirt;
	mlx_mouse_show();
}
#else

void	mouse_show(t_minirt *minirt)
{
	mlx_mouse_show(minirt->mlx, minirt->win);
}
#endif