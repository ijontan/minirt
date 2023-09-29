/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:05:15 by itan              #+#    #+#             */
/*   Updated: 2023/09/29 21:59:49 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void *render_gi_routine(void *data)
{
	t_minirt	*rt;

	rt = (t_minirt *)data;
	rt->image2 = create_image(rt);
	draw_scene(rt);
	mlx_put_image_to_window(rt->mlx, rt->win2, rt->image2.image, 0, 0);
	mlx_destroy_image(rt->mlx, rt->image2.image);
	return (NULL);
}

void render_gi(t_minirt *rt)
{
	pthread_t	thread;

	rt->win2 = mlx_new_window(rt->mlx, rt->cam.vp_width, rt->cam.vp_height, "Render!");
	pthread_create(&thread, NULL, render_gi_routine, rt);	
}

