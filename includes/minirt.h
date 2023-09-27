/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:22:20 by itan              #+#    #+#             */
/*   Updated: 2023/09/27 21:21:20 by itan             ###   ########.fr       */
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
# include <fcntl.h>
# include <math.h>
# include "./minilibx_opengl/mlx.h"
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

/* ---------------------------------- image --------------------------------- */
typedef struct s_image
{
	void			*image;
	int				pixel_bits;
	int				line_bytes;
	int				endian;
	char			*buffer;
}					t_image;

typedef union u_offset
{
	int				xy[2];
	struct
	{
		int			x;
		int			y;
	};
}					t_offset;

void				put_pixel(t_image *image, t_offset offset,
						unsigned int color);

/* ---------------------------------- vec3 ---------------------------------- */
typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

t_vec3				reflection(t_vec3 d_ray, t_vec3 normal);
t_vec3				vec3_apply_rot(t_vec3 vec, t_quaternion rot);
t_vec3				vec3_new(float x, float y, float z);
float				vec3_length(t_vec3 vec);
t_vec3				vec3_normalize(t_vec3 vec);
t_vec3				vec3_cross(t_vec3 vec1, t_vec3 vec2);
float				vec3_dot(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_tween(t_vec3 vec1, t_vec3 vec2, float t);
t_vec3				vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_subtract(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_multiply(t_vec3 vec, float scale);
t_vec3				vec3_divide(t_vec3 vec, float scale);

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

/* -------------------------------- material -------------------------------- */

typedef struct s_material
{
	t_color_c		color;
	t_color_c		emission;
	t_color_c		specular;
	float			diffuse_i;
	float			specular_i;
	float			reflective_i;
	float			shininess;
	float			emission_i;
}					t_material;

/* ----------------------------------- cam ---------------------------------- */

/**
 * @brief Camera struct
 *
 * @param origin camera position
 * @param direction camera direction or forward direction
 * @param up up direction
 * @param right right direction
 * @param fov field of view
 * @param vp_width viewport width
 * @param vp_height viewport height
 */
typedef struct s_cam
{
	t_vec3			origin;
	t_vec3			direction;
	t_vec3			up;
	t_vec3			right;
	t_vec3			position;
	t_quaternion	rotation;
	float			fov;
	int				vp_width;
	int				vp_height;
}					t_cam;

void				cam_init(t_cam *cam);

/* ----------------------------------- ray ---------------------------------- */

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
	t_vec3			inverse_direction;
	float			intensity;
	t_color_c		color;
}					t_ray;

t_ray				ray_init(t_vec3 origin, t_vec3 direction);
t_ray				ray_primary(t_cam *cam, t_offset offset);

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

typedef struct s_sphere
{
	t_vec3			center;
	float			radius;
	t_color_c		color;
	t_material		material;
}					t_sphere;

t_sphere			sphere_new(t_vec3 center, float radius,
						t_material material);
t_vec3				sphere_normal(t_sphere *sphere, t_vec3 point);
t_vec3				sphere_intersect(t_sphere *sphere, t_ray *ray);

typedef struct s_plane
{
	t_vec3			point_on_plane;
	t_vec3			normalized_norm_vec;
	t_material		material;
}					t_plane;

t_plane				plane_new(t_vec3 point, t_vec3 dir, t_material material);
t_vec3				disk_intersect(t_plane *plane, t_ray *ray, float radius,
						t_vec3 p0);
t_vec3				plane_intersect(t_plane *plane, t_ray *ray);

typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			normalized_axis;
	float			radius;
	float			height;
	t_material		material;
}					t_cylinder;

t_vec3				cylinder_intersect(t_cylinder *cylinder, t_ray *ray);
t_vec3				cylinder_normal(t_cylinder *cylinder, t_vec3 point,
						float type);

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

typedef struct s_bound_box
{
	t_vec3			min;
	t_vec3			max;
}					t_bound_box;

# define OCTREE_MAX_DEPTH 10
# define OCTREE_MAX_OBJECTS 10
# define OCTREE_MAX_NODE 8

typedef struct s_object
{
	void			*object;
	unsigned char	type;
	t_bound_box		bounding_box;
}					t_object;

typedef struct s_octree
{
	t_bound_box		bounding_box;
	t_list			*objects;
	struct s_octree	**children;
}					t_octree;

t_bound_box			bound_box_new(t_vec3 min, t_vec3 max);
t_bound_box			bound_box_expend(t_bound_box box, t_vec3 point);
bool				bound_box_intersect(t_bound_box box, t_ray ray);

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
	bool			holding_q;
	bool			holding_e;

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
	t_image			image;

	t_amb_light		amb_light;
	t_cam			cam;
	t_list			*pt_lights;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_list			*objects;
	t_key_events	key_events;
	t_mouse_events	mouse_events;
	t_selections	selection;
	pthread_t		*threads;
	int 			pixel_size;
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
	SPHERE,
	PLANE,
	CYLINDER,
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

int					render(t_minirt *minirt);
void				ray_cast(t_minirt *minirt);
void				draw_scene(t_minirt *minirt);
void				thread_init(t_minirt *minirt);
t_color_c			get_color(t_minirt *rt, t_hit_info *hi);

#endif
