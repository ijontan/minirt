/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:26:36 by itan              #+#    #+#             */
/*   Updated: 2023/11/06 15:10:36 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONS_H
# define ANIMATIONS_H
# include "libft.h"
# include "vec3.h"

typedef struct s_animations
{
	unsigned int	frame;
	unsigned int	frame_max;
	double			t;
}					t_animations;

typedef void		(*t_a_func)(void *);

void				handle_animation(void *rt, t_animations *animation,
						t_a_func init, t_a_func end_func);
#endif
