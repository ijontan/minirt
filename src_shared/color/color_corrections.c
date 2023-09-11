/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_corrections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:27:33 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 15:41:05 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CHAR_SQ_DIV 0.0000153787f
#define CHAR_SQ 65025

/**
 * @brief correct color values to from 0-255 to 0-1
 * 
 * @param color 
 * @return t_color_c 
 */
t_color_c	color_correct(t_color color)
{
	t_color_c	color_corrected;

	color_corrected.r = ft_power(color.rgba.r, 2) * CHAR_SQ_DIV;
	color_corrected.g = ft_power(color.rgba.g, 2) * CHAR_SQ_DIV;
	color_corrected.b = ft_power(color.rgba.b, 2) * CHAR_SQ_DIV;
	color_corrected.a = ft_power(color.rgba.a, 2) * CHAR_SQ_DIV;
	return (color_corrected);
}

/**
 * @brief revert color values to from 0-1 to 0-255
 * 
 * @param color_c 
 * @return t_color 
 */
t_color	color_revert(t_color_c color_c)
{
	t_color	color;

	color.rgba = (t_rgba){
		ft_sqrt(color_c.b * CHAR_SQ),
		ft_sqrt(color_c.g * CHAR_SQ),
		ft_sqrt(color_c.r * CHAR_SQ),
		ft_sqrt(color_c.a * CHAR_SQ),
	};
	return (color);
}
