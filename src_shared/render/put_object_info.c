/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_object_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:12:33 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 18:29:47 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void put_sphere_info(t_minirt *minirt)
{
	t_sphere *sp;

	sp = (t_sphere *)minirt->selection.selected->object;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 240, FONT_COLOR,
		"Object type: Sphere");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 260, FONT_COLOR,
		"Properties: ");
	minirt->msg = create_vec3_str("Center: ", sp->center);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 280, FONT_COLOR, minirt->msg);
	free(minirt->msg);
	minirt->msg = ft_strjoin("Radius: ", ft_itoa(sp->radius));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 300, FONT_COLOR, minirt->msg);
	free(minirt->msg);
}

void put_plane_info(t_minirt *minirt)
{
	t_plane *pl;

	pl = (t_plane *)minirt->selection.selected->object;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 240, FONT_COLOR,
		"Object type: Plane");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 260, FONT_COLOR,
		"Properties: ");
	minirt->msg = create_vec3_str("Point:  ", pl->center);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 280, FONT_COLOR, minirt->msg);
	free(minirt->msg);
	minirt->msg = create_vec3_str_brac("Normal: ", pl->normal);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 300, FONT_COLOR, minirt->msg);
	free(minirt->msg);
}

void put_cylinder_info(t_minirt *minirt)
{
	t_cylinder *cy;

	cy = (t_cylinder *)minirt->selection.selected->object;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 240, FONT_COLOR,
		"Object type: Cylinder");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 260, FONT_COLOR,
		"Properties: ");
	minirt->msg = create_vec3_str("Center: ", cy->center);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 280, FONT_COLOR, minirt->msg);
	free(minirt->msg);
	minirt->msg = create_vec3_str_brac("Axis:   ", cy->norm_axis);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 300, FONT_COLOR, minirt->msg);
	free(minirt->msg);
	minirt->msg = ft_strjoin("Radius: ", ft_itoa(cy->radius));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 320, FONT_COLOR, minirt->msg);
	free(minirt->msg);
	minirt->msg = ft_strjoin("Height: ", ft_itoa(cy->height));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 340, FONT_COLOR, minirt->msg);
	free(minirt->msg);
}

void put_cone_info(t_minirt *minirt)
{
	t_cone	*cn;

	cn = (t_cone *)minirt->selection.selected->object;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 240, FONT_COLOR,
		"Object type: Cone");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X, 260, FONT_COLOR,
		"Properties: ");
	minirt->msg = create_vec3_str("Tip:    ", cn->tip);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 280, FONT_COLOR, minirt->msg);
	free(minirt->msg);
	minirt->msg = create_vec3_str_brac("Axis:   ", cn->norm_axis);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 300, FONT_COLOR, minirt->msg);
	free(minirt->msg);
	minirt->msg = ft_strjoin("Radius: ", ft_itoa(cn->radius));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 320, FONT_COLOR, minirt->msg);
	free(minirt->msg);
	minirt->msg = ft_strjoin("Height: ", ft_itoa(cn->height));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_MENU_START_X + 20, 340, FONT_COLOR, minirt->msg);
	free(minirt->msg);
}
