/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:20:30 by itan              #+#    #+#             */
/*   Updated: 2023/09/27 22:20:39 by itan             ###   ########.fr       */
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
			{
				color = get_color(info->minirt, &hit_info);
				put_pixel(&info->minirt->image, (t_offset){.x = x, .y = y},
					color_revert(color).as_int);
			}
			else
			{
				put_pixel(&info->minirt->image, (t_offset){.x = x, .y = y},
					color_revert(info->minirt->amb_light.color).as_int);
			}
			i = -1;
			while (info->minirt->moving && ++i < pixel_size && x + i < 1280)
			{
				j = -1;
				while (++j < pixel_size && y + j < 720)
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
	minirt->threads = ft_calloc(7, sizeof(pthread_t));
	info = ft_calloc(7, sizeof(t_thread_info));
	size.x = 1280 / 7;
	size.y = 720 / 7;
	while (++i < 7)
	{
		info[i].minirt = minirt;
		info[i].start.x = 0;
		info[i].start.y = i * size.y;
		info[i].end.x = 1280;
		info[i].end.y = (i + 1) * size.y;
		if (i == 6)
		{
			info[i].end.x = 1280;
			info[i].end.y = 720;
		}
		pthread_create(&minirt->threads[i], NULL, &ray_cast_routine, &info[i]);
	}
	i = -1;
	while (++i < 7)
	{
		pthread_join(minirt->threads[i], NULL);
	}
	free(minirt->threads);
	free(info);
}
