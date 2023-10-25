/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:05:15 by itan              #+#    #+#             */
/*   Updated: 2023/10/25 15:38:34 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	*render_gi_routine(void *data)
// {
// 	t_minirt	*rt;
// 	void		*mlx;

// 	rt = (t_minirt *)data;
// 	mlx = mlx_init();
// 	rt->image2 = create_image(rt);
// 	rt->win2 = mlx_new_window(mlx, rt->cam.vp_width, rt->cam.vp_height,
// 			"Render!");
// 	draw_scene(rt);
// 	mlx_put_image_to_window(mlx, rt->win2, rt->image2.image, 0, 0);
// 	mlx_destroy_image(mlx, rt->image2.image);
// 	mlx_loop(mlx);
// 	return (NULL);
// }

void	render_gi(t_minirt *rt)
{
	render(rt, thread_raytrace);
	rt->moving = false;
}
