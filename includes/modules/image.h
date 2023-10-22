/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:32:04 by itan              #+#    #+#             */
/*   Updated: 2023/10/22 14:45:56 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H
/* ---------------------------------- image --------------------------------- */
typedef struct s_image
{
	void	*image;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
}			t_image;

typedef union u_offset
{
	int		xy[2];
	struct
	{
		int	x;
		int	y;
	};
}			t_offset;

void		put_pixel(t_image *image, t_offset offset, unsigned int color);

#endif