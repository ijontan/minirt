/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:35:36 by itan              #+#    #+#             */
/*   Updated: 2023/10/17 18:47:24 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#if defined(__APPLE__)
void mouse_move(t_minirt *minirt, int x, int y)
{
    mlx_mouse_move(minirt->win, x, y);
}
#else
void mouse_move(t_minirt *minirt, int x, int y)
{
    mlx_mouse_move(minirt->mlx, minirt->win, x, y);
}
#endif
