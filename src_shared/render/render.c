/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:11:04 by rsoo              #+#    #+#             */
/*   Updated: 2023/10/25 01:29:26 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <dirent.h>

char	**get_rt_files(int *num_of_files)
{
	struct dirent	**name_list;
	char			**rt_files;
	int				i;

	i = -1;
	*num_of_files = scandir("rt_files/scenes", &name_list, NULL, NULL);
	rt_files = (char **)ft_calloc(*num_of_files + 1, sizeof(char *));
	if (*num_of_files < 0)
		perror("scandir");
	else
	{
		while (++i < *num_of_files)
		{
			rt_files[i] = ft_strdup(name_list[i]->d_name);
			free(name_list[i]);
		}
		free(name_list);
	}
	return (rt_files);
}

void	render_menu(t_minirt *minirt)
{
	char	*str;
	char	**rt_files;
	int		num_of_files;
	int		i;
	int		j;

	i = -1;
	j = 1;
	str = "minirt: ";
	mlx_string_put(minirt->mlx, minirt->win, 20, 20, WHITE, str);
	rt_files = get_rt_files(&num_of_files);
	while (++i < num_of_files)
		if (rt_files[i][0] != '.')
			mlx_string_put(minirt->mlx, minirt->win, 40, 20 + (20 * j++), WHITE,
				rt_files[i]);
	free_2darray(rt_files);
}

int	render(t_minirt *minirt, void (*draw_func)(t_minirt *minirt))
{
	// static bool	status;
	minirt->image = create_image(minirt);
	// mlx_clear_window(minirt->mlx, minirt->win);
	// if (!status)
	// {
	// ray_cast(minirt);
	// thread_init(minirt);
	// draw_scene(minirt);
	draw_func(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->image.image, 0,
		0);
	render_menu(minirt);
	// 	status = true;
	// }
	mlx_destroy_image(minirt->mlx, minirt->image.image);
	return (0);
}
