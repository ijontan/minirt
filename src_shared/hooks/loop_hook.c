/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:04:12 by itan              #+#    #+#             */
/*   Updated: 2023/11/05 22:00:04 by itan             ###   ########.fr       */
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

void	render_new_scene(t_minirt *minirt)
{
	if (minirt->render_status == RENDER_NEW_SCENE)
	{
		start_minirt(minirt);
		minirt->render_status = RENDER_DONE;
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
	return (0);
}
