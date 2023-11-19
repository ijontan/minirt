/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:33 by itan              #+#    #+#             */
/*   Updated: 2023/11/19 16:32:39 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	list_iter(t_list *lst, t_minirt *rt, void (*f)(t_minirt *, void *))
{
	while (lst)
	{
		f(rt, lst->content);
		lst = lst->next;
	}
}

void	start_minirt(t_minirt *minirt)
{
	t_parse	parse_info;

	ft_memset(&parse_info, 0, sizeof(t_parse));
	printf("Parsing: %s\n", minirt->rt_file_path);
	parse_rt_file(minirt->rt_file_path, &parse_info);
	printf("\e[0;32mParsing done!!! ~~\n\e[0m");
	if (minirt->render_status == RENDER_NEW_SCENE)
		free_minirt(minirt);
	minirt->selection.selected = NULL;
	minirt->amb_light = parse_info.amb_light;
	minirt->cam = parse_info.camera;
	minirt->pt_lights = parse_info.pt_lights;
	minirt->objects = parse_info.objects;
	list_iter(minirt->objects, minirt, &load_texture);
	render(minirt, &ray_cast);
	printf("\e[0;32mRendering done!!! ~~\n\e[0m");
}

int	main(int ac, char **av)
{
	t_minirt	minirt;

	if (ac != 2)
		return (printf("\e[0;31mError: argument error\n\
Expected input format: ./minirt ~.rt\e[0m"));
	ft_memset(&minirt, 0, sizeof(t_minirt));
	minirt.pixel_size = 1;
	minirt.mlx = mlx_init();
	minirt.win = mlx_new_window(minirt.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Hello world!");
	init_hooks(&minirt);
	minirt.selection.outline_color = color_correct_new(0, 1, 1, 0.5);
	minirt.selection.plane_color = color_correct_new(0, 0.4, 0.4, 0.2);
	minirt.render_status = RENDER_FIRST_SCENE;
	init_files(&minirt, av);
	start_minirt(&minirt);
	mlx_loop(minirt.mlx);
}
