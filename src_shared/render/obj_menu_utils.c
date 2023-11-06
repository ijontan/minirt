/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_menu_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:39 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 20:21:20 by itan             ###   ########.fr       */
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

// creates strings in the format: (x, y, z)
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
