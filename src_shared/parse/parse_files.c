/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:26:00 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/17 16:36:38 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <dirent.h>

char	*get_dir_path(char *path)
{
	int		path_ind;
	char	*dir_path;
	int		i;

	path_ind = ft_strlen(path) - 1;
	i = 0;
	while (path[path_ind] != '/')
		path_ind--;
	dir_path = ft_strdup(path);
	dir_path[++path_ind] = '\0';
	return (dir_path);
}

void	assign_file_positions(t_file *files, int file_num)
{
	int	i;
	int	temp;

	i = -1;
	while (++i < file_num)
	{
		temp = SCENES_START_Y + i * 20;
		files[i].top_left.x = SCENES_START_X;
		files[i].top_left.y = temp;
		files[i].bottom_right.x = SCENES_START_X + (ft_strlen(files[i].name)
				* CHAR_WIDTH);
		files[i].bottom_right.y = temp + CHAR_HEIGHT;
	}
}

// *num_of_files -= 2; accounts for the files . and ..
t_file	*get_files(int *num_of_files, char *dir_path)
{
	struct dirent	**name_list;
	t_file			*files;
	int				i;
	int				file_ind;

	i = -1;
	file_ind = 0;
	*num_of_files = scandir(dir_path, &name_list, NULL, NULL);
	if (*num_of_files < 0)
		return (NULL);
	files = (t_file *)ft_calloc(*num_of_files - 2, sizeof(t_file));
	while (++i < *num_of_files)
	{
		if (name_list[i]->d_name[0] != '.')
		{
			files[file_ind].name = ft_strjoin(dir_path,
					name_list[i]->d_name);
			file_ind++;
		}
		free(name_list[i]);
	}
	free(name_list);
	*num_of_files -= 2;
	return (files);
}

void	init_files(t_minirt *minirt, char **av)
{
	minirt->rt_file_path = av[1];
	minirt->dir_path = get_dir_path(av[1]);
	minirt->rt_files = get_files(&minirt->file_num, minirt->dir_path);
	free(minirt->dir_path);
	if (!minirt->rt_files)
	{
		printf("\e[0;31mError: Directory %s not found\e[0m", minirt->dir_path);
		exit(EXIT_FAILURE);
	}
	assign_file_positions(minirt->rt_files, minirt->file_num);
}
