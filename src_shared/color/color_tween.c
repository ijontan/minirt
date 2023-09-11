/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tween.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 00:28:04 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 15:35:05 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief linear interpolation between two colors
 * 
 * @param color1 
 * @param color2 
 * @param t 
 * @return t_color_c 
 */
t_color_c	color_tween(t_color_c color1, t_color_c color2, double t)
{
	t_color_c	color;

	color = (t_color_c){
		color1.b * (1 - t) + color2.b * t,
		color1.g * (1 - t) + color2.g * t,
		color1.r * (1 - t) + color2.r * t,
		color1.a * (1 - t) + color2.a * t,
	};
	return (color);
}
