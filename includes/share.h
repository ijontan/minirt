/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:22:20 by itan              #+#    #+#             */
/*   Updated: 2023/09/11 15:10:41 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARE_H
# define SHARE_H

# include <fcntl.h>

/* ---------------------------------- vec3 ---------------------------------- */
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

typedef struct s_cam
{
	t_vec3			origin;
	t_vec3			direction;
	float			fov;
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
t_ray				ray_primary(t_cam *cam, float x, float y);

typedef struct s_amb_light
{
	float			ratio;
	t_color_c		color;
}					t_amb_light;

typedef struct s_light_src
{
	t_vec3			position;
	float			ratio;
	t_material material; // bonus
}					t_light_src;

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
	float			t;
}					t_plane;

t_plane				plane_new(t_vec3 point, t_vec3 dir, t_material material);
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
t_vec3				cylinder_normal(t_cylinder *cylinder, t_vec3 point);

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
	t_light_src		light_source;
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

/* ---------------------------------- image --------------------------------- */
typedef struct s_image
{
	void			*img;
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

#endif
