/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:20:30 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 18:13:53 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_thread_info
{
	t_minirt		*minirt;
	t_offset		start;
	t_offset		end;
	pthread_mutex_t	mutex;
}					t_thread_info;

void	*ray_cast_routine(void *data)
{
	t_offset		xy;
	t_ray			ray;
	t_color_c		color;
	t_hit_info		hit_info;
	t_thread_info	*info;

	info = (t_thread_info *)data;
	xy.y = info->start.y - 1;
	while (++xy.y < info->end.y)
	{
		xy.x = info->start.x - 1;
		while (++xy.x < info->end.x)
		{
			if (!(xy.x % info->minirt->pixel_size == 0 && xy.y
					% info->minirt->pixel_size == 0))
				continue ;
			ray = ray_primary(&info->minirt->cam, xy);
			hit_info = intersect_list(info->minirt, &ray);
			color = get_color_selection(info->minirt, &hit_info);
			fill_pixel(&info->minirt->image, xy, info->minirt->pixel_size,
				color);
		}
	}
	return (NULL);
}

void	thread_init(t_minirt *minirt)
{
	t_thread_info	*info;
	int				i;
	t_offset		size;

	i = -1;
	minirt->threads = ft_calloc(16, sizeof(pthread_t));
	info = ft_calloc(16, sizeof(t_thread_info));
	size.x = WINDOW_WIDTH / 16;
	size.y = WINDOW_HEIGHT / 16;
	while (++i < 16)
	{
		info[i].minirt = minirt;
		info[i].start.x = 0;
		info[i].start.y = i * size.y;
		info[i].end.x = WINDOW_WIDTH;
		info[i].end.y = (i + 1) * size.y;
		pthread_create(&minirt->threads[i], NULL, &ray_cast_routine, &info[i]);
	}
	i = -1;
	while (++i < 16)
	{
		pthread_join(minirt->threads[i], NULL);
	}
	free(minirt->threads);
	free(info);
}

void	*ray_trace_routine(void *data)
{
	t_offset		xy;
	t_ray			ray;
	t_thread_info	*info;

	info = (t_thread_info *)data;
	xy.y = info->start.y;
	while (xy.y < info->end.y)
	{
		xy.x = info->start.x;
		while (xy.x < info->end.x)
		{
			ray = ray_primary(&info->minirt->cam, xy);
			calculate_cycle(ray, info->minirt, xy);
			++xy.x;
		}
		++xy.y;
	}
	printf("start: %.5d, end: %.5d\n", info->start.y, info->end.y);
	return (NULL);
}

void	thread_raytrace(t_minirt *minirt)
{
	t_thread_info	*info;
	int				i;
	t_offset		size;

	i = -1;
	minirt->threads = ft_calloc(16, sizeof(pthread_t));
	info = ft_calloc(16, sizeof(t_thread_info));
	size.x = WINDOW_WIDTH / 16;
	size.y = WINDOW_HEIGHT / 16;
	while (++i < 16)
	{
		info[i].minirt = minirt;
		info[i].start.x = 0;
		info[i].start.y = i * size.y;
		info[i].end.x = WINDOW_WIDTH;
		info[i].end.y = (i + 1) * size.y;
		pthread_create(&minirt->threads[i], NULL, &ray_trace_routine, &info[i]);
	}
	i = -1;
	while (++i < 16)
	{
		pthread_join(minirt->threads[i], NULL);
	}
	free(minirt->threads);
	free(info);
}
