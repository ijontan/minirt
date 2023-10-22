/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:21:14 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 14:45:44 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H
# include "color.h"

/* -------------------------------- material -------------------------------- */

typedef struct s_material
{
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