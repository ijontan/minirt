/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:33 by itan              #+#    #+#             */
/*   Updated: 2023/09/04 15:59:00 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
Checks if all objects are present:
- ambient lighting
- camera
- lighting
- sphere
- plane
- cylinder
*/
static bool check_min_requirements(t_parse parse_info)
{	
	int i;

	i = -1;
	while (++i < 6)
	{
		if (!parse_info.mand_flag[i])
		{
			printf("\e[0;31mError: Missing Object: ");
			if (i == 0)
				printf("Ambient lighting required\e[0m");
			else if (i == 1)
				printf("Camera required\e[0m");
			else if (i == 2)
				printf("Lighting required\e[0m");
			else if (i == 3)
				printf("A sphere required\e[0m");
			else if (i == 4)
				printf("A plane required\e[0m");
			else if (i == 5)
				printf("A cylinder required\e[0m");
			return (false);
		}
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_parse parse_info;

	if (ac != 2)
		return (printf("\e[0;31mError: argument error\nExpected input format: ./minirt ~.rt\e[0m"));
	if (!parse_rt_file(av[1], &parse_info))
		return (1);
	if (!check_min_requirements(parse_info))
		return (1);
	return (0);
}
