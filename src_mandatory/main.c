/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:33 by itan              #+#    #+#             */
/*   Updated: 2023/11/03 10:39:41 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <dirent.h>

void assign_file_positions(t_file *files, int file_num)
{
	int i;
	int temp;

	i = -1;
	while (++i < file_num)
	{
		temp = SCENES_START_Y + i * 20;
		files[i].top_left.x = SCENES_START_X;
		files[i].top_left.y = temp;
		files[i].bottom_right.x = SCENES_START_X + (ft_strlen(files[i].name) * CHAR_WIDTH);
		files[i].bottom_right.y = temp + CHAR_HEIGHT;
	}
}

// *num_of_files -= 2; accounts for the files . and ..
t_file *get_files(int *num_of_files, char *dir_path)
{
	struct dirent	**name_list;
	t_file			*files;
	int				i;
	int				file_ind;

	i = -1;
	file_ind = 0;
	*num_of_files = scandir(dir_path, &name_list, NULL, NULL);
	if (*num_of_files < 0)
		perror("scandir");
	files = (t_file *)ft_calloc(*num_of_files - 2, sizeof(t_file));
	while (++i < *num_of_files)
	{
		if (name_list[i]->d_name[0] != '.')
		{
			files[file_ind].name = ft_strjoin(RT_FILE_DIR, name_list[i]->d_name);
			file_ind++;
		}
		free(name_list[i]);
	}
	free(name_list);
	*num_of_files -= 2;
	return (files);
}

void start_minirt(t_minirt *minirt)
{
	t_parse	parse_info;

	ft_memset(&parse_info, 0, sizeof(t_parse));
	printf("Parsing: %s\n", minirt->rt_file_path);
	if (!parse_rt_file(minirt->rt_file_path, &parse_info))
		return ;
	printf("\e[0;32mParsing done!!! ~~\n\e[0m");
	if (minirt->render_status == RENDER_NEW_SCENE)
		free_minirt(minirt);
	minirt->pixel_size = 3;
	minirt->amb_light = parse_info.amb_light;
	minirt->cam = parse_info.camera;
	minirt->pt_lights = parse_info.pt_lights;
	minirt->objects = parse_info.objects;
	minirt->outline_color = color_correct_new(0, 1, 1, 0.5);
	render(minirt, &ray_cast);
	printf("\e[0;32mRendering done!!! ~~\n\e[0m");
}

int	main(int ac, char **av)
{
	t_minirt	minirt;

	if (ac != 2)
		return (printf("\e[0;31mError: argument error\nExpected input format: ./minirt ~.rt\e[0m"));

	// mlx and win
	ft_memset(&minirt, 0, sizeof(t_minirt));
	minirt.mlx = mlx_init();
	minirt.win = mlx_new_window(minirt.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");
	init_hooks(&minirt);

	// getfiles
	minirt.rt_files = get_files(&minirt.file_num, "rt_files/scenes");
	assign_file_positions(minirt.rt_files, minirt.file_num);

	minirt.render_status = RENDER_FIRST_SCENE;
	minirt.rt_file_path = av[1];
	start_minirt(&minirt);

	mlx_loop(minirt.mlx);
}
