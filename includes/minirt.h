/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:27:57 by itan              #+#    #+#             */
/*   Updated: 2023/08/27 01:49:02 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include <key_linux.h>
# endif

# include "libft.h"
# include <mlx.h>

/* -------------------------------------------------------------------------- */
/*                                  Mandatory                                 */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                    Bonus                                   */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                   Shared                                   */
/* -------------------------------------------------------------------------- */
typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

t_vec3				vec3_new(float x, float y, float z);

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

# define MAX_UCHAR_2 65025;
# define DIV_MAX_UCHAR_2 0.000015384615384615385;

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

t_rgba				color_new(char a, char r, char g, char b);
t_color_c			color_tween(t_color_c color1, t_color_c color2, double t);
t_color_c			color_correct(t_color color);
t_color				color_revert(t_color_c color_c);
typedef struct s_image
{
	void			*img;
	int				pixel_bits;
	int				line_bytes;
	int				endian;
	char			*buffer;
}					t_image;

void				put_pixel(t_image *image, int x, int y, unsigned int color);

typedef struct s_cam
{
	t_vec3			origin;
	t_vec3			direction;
	float			fov;
}					t_cam;

typedef struct s_sphere
{
	t_vec3			center;
	float			radius;
	t_color			color;
}					t_sphere;

#endif