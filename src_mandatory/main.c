/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:21:09 by itan              #+#    #+#             */
/*   Updated: 2023/08/25 23:51:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	gradient(t_image *image)
{
	int		x;
	int		y;
	t_color	*color;
	double	opacity;
	double	opacity2;

	color = malloc(sizeof(t_color));
	y = 0;
	*color = color_new(0, 0xdd, 0xee, 0xff);
	while (y < 1080)
	{
		x = 0;
		opacity2 = (double)y / 1080;
		while (x < 1920)
		{
			opacity = (double)x / 1920;
			*color = color_new(ft_sqrt(((double)1 - opacity) * 0xff * 0xff),
				0xff, ft_sqrt(((double)1 - opacity2) * 0xff * 0xff), 0xff);
			put_pixel(image, x, y, *(unsigned int *)color);
			x++;
		}
		y++;
	}
}

int	main(int ac, char const **av)
{
	void		*mlx;
	void		*win;
	t_cam		cam;
	t_sphere	sphere;
	t_image		image;

	(void)ac;
	(void)av;
	cam.origin = vec3_new(0, 0, 0);
	cam.direction = vec3_new(0, 0, 1);
	cam.fov = 90;
	sphere.center = vec3_new(0, 0, 5);
	sphere.radius = 1;
	sphere.color = color_new(0xff, 0, 0, 0xff);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	image.img = mlx_new_image(mlx, 1920, 1080);
	image.buffer = mlx_get_data_addr(image.img, &image.pixel_bits,
		&image.line_bytes, &image.endian);
	gradient(&image);
	mlx_put_image_to_window(mlx, win, image.img, 0, 0);
	mlx_destroy_image(mlx, image.img);
	mlx_loop(mlx);
	return (0);
}
