/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:02:41 by itan              #+#    #+#             */
/*   Updated: 2023/08/29 00:52:05 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_c	color_multiply(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = color1.a * color2.a;
	new_color.r = color1.r * color2.r;
	new_color.g = color1.g * color2.g;
	new_color.b = color1.b * color2.b;
	return (new_color);
}

t_color_c	color_scale(t_color_c color, float scale)
{
	t_color_c	new_color;

	new_color.a = color.a * scale;
	new_color.r = color.r * scale;
	new_color.g = color.g * scale;
	new_color.b = color.b * scale;
	return (new_color);
}

t_color_c	color_add(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = color1.a + color2.a;
	new_color.r = color1.r + color2.r;
	new_color.g = color1.g + color2.g;
	new_color.b = color1.b + color2.b;
	return (new_color);
}

t_color_c	color_average(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = (color1.a + color2.a) / 2;
	new_color.r = (color1.r + color2.r) / 2;
	new_color.g = (color1.g + color2.g) / 2;
	new_color.b = (color1.b + color2.b) / 2;
	return (new_color);
}
