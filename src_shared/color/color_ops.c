/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:02:41 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 15:36:54 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief clamp corrected color values to 0.0 - 1.0
 * 
 * @param color 
 * @return t_color_c 
 */
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

/**
 * @brief multiply two corrected colors
 * 
 * @param color1 
 * @param color2 
 * @return t_color_c 
 */
t_color_c	color_multiply(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = color1.a * color2.a;
	new_color.r = color1.r * color2.r;
	new_color.g = color1.g * color2.g;
	new_color.b = color1.b * color2.b;
	return (color_clamp(new_color));
}

/**
 * @brief scale a corrected color by a float
 * 
 * @param color 
 * @param scale 
 * @return t_color_c 
 */
t_color_c	color_scale(t_color_c color, float scale)
{
	t_color_c	new_color;

	new_color.a = color.a * scale;
	new_color.r = color.r * scale;
	new_color.g = color.g * scale;
	new_color.b = color.b * scale;
	return (color_clamp(new_color));
}

/**
 * @brief add two corrected colors
 * 
 * @param color1 
 * @param color2 
 * @return t_color_c 
 */
t_color_c	color_add(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = color1.a + color2.a;
	new_color.r = color1.r + color2.r;
	new_color.g = color1.g + color2.g;
	new_color.b = color1.b + color2.b;
	return (new_color);
}

/**
 * @brief average two corrected colors
 * 
 * @param color1 
 * @param color2 
 * @return t_color_c 
 */
t_color_c	color_average(t_color_c color1, t_color_c color2)
{
	t_color_c	new_color;

	new_color.a = (color1.a + color2.a) * 0.5f;
	new_color.r = (color1.r + color2.r) * 0.5f;
	new_color.g = (color1.g + color2.g) * 0.5f;
	new_color.b = (color1.b + color2.b) * 0.5f;
	return (color_clamp(new_color));
}
