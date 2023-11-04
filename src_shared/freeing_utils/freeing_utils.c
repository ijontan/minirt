/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:39:51 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/03 10:58:28 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void del(void *content)
{
	if (content)
		free(content);
}

void free_minirt(t_minirt *minirt)
{
	ft_lstclear(&minirt->pt_lights, del);
	ft_lstclear(&minirt->objects, del);
	if (minirt->render_status == RENDER_DONE)
	{
		mlx_destroy_window(minirt->mlx, minirt->win);
		minirt->win = NULL;
		free(minirt->rt_files);
	}
}
