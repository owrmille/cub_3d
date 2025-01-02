/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:10:39 by meroshen          #+#    #+#             */
/*   Updated: 2024/12/21 22:50:17 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	recreate_img(t_data *data)
{
	if (data->img->mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img->mlx_img)
		ft_exit(data, error("img", 1));
	data->img->img_pixels_ptr = mlx_get_data_addr(data->img->mlx_img, \
		&(data->img->bpp), &(data->img->size_line), &(data->img->endian));
}

void	put_pixel(t_data *data, int x, int y, t_color color)
{
	char	*pixel_ptr;

	if ((x > 0 && x < WIN_WIDTH) && (y > 0 && y < WIN_HEIGHT))
	{
		pixel_ptr = data->img->img_pixels_ptr + (y * data->img->size_line) + \
			(x * (data->img->bpp / 8));
		if (data->img->bpp == 32)
			*(unsigned int *)pixel_ptr = (color.r << 16) \
										| (color.g << 8) \
										| color.b;
	}
}

/*Copy color of point from texture to point on screen*/
void	copy_pixel(t_image *texture, t_int_vector txtr_point, \
							t_data *data, t_int_vector scr_point)
{
	char	*textr_pixel_ptr;
	char	*scr_pixel_ptr;
	int		i;

	if (txtr_point.x < 0 || txtr_point.x >= texture->width \
		|| txtr_point.y < 0 || txtr_point.y >= texture->height \
		|| scr_point.x < 0 || scr_point.x >= WIN_WIDTH \
		|| scr_point.y < 0 || scr_point.y >= WIN_HEIGHT)
		return ;
	textr_pixel_ptr = texture->img_pixels_ptr + \
		(txtr_point.y * texture->size_line + txtr_point.x * (texture->bpp / 8));
	scr_pixel_ptr = data->img->img_pixels_ptr + \
		(scr_point.y * data->img->size_line + \
											scr_point.x * (data->img->bpp / 8));
	i = 0;
	while (i < (texture->bpp / 8))
	{
		scr_pixel_ptr[i] = textr_pixel_ptr[i];
		i++;
	}
}
