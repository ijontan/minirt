/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:59:54 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 17:14:03 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cam_init(t_cam *cam)
{
	ft_memset(cam, 0, sizeof(t_cam));
	cam->origin = vec3_new(0, 0, 0);
	cam->direction = vec3_new(0, 0, 1);
	cam->fov = 0.9f;
	cam->up = vec3_new(0, 1, 0);
	cam->vp_width = WINDOW_WIDTH;
	cam->vp_height = WINDOW_HEIGHT;
	cam->position = vec3_new(0, 0, 0);
	cam->yaw = 0;
	cam->pitch = 0;
	cam->right = vec3_cross(cam->direction, cam->up);
}
