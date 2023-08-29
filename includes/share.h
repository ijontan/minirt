/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:22:20 by itan              #+#    #+#             */
/*   Updated: 2023/08/29 13:23:26 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARE_H
# define SHARE_H

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct s_rgba
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_rgba;

typedef union u_color
{
	unsigned int	as_int;
	t_rgba			rgba;
}					t_color;

/**
 * @brief Color with correction and in float
 *
 */
typedef struct s_color_c
{
	float			b;
	float			g;
	float			r;
	float			a;
}					t_color_c;
#endif