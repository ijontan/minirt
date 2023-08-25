/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:27:57 by itan              #+#    #+#             */
/*   Updated: 2023/08/25 23:15:16 by itan             ###   ########.fr       */
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
	float	x;
	float	y;
	float	z;
}			t_vec3;

t_vec3		vec3_new(float x, float y, float z);

typedef struct s_color
{
	char	b;
	char	g;
	char	r;
	char	a;
}			t_color;

t_color		color_new(char a, char r, char g, char b);
typedef struct s_image
{
	void	*img;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
}			t_image;

void		put_pixel(t_image *image, int x, int y, unsigned int color);

typedef struct s_cam
{
	t_vec3	origin;
	t_vec3	direction;
	float	fov;
}			t_cam;

typedef struct s_sphere
{
	t_vec3	center;
	float	radius;
	t_color	color;
}			t_sphere;

#endif