/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:21:14 by itan              #+#    #+#             */
/*   Updated: 2023/10/30 15:24:43 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H
# include "color.h"
# include "image.h"

/* -------------------------------- material -------------------------------- */

typedef struct s_material
{
	char		*texture_path;
	char		*norm_map_path;
	char		*spec_map_path;
	t_image		*texture;
	t_image		*norm_map;
	t_image		*specular_map;
	t_color_c	color;
	t_color_c	emission;
	t_color_c	specular;
	float		diffuse_i;
	float		specular_i;
	float		reflective_i;
	float		shininess;
	float		emission_i;
}				t_material;

#endif