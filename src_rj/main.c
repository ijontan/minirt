/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:46:46 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 09:21:45 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool check_min_requirements(t_parse parse_info)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		if (!parse_info.mand_flag[i])
		{
			if (i == 0)
				printf("\e[0;31mError: Ambient lighting required\e[0m")
			else if (i == 1)
				printf("\e[0;31mError: Camera required\e[0m")
			else if (i == 2)
				printf("\e[0;31mError: Light required\e[0m")
			else if (i == 3)
				printf("\e[0;31mError: A sphere required\e[0m")
			else if (i == 4)
				printf("\e[0;31mError: A plane required\e[0m")
			else if (i == 5)
				printf("\e[0;31mError: A cylinder required\e[0m")
			return (false);
		}
	}
	return (true);
}

int main(int ac, char **av)
{
	t_parse parse_info;

	if (ac != 2)
		return (printf("\e[0;31mError: argument error\nExpected input: [./minirt] [~.rt]\e[0m"));
	if (!parse_rt_file(av[1], &parse_info))
		return (1);
	if (!check_min_requirements(parse_info))
		return (1);
}
