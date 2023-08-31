/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:03:48 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/31 09:58:20 by rsoo             ###   ########.fr       */
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

static void	exit_format_err(char **info, char *s, int n)
{
	free_2darray(info);
	printf("\e[0;31mError: %s format\nExpected Format Example: ", s);
	if (n == 1)
		printf("A 0.2 255,255,255\e[0m\n");
	else if (n == 2)
		printf("C -50,0,20 0,0,0 70\e[0m\n");
	else if (n == 3)
		printf("L -40,0,30 0.7 255,255,255\e[0m\n");
	else if (n == 4)
		printf("pl 0,0,0 0,1.0,0 255,0,225\e[0m\n");
	else if (n == 5)
		printf("sp 0,0,20 20 255,0,0\e[0m\n");
	else if (n == 6)
		printf("cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255\e[0m\n");
	exit(EXIT_FAILURE);
}

static void	check_line_format2(char *s, t_parse *p)
{
	if (!ft_strncmp(s, "sp", ft_strlen(s)) && (!check_info_size(3, p) || \
	!valid_triplet(p->info[1]) || !valid_triplet(p->info[2]) || \
	!valid_triplet(p->info[3])))
		exit_format_err(p->info, "Sphere", 4);
	else if (!ft_strncmp(s, "pl", ft_strlen(s)) && (!check_info_size(3, p) || \
	!valid_triplet(p->info[1]) || !valid_float(p->info[2]) || \
	!valid_triplet(p->info[3])))
		exit_format_err(p->info, "Plane", 5);
	else if (!ft_strncmp(s, "cy", ft_strlen(s)) && (!check_info_size(5, p) || \
	!valid_triplet(p->info[1]) || !valid_triplet(p->info[2]) || \
	!valid_float(p->info[3]) || !valid_float(p->info[4]) || \
	!valid_triplet(p->info[5])))
		exit_format_err(p->info, "Cylinder", 6);
}

void	check_line_format(char *s, t_parse *p)
{
	if (!ft_strncmp(s, "A", ft_strlen(s)) && (!check_info_size(2, p) || \
	!valid_float(p->info[1]) || !valid_triplet(p->info[2])))
		exit_format_err(p->info, "Ambient light", 1);
	else if (!ft_strncmp(s, "C", ft_strlen(s)) && (!check_info_size(3, p) || \
	!valid_triplet(p->info[1]) || !valid_triplet(p->info[2]) || \
	!valid_float(p->info[3])))
		exit_format_err(p->info, "Camera", 2);
	else if (!ft_strncmp(s, "L", ft_strlen(s)) && (!check_info_size(3, p) || \
	!valid_triplet(p->info[1]) || !valid_float(p->info[2]) || \
	!valid_triplet(p->info[3])))
		exit_format_err(p->info, "Lighting", 3);
	check_line_format2(s, p);
}


void	exit_parse(char **info, char *s, char c)
{
	if (info)
		free_2darray(info);
	printf("\e[0;31mError: %s ", s);
	if (c == 'r')
		printf("ratio out of range [0.0, 1.0]\e[0m\n");
	else if (c == 'c')
		printf("color out of range [0, 255]\e[0m\n");
	else if (c == 'd')
		printf("diameter out of range [> 0.0]\e[0m\n");
	else if (c == 'h')
		printf("height out of range [> 0.0]\e[0m\n");
	else if (c == 'a')
		printf("field of view out of range [0.0, 180.0]\e[0m\n");
	else if (c == 'n')
	{
		if (!ft_strncmp(s, "Camera", ft_strlen(s)))
			printf("normalized orientation vector ");
		else if (!ft_strncmp(s, "Plane", ft_strlen(s)))
			printf("normalized normal vector ");
		else if (!ft_strncmp(s, "Cylinder", ft_strlen(s)))
			printf("normalized vector of axis of cylinder");
		printf("out of range [-1, 1]\e[0m\n");
	}
	exit(EXIT_FAILURE);
}
