/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fields_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:10:35 by itan              #+#    #+#             */
/*   Updated: 2023/11/10 14:11:02 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_color(t_color_c *color, t_key_events key_events)
{
	if (key_events.holding_q && key_events.holding_up)
		color->r += 0.01;
	if (key_events.holding_w && key_events.holding_up)
		color->g += 0.01;
	if (key_events.holding_e && key_events.holding_up)
		color->b += 0.01;
	if (key_events.holding_q && key_events.holding_down)
		color->r -= 0.01;
	if (key_events.holding_w && key_events.holding_down)
		color->g -= 0.01;
	if (key_events.holding_e && key_events.holding_down)
		color->b -= 0.01;
	*color = color_clamp(*color);
}

void	update_value(float *value, t_key_events key_events, t_vec3 step)
{
	printf("value: %f\n", *value);
	if (key_events.holding_up)
		*value += step.x;
	if (key_events.holding_down)
		*value -= step.x;
	if (*value < step.y)
		*value = step.y;
	else if (*value > step.z)
		*value = step.z;
}
