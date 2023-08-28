/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:27:57 by itan              #+#    #+#             */
/*   Updated: 2023/08/29 01:59:49 by itan             ###   ########.fr       */
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
# include <math.h>
# include <mlx.h>
# include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                                  Mandatory                                 */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                    Bonus                                   */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                   Shared                                   */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- vec3 ---------------------------------- */

typedef struct s_offset
{
	int				x;
	int				y;
}					t_offset;
typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

t_vec3				vec3_new(float x, float y, float z);
float				vec3_length(t_vec3 vec);
t_vec3				vec3_normalize(t_vec3 vec);
t_vec3				vec3_cross(t_vec3 vec1, t_vec3 vec2);
float				vec3_dot(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_subtract(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_multiply(t_vec3 vec, float scale);
t_vec3				vec3_divide(t_vec3 vec, float scale);

typedef struct s_cam
{
	t_vec3			origin;
	t_vec3			direction;
	float			fov;
}					t_cam;

void				cam_init(t_cam *cam);

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
t_color_c			color_multiply(t_color_c color1, t_color_c color2);
t_color_c			color_scale(t_color_c color, float scale);
t_color_c			color_add(t_color_c color1, t_color_c color2);
t_color_c			color_average(t_color_c color1, t_color_c color2);

typedef struct s_light
{
	t_vec3			origin;
	float			intensity;
	t_color_c		color;
}					t_light;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
	float			intensity;
	t_color_c		color;
}					t_ray;

t_ray				ray_init(t_vec3 origin, t_vec3 direction);
t_ray				ray_primary(t_cam *cam, float x, float y);

# define MAX_UCHAR_2 65025;
# define DIV_MAX_UCHAR_2 0.000015384615384615385;

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

typedef struct s_material
{
	t_color_c		color;
	t_color_c		emission;
	float			emission_i;
}					t_material;

typedef struct s_sphere
{
	t_vec3			center;
	float			radius;
	t_material		material;
}					t_sphere;

t_sphere			sphere_new(t_vec3 center, float radius,
						t_material material);
t_vec3				sphere_normal(t_sphere *sphere, t_vec3 point);
t_vec3				sphere_intersect(t_sphere *sphere, t_ray *ray);

/* ---------------------------------- hooks --------------------------------- */
typedef struct s_key_events
{
	bool			holding_1;
	bool			holding_2;
	bool			holding_3;
	bool			holding_m_left;
	bool			holding_m_middle;
	bool			holding_m_right;
}					t_key_events;

typedef struct s_mouse_events
{
	int				prev_x;
	int				prev_y;
}					t_mouse_events;

typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_cam			cam;
	t_sphere		sphere[4];
	t_key_events	key_events;
	t_mouse_events	mouse_events;
	t_light			light;
}					t_minirt;

typedef struct s_hit_info
{
	t_vec3			point;
	t_vec3			normal;
	t_material		material;
	bool			hit;
}					t_hit_info;

int					key_down_hook(int keycode, t_minirt *minirt);
int					key_up_hook(int keycode, t_minirt *minirt);
int					mouse_down_hook(int button, int x, int y, t_minirt *minirt);
int					mouse_up_hook(int button, int x, int y, t_minirt *minirt);
int					mouse_move_hook(int x, int y, t_minirt *minirt);
int					loop_hook(t_minirt *minirt);
float				random_num(unsigned int *state);
float				normal_dist_random_num(unsigned int *state);
t_vec3				random_vec3_hs(t_vec3 normal, unsigned int *state);

t_vec3				random_vec3_hs(t_vec3 normal, unsigned int *state);

t_hit_info			intersections(t_minirt *minirt, t_ray *ray,
						unsigned int *state);

t_color_c			ray_tracing(t_ray *ray, t_minirt *minirt,
						unsigned int *state);
#endif