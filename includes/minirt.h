/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:27:57 by itan              #+#    #+#             */
/*   Updated: 2023/09/06 16:16:10 by itan             ###   ########.fr       */
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
# include "share.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                                  Mandatory                                 */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                    Bonus                                   */
/* -------------------------------------------------------------------------- */

typedef struct s_offset
{
	int				x;
	int				y;
}					t_offset;

typedef struct s_light
{
	t_vec3			origin;
	float			intensity;
	t_color_c		color;
}					t_light;

# define MAX_UCHAR_2 65025;
# define DIV_MAX_UCHAR_2 0.000015384615384615385;

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

	t_amb_light		amb_light;
	t_cam			cam;
	t_light_src		light_source;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_list			*objects;
	t_key_events	key_events;
	t_mouse_events	mouse_events;
}					t_minirt;

typedef struct s_hit_info
{
	t_vec3			point;
	t_vec3			normal;
	t_material		material;
	bool			hit;
}					t_hit_info;

void				draw_scene(t_minirt *minirt);

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