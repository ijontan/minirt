/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:46:15 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 13:14:44 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_hooks(t_minirt *minirt)
{
	mlx_hook(minirt->win, 2, 1L << 0, key_down_hook, minirt);
	mlx_hook(minirt->win, 3, 1L << 1, key_up_hook, minirt);
	mlx_hook(minirt->win, 4, 1L << 2, mouse_down_hook, minirt);
	mlx_hook(minirt->win, 5, 1L << 3, mouse_up_hook, minirt);
	mlx_hook(minirt->win, 6, 1L << 6, mouse_move_hook, minirt);
	mlx_hook(minirt->win, 17, 1L << 17, close_hook, minirt);
	mlx_loop_hook(minirt->mlx, loop_hook, minirt);
}
