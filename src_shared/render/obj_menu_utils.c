/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_menu_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:10:39 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 18:13:40 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// creates strings in the format: x: ..., y: ..., z: ...
char	*create_vec3_str(char *title, t_vec3 coords)
{
	char	*res;
	
	res = ft_strjoin(title, "x: ");
	res = ft_strjoin(res, ft_itoa(coords.x));
	res = ft_strjoin(res, " y: ");
	res = ft_strjoin(res, ft_itoa(coords.y));
	res = ft_strjoin(res, " z: ");
	res = ft_strjoin(res, ft_itoa(coords.z));
	return res;
}

// creates strings in the format: (x, y, z)
char	*create_vec3_str_brac(char *title, t_vec3 coords)
{
	char	*res;
	
	res = ft_strjoin(title, "(");
	res = ft_strjoin(res, ft_itoa(coords.x));
	res = ft_strjoin(res, ", ");
	res = ft_strjoin(res, ft_itoa(coords.y));
	res = ft_strjoin(res, ", ");
	res = ft_strjoin(res, ft_itoa(coords.z));
	res = ft_strjoin(res, ")");
	return res;
}

