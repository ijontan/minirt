/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:20:30 by itan              #+#    #+#             */
/*   Updated: 2023/11/06 12:44:20 by itan             ###   ########.fr       */
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
	int				x;
	int				y;
	t_ray			ray;
	t_color_c		color;
	t_hit_info		hit_info;
	t_thread_info	*info;
	int				pixel_size;
	int				i;
	int				j;

	info = (t_thread_info *)data;
	pixel_size = info->minirt->pixel_size;
	y = info->start.y;
	while (y < info->end.y)
	{
		x = info->start.x;
		while (x < info->end.x)
		{
			if ((x % pixel_size != 0 || y % pixel_size != 0))
			{
				++x;
				continue ;
			}
			ft_memset(&ray, 0, sizeof(t_ray));
			ray = ray_primary(&info->minirt->cam, (t_offset){.x = x, .y = y});
			hit_info = intersect_list(info->minirt, &ray);
			color = color_correct_new(0, 0, 0, 0);
			if (hit_info.hit)
				color = get_color(info->minirt, &hit_info);
			if (hit_info.hit_selection_plane)
				color = color_add(color, info->minirt->selection.plane_color);
			if (hit_info.hit_rotation_plane)
				color = color_add(color, info->minirt->selection.plane_color);
			color = color_clamp(color);
			put_pixel(&info->minirt->image, (t_offset){.x = x, .y = y},
				color_revert(color).as_int);
			i = -1;
			while (++i < pixel_size && x + i < WINDOW_WIDTH)
			{
				j = -1;
				while (++j < pixel_size && y + j < WINDOW_HEIGHT)
				{
					put_pixel(&info->minirt->image, (t_offset){.x = x + i,
						.y = y + j}, color_revert(color).as_int);
				}
			}
			++x;
		}
		++y;
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
	int				x;
	int				y;
	t_ray			ray;
	t_color_c		color;
	t_thread_info	*info;
	int				cycle;
	unsigned int	state;
	t_color_c		incoming_light;

	info = (t_thread_info *)data;
	y = info->start.y;
	while (y < info->end.y)
	{
		x = info->start.x;
		while (x < info->end.x)
		{
			color = color_correct_new(0, 0, 0, 0);
			cycle = -1;
			ray = ray_primary(&info->minirt->cam, (t_offset){.x = x, .y = y});
			state = (unsigned int)((x + y * WINDOW_WIDTH));
			while (++cycle < 50)
			{
				incoming_light = ray_tracing(ray, info->minirt, &state);
				color = color_add(color, incoming_light);
			}
			color = color_scale(color, 1 / (float)cycle);
			put_pixel(&info->minirt->image, (t_offset){.x = x, .y = y},
				color_revert(color).as_int);
			++x;
		}
		++y;
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
