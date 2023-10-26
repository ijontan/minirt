/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:11:04 by rsoo              #+#    #+#             */
/*   Updated: 2023/10/26 22:07:30 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <dirent.h>

#define FONT_COLOR BLACK

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
	j = -1;
	while (++j < WINDOW_HEIGHT)
	{
		i = -1;
		while (++i < 250)
		{
			mlx_pixel_put(minirt->mlx, minirt->win, i, j, WHITE);
			// printf("putting pixels\n");
		}
	}

	mlx_string_put(minirt->mlx, minirt->win, 20, 20, FONT_COLOR, "w: move forward");
	mlx_string_put(minirt->mlx, minirt->win, 20, 40, FONT_COLOR, "s: move backward");
	mlx_string_put(minirt->mlx, minirt->win, 20, 60, FONT_COLOR, "a: move left");
	mlx_string_put(minirt->mlx, minirt->win, 20, 80, FONT_COLOR, "d: move right");
	mlx_string_put(minirt->mlx, minirt->win, 20, 100, FONT_COLOR, "space: move up");
	mlx_string_put(minirt->mlx, minirt->win, 20, 120, FONT_COLOR, "shift: move down");
	mlx_string_put(minirt->mlx, minirt->win, 20, 140, FONT_COLOR, "r: render scene");
	mlx_string_put(minirt->mlx, minirt->win, 20, 160, FONT_COLOR, "f: toggle mode (flying / edit)");
	mlx_string_put(minirt->mlx, minirt->win, 20, 180, FONT_COLOR, "esc: exit");
	i = -1;
	j = 1;
	str = "scenes: ";
	mlx_string_put(minirt->mlx, minirt->win, 20, 240, FONT_COLOR, str);
	rt_files = get_rt_files(&num_of_files);
	while (++i < num_of_files)
		if (rt_files[i][0] != '.')
			mlx_string_put(minirt->mlx, minirt->win, 40, 240 + (20 * j++), FONT_COLOR,
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
