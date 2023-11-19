/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:12:41 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/19 17:15:57 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_files(t_minirt *minirt, char **av)
{
	minirt->rt_file_path = av[1];
	minirt->dir_path = get_dir_path(av[1]);
	minirt->rt_files = get_files(&minirt->file_num, minirt->dir_path);
	free(minirt->dir_path);
	if (!minirt->rt_files)
	{
		printf("\e[0;31mError: Directory %s not found \
/ empty\e[0m", minirt->dir_path);
		exit(EXIT_FAILURE);
	}
	assign_file_positions(minirt->rt_files, minirt->file_num);
}
