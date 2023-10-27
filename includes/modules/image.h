/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:32:04 by itan              #+#    #+#             */
/*   Updated: 2023/10/27 18:41:20 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H
# include "color.h"
# include "vec3.h"
/* ---------------------------------- image --------------------------------- */

/**
 * @brief A union to store the x and y offset of a pixel or size of image.
 *
 * @param xy An array of 2 integers.
 * @param x The x offset or size of image.
 * @param y The y offset or size of image.
 */
typedef union u_offset
{
	int			xy[2];
	struct
	{
		int		x;
		int		y;
	};
}				t_offset;

/**
 * @brief A struct to store the image data.
 *
 * @param image The image pointer returned by mlx_new_image().
 * @param buffer The image buffer returned by mlx_get_data_addr().
 * @param pixel_bits The number of bits per pixel.
 * @param line_bytes The number of bytes per line.
 * @param endian The endian of the image.
 * @param size The size of the image.
 */
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