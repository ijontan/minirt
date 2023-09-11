/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:05:13 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 15:38:11 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgba	color_new(char a, char r, char g, char b)
{
	return ((t_rgba){b, g, r, a});
}

/**
 * @brief new color with correction and in float
 * 
 * @param a not real alpha but transparency which is 1 - opacity
 * @param r red intensity in float
 * @param g green intensity in float
 * @param b blue intensity in float
 * @return t_color_c 
 */
t_color_c	color_correct_new(float a, float r, float g, float b)
{
	t_color_c	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}
