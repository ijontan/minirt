/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:03:48 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 20:27:58 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_info_size(int size, t_parse *p)
{
	int	i;

	i = 0;
	while (p->info[i])
		i++;
	if (i == size)
		return (true);
	return (false);
}

static void	exit_format_err(char **info, char *s, int type)
{
	free_2darray(info);
	printf("\e[0;31mError: %s format\nExpected Format Example: ", s);
	if (type == AMB_LIGHT)
		printf("A 0.2 255,255,255\e[0m\n");
	else if (type == CAM)
		printf("C -50,0,20 0,0,0 70\e[0m\n");
	else if (type == LIGHT)
		printf("L -40,0,30 0.7 255,255,255\e[0m\n");
	else if (type == SPHERE)
		printf("sp 0,0,20 20 255,0,0\e[0m\n");
	else if (type == PLANE)
		printf("pl 0,0,0 0,1.0,0 255,0,225\e[0m\n");
	else if (type == CYLINDER)
		printf("cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255\e[0m\n");
	exit(EXIT_FAILURE);
}

static void	check_line_format2(int type, t_parse *p)
{
	if (type == SPHERE && (!valid_triplet(p->info[1]) || \
	!valid_float(p->info[2]) || !valid_triplet(p->info[3])))
		exit_format_err(p->info, "Sphere", SPHERE);
	else if (type == PLANE && (!valid_triplet(p->info[1]) || \
	!valid_triplet(p->info[2]) || !valid_triplet(p->info[3])))
		exit_format_err(p->info, "Plane", PLANE);
	else if (type == CYLINDER && (!valid_triplet(p->info[1])
			|| !valid_triplet(p->info[2]) || !valid_float(p->info[3])
			|| !valid_float(p->info[4]) || !valid_triplet(p->info[5])))
		exit_format_err(p->info, "Cylinder", CYLINDER);
}

/*
checks if the info in the .rt file is in the correct format by checking:
- number of info (A 0.2 255,255,255 has 3 blocks of info)
- check if a float is in correct format
- check if a triplet (255,255,255) is in correct format
*/
void	check_line_format(int type, t_parse *p)
{
	if (type == AMB_LIGHT && (!check_info_size(3, p) || !valid_float(p->info[1])
			|| !valid_triplet(p->info[2])))
		exit_format_err(p->info, "Ambient light", AMB_LIGHT);
	else if (type == CAM && (!check_info_size(4, p)
			|| !valid_triplet(p->info[1]) || !valid_triplet(p->info[2])
			|| !valid_float(p->info[3])))
		exit_format_err(p->info, "Camera", CAM);
	else if (type == LIGHT && (!check_info_size(4, p) || \
	!valid_triplet(p->info[1]) || !valid_float(p->info[2]) || \
	!valid_triplet(p->info[3])))
		exit_format_err(p->info, "Lighting", LIGHT);
	check_line_format2(type, p);
}
