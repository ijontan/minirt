/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:22:20 by itan              #+#    #+#             */
/*   Updated: 2023/10/25 15:30:31 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# if defined(__APPLE__)
#  include "./minilibx_opengl/mlx.h"
#  include <key_macos.h>
# else
#  include <key_linux.h>
#  include <mlx.h>
# endif

# include "libft.h"
# include "share.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>

// positions
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MID_X 960
# define MID_Y 540

// colors
# define WHITE 0xFFFFFF
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define YELLOW 0xFFFF00
# define ORANGE 0xFF6900
# define RED 0xFF0000
# define PINK 0xFF00FF
# define PURPLE 0x7800FF

/* -------------------------------------------------------------------------- */
/*                                  Mandatory                                 */
/* -------------------------------------------------------------------------- */

typedef struct s_amb_light
{
	float			ratio;
	t_color_c		color;
}					t_amb_light;

typedef struct s_pt_light
{
	t_vec3			position;
	float			ratio;
	t_material material; // bonus
}					t_pt_light;

/* ---------------------------------- shape --------------------------------- */

/* ---------------------------------- parse --------------------------------- */

typedef struct s_atof
{
	float			result;
	float			power;
	int				sign;
	int				i;
}					t_atof;

// Parsing
typedef struct s_parse
{
	int				infile_fd;
	char			*obj_type[6];
	void			(*func_ptr[6])(struct s_parse *);
	int				obj_code[6];
	char			**info;
	int				rgb[3];
	float			coords[3];
	t_atof			atof;
	t_amb_light		amb_light;
	t_cam			camera;
	t_list			*pt_lights;
	t_list			*objects;
}					t_parse;

// parsing.c
bool				parse_rt_file(char *infile, t_parse *parse_info);

// parsing_utils.c
void				free_2darray(char **s);
float				ft_atof(char *s, t_parse *p);

// parse_objects.c
void				add_object(t_list **objects, void *object,
						unsigned char type);
void				parse_sphere(t_parse *p);
void				parse_plane(t_parse *p);
void				parse_cylinder(t_parse *p);

// parse_environment.c
void				parse_ambient_lighting(t_parse *p);
void				parse_camera(t_parse *p);
void				parse_lighting(t_parse *p);

// parse_attr.c
bool				check_rgb(char *s, t_parse *p);
bool				check_normalized(char *s, t_parse *p);
t_vec3				assign_norm_vec(t_parse *p);
t_vec3				parse_coordinates(char *s, t_parse *p);

// error_handling.c
void				exit_parse(char **info, char *s, char c);
void				check_line_format(int type, t_parse *p);

// error_handling2.c
bool				valid_float(char *s);
bool				valid_triplet(char *s);

/* --------------------------------- octree --------------------------------- */

# define OCTREE_MAX_DEPTH 10
# define OCTREE_MAX_OBJECTS 10
# define OCTREE_MAX_NODE 8

typedef struct s_octree
{
	t_bound_box		bounding_box;
	t_list			*objects;
	struct s_octree	**children;
}					t_octree;

/* -------------------------------------------------------------------------- */
/*                                    Bonus                                   */
/* -------------------------------------------------------------------------- */

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
	bool			holding_w;
	bool			holding_a;
	bool			holding_s;
	bool			holding_d;
	bool			holding_lsh;
	bool			holding_sp;

}					t_key_events;

typedef struct s_mouse_events
{
	bool			holding_m_left;
	bool			holding_m_middle;
	bool			holding_m_right;
	int				prev_x;
	int				prev_y;
}					t_mouse_events;

typedef struct s_selections
{
	t_object		*selected;
}					t_selections;

typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	void			*win2;
	t_image			image;
	t_image			image2;

	t_amb_light		amb_light;
	t_cam			cam;
	t_list			*pt_lights;
	t_list			*objects;
	t_key_events	key_events;
	t_mouse_events	mouse_events;
	t_selections	selection;
	t_color_c		outline_color;
	pthread_t		*threads;
	int				pixel_size;
	bool			moving;
}					t_minirt;

/*
sphere: obj_type = 1
plane: obj_type = 2
cylinder: obj_type = 3
*/

/**
 * @brief type of object
 *
 * @param SPHERE: 0
 * @param PLANE: 1
 * @param CYLINDER: 2
 * @param AMB_LIGHT: 3
 * @param CAM: 4
 * @param LIGHT: 5
 */
typedef enum e_obj_type
{
	SPHERE = 0,
	PLANE = 1,
	CYLINDER = 2,
	AMB_LIGHT,
	CAM,
	LIGHT
}					t_obj_type;

typedef struct s_hit_info
{
	t_vec3			intersect_pt;
	t_vec3			normal;
	t_vec3			d_diffuse;
	t_vec3			d_specular;
	t_vec3			pt_to_l;
	t_vec3			pt_to_cam;
	t_material		material;
	t_object		*object;
	t_obj_type		obj_type;
	bool			hit;
}					t_hit_info;

void				draw_scene(t_minirt *minirt);

void				init_hooks(t_minirt *minirt);
int					x_button_exit(int keycode, t_minirt *minirt);
int					key_down_hook(int keycode, t_minirt *minirt);
int					key_up_hook(int keycode, t_minirt *minirt);
int					mouse_down_hook(int button, int x, int y, t_minirt *minirt);
int					mouse_up_hook(int button, int x, int y, t_minirt *minirt);
int					mouse_move_hook(int x, int y, t_minirt *minirt);
int					loop_hook(t_minirt *minirt);
float				random_num(unsigned int *state);
float				normal_dist_random_num(unsigned int *state);
t_vec3				random_vec3(unsigned int *state);
t_vec3				random_vec3_hs(t_vec3 normal, unsigned int *state);

t_hit_info			intersections(t_minirt *minirt, t_ray *ray);
t_hit_info			intersect_list(t_minirt *minirt, t_ray *ray);

t_color_c			get_color(t_minirt *rt, t_hit_info *hi);
t_color_c			ray_tracing(t_ray ray, t_minirt *minirt,
						unsigned int *state);

int					render(t_minirt *minirt,
						void (*draw_func)(t_minirt *minirt));
void				render_gi(t_minirt *rt);
void				ray_cast(t_minirt *minirt);
void				draw_scene(t_minirt *minirt);
void				thread_init(t_minirt *minirt);
void				thread_raytrace(t_minirt *minirt);
t_color_c			get_color(t_minirt *rt, t_hit_info *hi);
t_color_c			get_lights_color(t_minirt *rt, t_hit_info *hi);
t_image				create_image(t_minirt *rt);

/* ------------------------------- mouse_util ------------------------------- */

void				mouse_hide(t_minirt *minirt);
void				mouse_show(t_minirt *minirt);
void				mouse_move(t_minirt *minirt, int x, int y);

#endif
