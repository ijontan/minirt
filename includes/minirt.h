/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:22:20 by itan              #+#    #+#             */
/*   Updated: 2023/11/08 14:46:49 by rsoo             ###   ########.fr       */
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

// window size
# define WINDOW_WIDTH 1580
# define WINDOW_HEIGHT 720
# define MID_X 790
# define MID_Y 360

// padding for the menu strings 
# define MENU_START_X 20
# define SCENES_START_X 40
# define SCENES_START_Y 360
# define OBJ_MENU_START_X 1340
# define MATERIAL_SECTION_START_Y 450

// misc.
# define MENU_WIDTH 250
# define CHAR_WIDTH 7
# define CHAR_HEIGHT 25

// loading overlay
# define OVERLAY_WIDTH 400
# define OVERLAY_HEIGHT 40
# define OVERLAY_START_Y 340
# define OVERLAY_END_Y 380
// camera position overlay
# define CAM_POS_OVERLAY_START_Y 640
# define CAM_POS_OVERLAY_END_Y 680

// paths
# define RT_FILE_DIR "rt_files/scenes/"

// colors
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define YELLOW 0xFFFF00
# define ORANGE 0xFF6900
# define RED 0xFF0000
# define PINK 0xFF00FF
# define PURPLE 0x7800FF

// useful numbers
// - number of objects + env objects
# define PARSE_NUM 7

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
	char			*obj_type[PARSE_NUM];
	void			(*func_ptr[PARSE_NUM])(struct s_parse *);
	int				obj_code[PARSE_NUM];
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
void				parse_cone(t_parse *p);

// parse_environment.c
void				parse_ambient_lighting(t_parse *p);
void				parse_camera(t_parse *p);
void				parse_lighting(t_parse *p);

// parse_attr.c
bool				check_rgb(char *s, t_parse *p);
bool				check_norm_vec_range(char *s, t_parse *p);
t_vec3				assign_norm_vec(t_parse *p);
t_vec3				parse_coordinates(char *s, t_parse *p);

// error_handling.c
void				exit_parse(char **info, char *s, char c);
void				check_line_format(int type, t_parse *p);

// error_handling2.c
bool				valid_float(char *s);
bool				valid_triplet(char *s);

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
	bool			holding_4;
	bool			holding_5;
	bool			holding_6;
	bool			holding_7;
	bool			holding_8;
	bool			holding_9;
	bool			holding_0;
	bool			holding_up;
	bool			holding_down;
	bool			holding_left;
	bool			holding_right;
	bool			holding_q;
	bool			holding_e;
	bool			holding_w;
	bool			holding_a;
	bool			holding_s;
	bool			holding_d;
	bool			holding_z;
	bool			holding_x;
	bool			holding_c;
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

typedef enum e_material_f
{
	NOT_SELECTED,
	MATERIAL_COLOR,
	EMISSION_COLOR,
	SPECULAR_COLOR,
	DIFFUSE_INTENSITY,
	SPECULAR_INTENSITY,
	REFLECTIVE_INTENSITY,
	EMISSION_INTENSITY,
	SHININESS
}					t_material_f;

typedef struct s_selections
{
	t_object		*selected;
	t_plane			*translation_plane;
	t_plane			*rotation_plane;
	t_vec3			rotation_start;
	float			angle;
	t_color_c		plane_color;
	t_color_c		outline_color;
	t_quaternion	rotation;
	t_material_f	selected_material_field;
}					t_selections;

typedef struct s_vec2
{
	int				x;
	int				y;
}					t_vec2;

typedef struct s_file
{
	char			*name;
	t_vec2			top_left;
	t_vec2			bottom_right;
}					t_file;

typedef struct s_overlay
{
	int				obj_type;
	char			*msg;
	int				len;
	int				midpoint;
	int				start_x;
	int				end_x;
}					t_overlay;

typedef enum e_render_status
{
	RENDER_FIRST_SCENE,
	RENDER_NEW_SCENE,
	RENDER_CURRENT_SCENE,
	RENDERING,
	RENDER_DONE,
	RENDER_START_ANIMATION,
	RENDER_END_ANIMATION,
	FLOATING_MODE,
	NON_FLOATING_MODE,
	RESET_CAM_ANIMATION,
	RESET_CAM_DONE,
}					t_render_status;

typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	t_image			image;

	t_amb_light		amb_light;
	t_cam			cam;
	t_list			*pt_lights;
	t_list			*objects;
	t_key_events	key_events;
	t_mouse_events	mouse_events;
	t_selections	selection;
	pthread_t		*threads;
	int				pixel_size;
	bool			moving;

	t_file			*rt_files;
	int				file_num;

	int				render_status;
	int				file_ind;
	char			*rt_file_path;

	char			*msg;
	t_overlay		cam_pos_overlay;
	t_overlay		loading_overlay;
	t_overlay		selected_obj_overlay;

	int				font_color;
	t_material		selected_obj_material;
}					t_minirt;

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
	CONE = 3,
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
	bool			hit_selection_plane;
	bool			hit_rotation_plane;
}					t_hit_info;

void				draw_scene(t_minirt *minirt);
void				start_minirt(t_minirt *minirt);

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
float				float_clamp(float value, float min, float max);

t_hit_info			intersections(t_minirt *minirt, t_ray *ray);
t_hit_info			intersect_list(t_minirt *minirt, t_ray *ray);

t_color_c			get_color(t_minirt *rt, t_hit_info *hi);
t_color_c			ray_tracing(t_ray ray, t_minirt *minirt,
						unsigned int *state);

// rendering
int					render(t_minirt *minirt,
						void (*draw_func)(t_minirt *minirt));
void				render_gi(t_minirt *rt);

// render menu
void				render_menu(t_minirt *minirt, int start_x, int end_x, int end_y);
void 				put_menu_str(t_minirt *minirt);
void				put_obj_menu_str(t_minirt *minirt);
char				*create_vec3_str(char *title, t_vec3 coords);
char				*create_vec3_str_brac(char *title, t_vec3 coords);
char				*create_color_str_brac(char *title, t_color_c color);

// render overlay
void				render_loading_overlay(t_minirt *minirt);
void				render_cam_pos_overlay(t_minirt *minirt);
void 				put_overlay_str(t_minirt *minirt, int start_x, int start_y, char *str);

void				put_handle_material_str(t_minirt *minirt);

void				put_sphere_info(t_minirt *minirt);
void				put_plane_info(t_minirt *minirt);
void				put_cylinder_info(t_minirt *minirt);
void				put_cone_info(t_minirt *minirt);

void				ray_cast(t_minirt *minirt);
void				draw_scene(t_minirt *minirt);
void				thread_init(t_minirt *minirt);
void				thread_raytrace(t_minirt *minirt);
t_color_c			get_color(t_minirt *rt, t_hit_info *hi);
t_color_c			get_lights_color(t_minirt *rt, t_hit_info *hi);
t_image				create_image(t_minirt *rt, t_offset size);
t_image				load_image(t_minirt *rt, char *path);

char				*ft_ftoa(double num, int precision);
/* ---------------------------------- hooks --------------------------------- */
void				update_selected_material(t_minirt *minirt);
void				key_holding_down(int keycode, t_minirt *minirt);
void				key_holding_up(int keycode, t_minirt *minirt);
void				add_translation_plane(t_minirt *rt);
void				remove_translation_plane(t_minirt *rt);
void				translate_objects(int x, int y, t_minirt *minirt);
void				init_rotation(t_offset xy, t_minirt *minirt);
void				stop_rotation(t_minirt *minirt);
void				calc_rotation(t_offset xy, t_minirt *minirt);
void				rotate_cam(int x, int y, t_minirt *minirt);
void				reset_cam_animation(t_minirt *minirt);

/* ------------------------------- mouse_util ------------------------------- */

void				mouse_hide(t_minirt *minirt);
void				mouse_show(t_minirt *minirt);
void				mouse_move(t_minirt *minirt, int x, int y);

/* ------------------------------ freeing_utils ----------------------------- */

void				free_minirt(t_minirt *minirt);

#endif
