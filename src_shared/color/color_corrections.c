/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_corrections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:27:33 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 01:51:12 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_c	color_correct(t_color color)
{
	t_color_c	color_corrected;

	color_corrected.r = ft_power(color.rgba.r, 2) / 65025;
	color_corrected.g = ft_power(color.rgba.g, 2) / 65025;
	color_corrected.b = ft_power(color.rgba.b, 2) / 65025;
	color_corrected.a = ft_power(color.rgba.a, 2) / 65025;
	return (color_corrected);
}

t_color	color_revert(t_color_c color_c)
{
	t_color	color;

	color.rgba = (t_rgba){
		ft_sqrt(color_c.b * 65025),
		ft_sqrt(color_c.g * 65025),
		ft_sqrt(color_c.r * 65025),
		ft_sqrt(color_c.a * 65025),
	};
	return (color);
}
