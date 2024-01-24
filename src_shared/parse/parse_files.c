/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:26:00 by rsoo              #+#    #+#             */
/*   Updated: 2024/01/24 15:53:01 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <dirent.h>

char	*get_dir_path(char *path)
{
	int		path_ind;
	char	*dir_path;

	path_ind = ft_strlen(path) - 1;
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

int	get_num_of_redundant_files(struct dirent **name_list, int n)
{
	int	num;
	int	i;

	num = 0;
	i = -1;
	while (++i < n)
		if (name_list[i]->d_name[0] == '.')
			num++;
	return (num);
}

t_file	*get_files(int *num_of_files, char *dir_path)
{
	struct dirent	**name_list;
	t_file			*files;
	int				i;
	int				file_ind;
	int				n;

	i = -1;
	file_ind = 0;
	*num_of_files = scandir(dir_path, &name_list, NULL, NULL);
	if (*num_of_files < 0)
		return (NULL);
	n = get_num_of_redundant_files(name_list, *num_of_files);
	files = (t_file *)ft_calloc(*num_of_files - n, sizeof(t_file));
	while (++i < *num_of_files)
	{
		if (name_list[i]->d_name[0] != '.')
			files[file_ind++].name = ft_strjoin(dir_path, name_list[i]->d_name);
		free(name_list[i]);
	}
	free(name_list);
	*num_of_files -= n;
	return (files);
}

void	check_valid_file_name(char *infile_name)
{
	char	*extension;
	char	*tmp;
	int		infile_len;

	extension = ft_strdup(".rt");
	infile_len = ft_strlen(infile_name);
	tmp = infile_name + (infile_len - 3);
	if (ft_strncmp(tmp, extension, 3))
	{
		printf("\e[0;31mError: File %s is not allowed. It must end with the \
.rt extension\e[0m\n", infile_name);
		free(extension);
		exit(EXIT_FAILURE);
	}
	free(extension);
}
