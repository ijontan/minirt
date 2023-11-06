/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animates.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:33:40 by itan              #+#    #+#             */
/*   Updated: 2023/11/06 15:18:35 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief This function is used to handle animation.
 * 
 * @param rt usually t_minirt but can be any struct.
 * @param animation the t_animations struct for config.
 * @param init the function to run when animation starts.
 * @param end_func the function to run when animation ends.
*/
void	handle_animation(void *rt, t_animations *animation, t_a_func init,
		t_a_func end_func)
{
	if (animation->frame == 0 && init)
		init(rt);
	if (animation->frame < animation->frame_max)
		animation->frame++;
	else
	{
		if (end_func)
			end_func(rt);
		animation->frame = 0;
		return ;
	}
	animation->t = (double)animation->frame / (double)animation->frame_max;
}
