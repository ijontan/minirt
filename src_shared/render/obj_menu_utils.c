/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_menu_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:39 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 18:15:33 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	append_num_to_str(char **msg, char *str, char *num)
{
	*msg = ft_strjoin(str, num);
	free(num);
}

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
	char	*num;

	res = ft_strjoin(title, "x: ");
	num = ft_ftoa(coords.x, 1);
	res = ft_append(res, num);
	free(num);
	res = ft_append(res, " y: ");
	num = ft_ftoa(coords.y, 1);
	res = ft_append(res, num);
	free(num);
	res = ft_append(res, " z: ");
	num = ft_ftoa(coords.z, 1);
	res = ft_append(res, num);
	free(num);
	return (res);
}

// creates strings in the format: (x, y, z) with vec3 as a param
char	*create_vec3_str_brac(char *title, t_vec3 coords)
{
	char	*res;
	char	*num;

	res = ft_strjoin(title, "(");
	num = ft_ftoa(coords.x, 1);
	res = ft_append(res, num);
	free(num);
	res = ft_append(res, ", ");
	num = ft_ftoa(coords.y, 1);
	res = ft_append(res, num);
	free(num);
	res = ft_append(res, ", ");
	num = ft_ftoa(coords.z, 1);
	res = ft_append(res, num);
	free(num);
	res = ft_append(res, ")");
	return (res);
}

// creates strings in the format: (x, y, z) with t_color as a param
char	*create_color_str_brac(char *title, t_color_c color)
{
	char	*res;
	char	*num;
	t_color	reverted_color;

	reverted_color = color_revert(color);
	res = ft_strjoin(title, "(");
	num = ft_ftoa(reverted_color.rgba.r, 1);
	res = ft_append(res, num);
	free(num);
	res = ft_append(res, ", ");
	num = ft_ftoa(reverted_color.rgba.r, 1);
	res = ft_append(res, num);
	free(num);
	res = ft_append(res, ", ");
	num = ft_ftoa(reverted_color.rgba.r, 1);
	res = ft_append(res, num);
	free(num);
	res = ft_append(res, ")");
	return (res);
}
