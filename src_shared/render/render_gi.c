/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:05:15 by itan              #+#    #+#             */
/*   Updated: 2023/11/17 01:30:58 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_gi(t_minirt *rt)
{
	rt->selection.selected = NULL;
	render(rt, &thread_init);
	rt->render_status = RENDER_DONE;
	render(rt, thread_raytrace);
	rt->moving = false;
	rt->selection.selected = NULL;
}
