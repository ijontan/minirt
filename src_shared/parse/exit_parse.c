/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:34:32 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/17 11:34:32 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_parse_material(char **info, char *s, char c)
{
	if (info)
		free_2darray(info);
	printf("\e[0;31mError: %s ", s);
	if (c == 'i')
		printf("index out of range [0.0, 1.0]\e[0m\n");
	else if (c == 'c')
		printf("color out of range [0, 255]\e[0m\n");
	free(s);
	exit(EXIT_FAILURE);
}

void	exit_parse2(char *s, char c)
{
	if (c == 'n')
	{
		if (!ft_strncmp(s, "Camera", ft_strlen(s)))
			printf("normalized orientation vector ");
		else if (!ft_strncmp(s, "Plane", ft_strlen(s)))
			printf("normalized normal vector ");
		else if (!ft_strncmp(s, "Cylinder", ft_strlen(s)))
			printf("normalized vector of axis of cylinder");
		else if (!ft_strncmp(s, "Cone", ft_strlen(s)))
			printf("normalized vector of axis of cone ");
		printf("out of range [-1, 1]\e[0m\n");
	}
}

void	exit_parse(char **info, char *s, char c)
{
	if (info)
		free_2darray(info);
	printf("\e[0;31mError: %s ", s);
	if (c == 'r')
		printf("ratio out of range [0.0, 1.0]\e[0m\n");
	else if (c == 'i')
		printf("index out of range [0.0, 1.0]\e[0m\n");
	else if (c == 'c')
		printf("color out of range [0, 255]\e[0m\n");
	else if (c == 'd')
		printf("diameter out of range [> 0.0]\e[0m\n");
	else if (c == 'h')
		printf("height out of range [> 0.0]\e[0m\n");
	else if (c == 's')
		printf("shininess out of range [> 0.0]\e[0m\n");
	else if (c == 'a')
		printf("field of view out of range [0.0, 180.0]\e[0m\n");
	exit_parse2(s, c);
	exit(EXIT_FAILURE);
}
