/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_menu_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:39 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/08 14:53:59 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_ftoa(double num, int precision)
{
	char	*res;
	char	*tmp;
	int		num_int;

	num_int = (int)num;
	res = ft_itoa(num_int);
	tmp = ft_append(res, ".");
	num_int = (int)((num - num_int) * pow(10, precision));
	if (num_int < 0)
		num_int *= -1;
	res = ft_itoa(num_int);
	tmp = ft_append(tmp, res);
	free(res);
	return (tmp);
}

// creates strings in the format: x: ..., y: ..., z: ...
char	*create_vec3_str(char *title, t_vec3 coords)
{
	char	*res;

	res = ft_strjoin(title, "x: ");
	res = ft_strjoin(res, ft_ftoa(coords.x, 1));
	res = ft_strjoin(res, " y: ");
	res = ft_strjoin(res, ft_ftoa(coords.y, 1));
	res = ft_strjoin(res, " z: ");
	res = ft_strjoin(res, ft_ftoa(coords.z, 1));
	return (res);
}

// creates strings in the format: (x, y, z) with vec3 as a param
char	*create_vec3_str_brac(char *title, t_vec3 coords)
{
	char	*res;

	res = ft_strjoin(title, "(");
	res = ft_strjoin(res, ft_ftoa(coords.x, 1));
	res = ft_strjoin(res, ", ");
	res = ft_strjoin(res, ft_ftoa(coords.y, 1));
	res = ft_strjoin(res, ", ");
	res = ft_strjoin(res, ft_ftoa(coords.z, 1));
	res = ft_strjoin(res, ")");
	return (res);
}

// creates strings in the format: (x, y, z) with t_color as a param
char	*create_color_str_brac(char *title, t_color_c color)
{
	char	*res;
	t_color	reverted_color;

	reverted_color = color_revert(color);
	res = ft_strjoin(title, "(");
	res = ft_strjoin(res, ft_ftoa(reverted_color.rgba.r, 1));
	res = ft_strjoin(res, ", ");
	res = ft_strjoin(res, ft_ftoa(reverted_color.rgba.g, 1));
	res = ft_strjoin(res, ", ");
	res = ft_strjoin(res, ft_ftoa(reverted_color.rgba.b, 1));
	res = ft_strjoin(res, ")");
	return (res);
}
