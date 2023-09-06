/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:02:41 by itan              #+#    #+#             */
/*   Updated: 2023/09/06 23:34:43 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_c	color_clamp(t_color_c color)
{
	if (color.a > 1.0f)
		color.a = 1.0f;
	if (color.r > 1.0f)
		color.r = 1.0f;
	if (color.g > 1.0f)
		color.g = 1.0f;
	if (color.b > 1.0f)
		color.b = 1.0f;
	if (color.a < 0.0f)
		color.a = 0.0f;
	if (color.r < 0.0f)
		color.r = 0.0f;
	if (color.g < 0.0f)
		color.g = 0.0f;
	if (color.b < 0.0f)
		color.b = 0.0f;
	return (color);
}

t_color_c	color_multiply(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = color1.a * color2.a;
	new_color.r = color1.r * color2.r;
	new_color.g = color1.g * color2.g;
	new_color.b = color1.b * color2.b;
	return (color_clamp(new_color));
}

t_color_c	color_scale(t_color_c color, float scale)
{
	t_color_c	new_color;

	new_color.a = color.a * scale;
	new_color.r = color.r * scale;
	new_color.g = color.g * scale;
	new_color.b = color.b * scale;
	return (color_clamp(new_color));
}

t_color_c	color_add(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = color1.a + color2.a;
	new_color.r = color1.r + color2.r;
	new_color.g = color1.g + color2.g;
	new_color.b = color1.b + color2.b;
	return (color_clamp(new_color));
}

t_color_c	color_average(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = (color1.a + color2.a) / 2;
	new_color.r = (color1.r + color2.r) / 2;
	new_color.g = (color1.g + color2.g) / 2;
	new_color.b = (color1.b + color2.b) / 2;
	return (color_clamp(new_color));
}
