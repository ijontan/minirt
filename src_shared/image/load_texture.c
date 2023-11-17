/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 01:36:00 by itan              #+#    #+#             */
/*   Updated: 2023/11/17 01:42:23 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_image	*load_image_alloc(t_minirt *rt, char *path)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	*img = load_image(rt, path);
	return (img);
}

void	load_texture(t_minirt *rt, void *content)
{
	t_object	*obj;
	t_material	*mt;

	obj = (t_object *)content;
	if (obj->type == SPHERE)
		mt = &((t_sphere *)obj->object)->material;
	else if (obj->type == PLANE)
		mt = &((t_plane *)obj->object)->material;
	else if (obj->type == CYLINDER)
		mt = &((t_cylinder *)obj->object)->material;
	else
		return ;
	if (mt->texture_path)
		mt->texture = load_image_alloc(rt, mt->texture_path);
	if (mt->norm_map_path)
		mt->norm_map = load_image_alloc(rt, mt->norm_map_path);
	if (mt->spec_map_path)
		mt->specular_map = load_image_alloc(rt, mt->spec_map_path);
}
