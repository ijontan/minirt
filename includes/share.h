/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:22:20 by itan              #+#    #+#             */
/*   Updated: 2023/09/06 15:20:55 by itan             ###   ########.fr       */
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

typedef struct s_material
{
	t_color_c		color;
	t_color_c		emission;
	float			emission_i;
}					t_material;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
	float			intensity;
	t_color_c		color;
}					t_ray;

typedef struct s_amb_light
{
	float			ratio;
	t_material		material;
}					t_amb_light;

typedef struct s_cam
{
	t_vec3			origin;
	t_vec3			direction;
	float			fov;
}					t_cam;

void				cam_init(t_cam *cam);

typedef struct s_light_src
{
	t_vec3			position;
	float			ratio;
	t_material material; // bonus
}					t_light_src;

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
	int				mand_flag[6];
	char			*obj_type[6];
	void			(*func_ptr[6])(struct s_parse *);
	char			**info;
	int				rgb[3];
	float			coords[3];
	t_atof			atof;
	t_amb_light		amb_light;
	t_cam			camera;
	t_light_src		light_source;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
}					t_parse;

// parsing.c
bool				parse_rt_file(char *infile, t_parse *parse_info);

// parsing_utils.c
void				free_2darray(char **s);
float				ft_atof(char *s, t_parse *p);

// parse_objects.c
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
void				check_line_format(char *s, t_parse *p);

// error_handling2.c
bool				valid_float(char *s);
bool				valid_triplet(char *s);

/* --------------------------------- octree --------------------------------- */

typedef struct s_bounding_box
{
	t_vec3			min;
	t_vec3			max;
}					t_bounding_box;

# define OCTREE_MAX_DEPTH 10
# define OCTREE_MAX_OBJECTS 10
# define OCTREE_MAX_NODE 8

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2

typedef struct s_object
{
	void			*object;
	unsigned char	type;
}					t_object;

typedef struct s_octree
{
	t_bounding_box	bounding_box;
	t_list			*objects;
	struct s_octree	**children;
}					t_octree;

#endif
