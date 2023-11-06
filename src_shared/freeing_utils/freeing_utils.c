/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:39:51 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/06 14:17:29 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	del_light(void *content)
{
	if (content)
		free(content);
}

void	del_obj(void *content)
{
	t_object	*obj;
	t_material	mt;

	obj = (t_object *)content;
	if (!obj)
		return ;
	if (obj->type == SPHERE)
		mt = ((t_sphere *)obj->object)->material;
	else if (obj->type == PLANE)
		mt = ((t_plane *)obj->object)->material;
	else if (obj->type == CYLINDER)
		mt = ((t_cylinder *)obj->object)->material;
	else if (obj->type == CONE)
		mt = ((t_cone *)obj->object)->material;
	if (mt.texture_path)
		free(mt.texture_path);
	if (mt.norm_map_path)
		free(mt.norm_map_path);
	if (mt.spec_map_path)
		free(mt.spec_map_path);
	free(obj->object);
	free(obj);
}

void	free_minirt(t_minirt *minirt)
{
	ft_lstclear(&minirt->pt_lights, del_light);
	ft_lstclear(&minirt->objects, del_obj);
	if (minirt->render_status == RENDER_DONE)
	{
		mlx_destroy_window(minirt->mlx, minirt->win);
		minirt->win = NULL;
		free(minirt->rt_files);
	}
}
