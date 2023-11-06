/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:04:12 by itan              #+#    #+#             */
/*   Updated: 2023/11/06 15:27:58 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	transforms(t_vec3 position, t_vec3 direction,
		t_quaternion rotation, float speed)
{
	t_vec3	ret;

	ret = vec3_apply_rot(direction, rotation);
	ret = vec3_multiply(ret, speed);
	ret = vec3_add(position, ret);
	return (ret);
}

void	end_pixelate(void *rt)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)rt;
	if (minirt->render_status == RENDER_START_ANIMATION)
		minirt->render_status = RENDER_NEW_SCENE;
	if (minirt->render_status == RENDER_END_ANIMATION)
		minirt->render_status = RENDER_DONE;
}

void	render_new_scene(t_minirt *minirt)
{
	static t_animations	animation;

	if (minirt->render_status == RENDER_START_ANIMATION)
	{
		animation.frame_max = 50;
		handle_animation(minirt, &animation, NULL, end_pixelate);
		minirt->pixel_size = bazier_curves_1d_quadratic(animation.t,
				(double[3]){2, 10, 40});
		render(minirt, &thread_init);
	}
	if (minirt->render_status == RENDER_END_ANIMATION)
	{
		handle_animation(minirt, &animation, NULL, end_pixelate);
		minirt->pixel_size = bazier_curves_1d_quadratic(animation.t,
				(double[3]){40, 10, 2});
		if (minirt->pixel_size < 1)
			minirt->pixel_size = 1;
		render(minirt, &thread_init);
	}
	if (minirt->render_status == RENDER_NEW_SCENE)
	{
		start_minirt(minirt);
		minirt->render_status = RENDER_END_ANIMATION;
	}
	else if (minirt->render_status == RENDER_CURRENT_SCENE)
	{
		render_gi(minirt);
		minirt->render_status = RENDER_DONE;
	}
}

void	fly_mode_movement(t_minirt *minirt)
{
	if (!minirt->moving)
		return ;
	if (minirt->key_events.holding_w)
		minirt->cam.position = transforms(minirt->cam.position,
				minirt->cam.direction, minirt->cam.rotation_h, 2);
	if (minirt->key_events.holding_s)
		minirt->cam.position = transforms(minirt->cam.position,
				minirt->cam.direction, minirt->cam.rotation_h, -2);
	if (minirt->key_events.holding_a)
		minirt->cam.position = transforms(minirt->cam.position,
				minirt->cam.right, minirt->cam.rotation_h, 2);
	if (minirt->key_events.holding_d)
		minirt->cam.position = transforms(minirt->cam.position,
				minirt->cam.right, minirt->cam.rotation_h, -2);
	if (minirt->key_events.holding_lsh)
		minirt->cam.position = transforms(minirt->cam.position, minirt->cam.up,
				minirt->cam.rotation_h, -2);
	if (minirt->key_events.holding_sp)
		minirt->cam.position = transforms(minirt->cam.position, minirt->cam.up,
				minirt->cam.rotation_h, 2);
	render(minirt, &thread_init);
}

int	loop_hook(t_minirt *minirt)
{
	update_selected_material(minirt);
	render_new_scene(minirt);
	add_translation_plane(minirt);
	remove_translation_plane(minirt);
	if (minirt->selection.translation_plane)
		render(minirt, thread_init);
	fly_mode_movement(minirt);
	if (minirt->render_status == RESET_CAM_ANIMATION)
		reset_cam_animation(minirt);
	return (0);
}
