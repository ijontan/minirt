/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:20:50 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 14:46:13 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
/* ---------------------------------- color --------------------------------- */

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

t_color_c			color_correct_new(float a, float r, float g, float b);
t_color_c			color_clamp(t_color_c color);
t_color_c			color_multiply(t_color_c color1, t_color_c color2);
t_color_c			color_scale(t_color_c color, float scale);
t_color_c			color_add(t_color_c color1, t_color_c color2);
t_color_c			color_average(t_color_c color1, t_color_c color2);
t_rgba				color_new(char a, char r, char g, char b);
t_color_c			color_tween(t_color_c color1, t_color_c color2, double t);
t_color_c			color_correct(t_color color);
t_color				color_revert(t_color_c color_c);

#endif