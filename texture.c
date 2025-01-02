/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:47:10 by meroshen          #+#    #+#             */
/*   Updated: 2024/12/20 23:47:10 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_data *data, int tex_num, char *file_path)
{
	data->textures[tex_num].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, \
											(char *)file_path, \
											&data->textures[tex_num].width, \
											&data->textures[tex_num].height);
	if (!data->textures[tex_num].mlx_img)
		ft_exit(data, error("Texture loading error", 1));
	data->textures[tex_num].img_pixels_ptr = mlx_get_data_addr(\
										data->textures[tex_num].mlx_img, \
										&data->textures[tex_num].bpp, \
										&data->textures[tex_num].size_line, \
										&data->textures[tex_num].endian);
}

static t_image	*select_texture(t_data *data)
{
	if (data->ray->is_hit_side_y == 0)
	{
		if (data->ray->map_pos.x < data->player->pos.x)
			return (&(data->textures[EAST]));
		else
			return (&(data->textures[WEST]));
	}
	else
	{
		if (data->ray->map_pos.y < data->player->pos.y)
			return (&(data->textures[NORTH]));
		else
			return (&(data->textures[SOUTH]));
	}
}

static double	calc_collis_pnt(t_data *data)
{
	if (data->ray->is_hit_side_y == 0)
		return (data->player->pos.y + data->ray->wall_dist * data->ray->dir.y);
	else
		return (data->player->pos.x + data->ray->wall_dist * data->ray->dir.x);
}

static int	calc_texture_x(t_data *data, t_image *texture)
{
	int	x;

	x = (int)(data->ray->collis_pnt_x * texture->width);
	if ((data->ray->is_hit_side_y == 0 && data->ray->dir.x < 0)
		|| (data->ray->is_hit_side_y == 1 && data->ray->dir.y > 0))
		x = texture->width - x - 1;
	return (x);
}

/*If the collision is along the X, we select the texture for the N(north) or 
	S wall (the wall is horizontally aligned). If the collision is along the Y, 
	we choose between the W and E texture. And then draw(put in img) 
	the column of wall*/
void	draw_col_texture(t_data *data, t_line_data *line)
{
	t_image			*texture;
	t_for_norm		s;

	texture = select_texture(data);
	data->ray->collis_pnt_x = calc_collis_pnt(data) - \
									floor(calc_collis_pnt(data));
	s.x = calc_texture_x(data, texture);
	s.step = (double)texture->height / (double)line->line_height;
	s.pos = (line->line_start - WIN_HEIGHT / 2
			+ line->line_height / 2) * s.step;
	s.y_scr = line->line_start;
	while (s.y_scr < line->line_end)
	{
		s.y = (int) s.pos & (texture->height - 1);
		s.pos += s.step;
		s.vect_txtr = vector_int_create(s.x, s.y);
		s.vect_scr = vector_int_create(line->x, s.y_scr);
		copy_pixel(texture, s.vect_txtr, data, s.vect_scr);
		s.y_scr ++;
	}
}
