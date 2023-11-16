/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material_and_uv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:34:24 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/17 01:26:09 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_uv_files(t_material *mt, t_parse *p)
{
	int	i;

	i = 11;
	if (p->info[11])
	{
		mt->texture_path = ft_strdup(p->info[i]);
		printf("texture path: %s\n", mt->texture_path);
	} else
		return ;
	if (p->info[++i])
	{
		mt->norm_map_path = ft_strdup(p->info[i]);
		printf("normal path: %s\n", mt->norm_map_path);
	} else
		return ;
	if (p->info[++i])
	{
		mt->spec_map_path = ft_strdup(p->info[i]);
		printf("specular path: %s\n", mt->spec_map_path);
	}
}

void	parse_material3(char *obj_type, int *i, t_material *mt, t_parse *p)
{
	if (p->info[++(*i)])
	{
		if (check_rgb(p->info[(*i)], p))
			mt->emission = color_correct((t_color)color_new(0, p->rgb[0],
						p->rgb[1], p->rgb[2]));
		else
			exit_parse(p->info, ft_strjoin(obj_type, "emission"), 'c');
	} else
		return ;
	if (p->info[++(*i)])
	{
		mt->shininess = ft_atof(p->info[(*i)], p);
		if (mt->shininess < 0.0)
			exit_parse(p->info, obj_type, 's');
	} else
		return ;
}

void	parse_material2(char *obj_type, int *i, t_material *mt, t_parse *p)
{
	if (p->info[++(*i)])
	{
		mt->reflective_i = ft_atof(p->info[(*i)], p);
		if (mt->reflective_i < 0.0 || mt->reflective_i > 1.0)
			exit_parse(p->info, ft_strjoin(obj_type, "reflective"), 'i');
	} else
		return ;
	if (p->info[++(*i)])
	{
		mt->diffuse_i = ft_atof(p->info[(*i)], p);
		if (mt->diffuse_i < 0.0 || mt->diffuse_i > 1.0)
			exit_parse(p->info, ft_strjoin(obj_type, "diffuse"), 'i');
	} else
		return ;
	if (p->info[++(*i)])
	{
		mt->emission_i = ft_atof(p->info[(*i)], p);
		if (mt->emission_i < 0.0 || mt->emission_i > 1.0)
			exit_parse(p->info, ft_strjoin(obj_type, "emission"), 'i');
	} else
		return ;
}

void	parse_material(char *obj_type, int i, t_material *mt, t_parse *p)
{
	mt->diffuse_i = 1.0f;
	mt->shininess = 7.0f;
	if (p->info[i])
	{
		mt->specular_i = ft_atof(p->info[i], p);
		if (mt->specular_i < 0.0 || mt->specular_i > 1.0)
			exit_parse(p->info, ft_strjoin(obj_type, "specular"), 'i');
	} else
		return ;
	if (p->info[++i])
	{
		if (check_rgb(p->info[i], p))
			mt->specular = color_correct((t_color)color_new(0, p->rgb[0],
						p->rgb[1], p->rgb[2]));
		else
			exit_parse(p->info, ft_strjoin(obj_type, "specular"), 'c');
	} else
		return ;
	parse_material2(obj_type, &i, mt, p);
	parse_material3(obj_type, &i, mt, p);
}
