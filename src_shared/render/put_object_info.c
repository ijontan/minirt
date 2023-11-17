/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_object_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:12:33 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/17 15:16:08 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define FONT_COLOR BLACK

void	put_sphere_info(t_minirt *minirt)
{
	t_sphere	*sp;

	sp = (t_sphere *)minirt->selection.selected->object;
	minirt->selected_obj_material = sp->material;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 240, FONT_COLOR,
		"Object type: Sphere");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 260, FONT_COLOR,
		"Properties: ");
	minirt->msg = create_vec3_str("Center: ", sp->center);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 280, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	append_num_to_str(&minirt->msg, "Radius: ", \
	ft_ftoa(sp->radius, 2));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 300, FONT_COLOR,
		minirt->msg);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 340, FONT_COLOR,
		"Translate: z / x / c + left drag");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 360, FONT_COLOR,
		"Edit radius: v + up / down");
	free(minirt->msg);
}

void	put_plane_info(t_minirt *minirt)
{
	t_plane	*pl;

	pl = (t_plane *)minirt->selection.selected->object;
	minirt->selected_obj_material = pl->material;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 240, FONT_COLOR,
		"Object type: Plane");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 260, FONT_COLOR,
		"Properties: ");
	minirt->msg = create_vec3_str("Point:  ", pl->center);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 280, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	minirt->msg = create_vec3_str_brac("Normal: ", pl->rot_normal);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 300, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
}

void	put_cylinder_info(t_minirt *minirt)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)minirt->selection.selected->object;
	minirt->selected_obj_material = cy->material;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 240, FONT_COLOR,
		"Object type: Cylinder");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 260, FONT_COLOR,
		"Properties: ");
	minirt->msg = create_vec3_str("Center: ", cy->center);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 280, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	minirt->msg = create_vec3_str_brac("Axis:   ", cy->rot_axis);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 300, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	append_num_to_str(&minirt->msg, "Radius: ", ft_ftoa(cy->radius, 2));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 320, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	append_num_to_str(&minirt->msg, "Height: ", ft_ftoa(cy->height, 2));
	put_cylinder_info2(minirt);
}

void	put_cone_info2(t_minirt *minirt, t_cone *cn)
{
	append_num_to_str(&minirt->msg, "Radius: ", ft_ftoa(cn->radius, 2));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 320, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	append_num_to_str(&minirt->msg, "Height: ", ft_ftoa(cn->height, 2));
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 340, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 380, FONT_COLOR,
		"Translate: z / x / c + left drag");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 400, FONT_COLOR,
		"Rotate: z / x / c + right drag");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 420, FONT_COLOR,
		"Edit radius: v + up / down");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 440, FONT_COLOR,
		"Edit height: b + up / down");
}

void	put_cone_info(t_minirt *minirt)
{
	t_cone	*cn;

	cn = (t_cone *)minirt->selection.selected->object;
	minirt->selected_obj_material = cn->material;
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 240, FONT_COLOR,
		"Object type: Cone");
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X, 260, FONT_COLOR,
		"Properties: ");
	minirt->msg = create_vec3_str("Tip:    ", cn->tip);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 280, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	minirt->msg = create_vec3_str_brac("Axis:   ", cn->rot_axis);
	mlx_string_put(minirt->mlx, minirt->win, OBJ_START_X + 10, 300, FONT_COLOR,
		minirt->msg);
	free(minirt->msg);
	put_cone_info2(minirt, cn);
}
