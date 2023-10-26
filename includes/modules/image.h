/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:32:04 by itan              #+#    #+#             */
/*   Updated: 2023/10/27 04:27:32 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H
# include "color.h"
# include "vec3.h"
/* ---------------------------------- image --------------------------------- */
typedef union u_offset
{
	int			xy[2];
	struct
	{
		int		x;
		int		y;
	};
}				t_offset;

typedef struct s_image
{
	void		*image;
	char		*buffer;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	t_offset	size;
}				t_image;

void			put_pixel(t_image *image, t_offset offset, unsigned int color);
unsigned int	get_pixel(t_image *image, t_offset offset);
t_color_c		get_pixel_color(t_image *image, t_offset offset);
t_vec3			get_pixel_vec3(t_image *image, t_offset offset);
unsigned int	convert_endian(unsigned int color);
#endif