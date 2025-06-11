/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:46:15 by itan              #+#    #+#             */
/*   Updated: 2025/06/11 23:10:39 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_hooks(t_minirt *minirt)
{
	mlx_hook(minirt->win, 2, 1L << 0, (void *)key_down_hook, minirt);
	mlx_hook(minirt->win, 3, 1L << 1, (void *)key_up_hook, minirt);
	mlx_hook(minirt->win, 4, 1L << 2, (void *)mouse_down_hook, minirt);
	mlx_hook(minirt->win, 5, 1L << 3, (void *)mouse_up_hook, minirt);
	mlx_hook(minirt->win, 6, 1L << 6, (void *)mouse_move_hook, minirt);
	mlx_hook(minirt->win, 17, 1L << 17, (void *)close_hook, minirt);
	mlx_loop_hook(minirt->mlx, (void *)loop_hook, minirt);
}
