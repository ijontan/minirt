/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:31:04 by itan              #+#    #+#             */
/*   Updated: 2023/11/10 15:16:10 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_H
# define CAM_H
# include "libft.h"
# include "vec3.h"

/* ----------------------------------- cam ---------------------------------- */

/**
 * @brief Camera struct
 *
 * @param origin camera position
 * @param direction camera direction or forward direction
 * @param up up direction
 * @param right right direction
 * @param fov field of view
 * @param vp_width viewport width
 * @param vp_height viewport height
 */
typedef struct s_cam
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	up;
	t_vec3	right;
	t_vec3	position;
	float	yaw;
	float	pitch;
	float	fov;
	int		vp_width;
	int		vp_height;
}			t_cam;

void		cam_init(t_cam *cam);

#endif