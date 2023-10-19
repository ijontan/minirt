/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:32:38 by itan              #+#    #+#             */
/*   Updated: 2023/10/17 18:52:50 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#if defined(__APPLE__)
void mouse_hide(t_minirt *minirt)
{
        (void)minirt;
        mlx_mouse_hide();
}
#else
void mouse_hide(t_minirt *minirt)
{
        mlx_mouse_hide(minirt->mlx, minirt->win);
}
#endif