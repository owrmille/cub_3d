/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:22:14 by meroshen          #+#    #+#             */
/*   Updated: 2025/01/02 17:26:36 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(int x, t_data *data)
{
	t_line_data	line;

	line.x = x;
	line.line_height = (int)(WIN_HEIGHT / data->ray->wall_dist);
	line.line_start = -line.line_height / 2 + WIN_HEIGHT / 2;
	if (line.line_start < 0)
		line.line_start = 0;
	line.line_end = line.line_height / 2 + WIN_HEIGHT / 2;
	if (line.line_end >= WIN_HEIGHT)
		line.line_end = WIN_HEIGHT - 1;
	draw_col_texture(data, &line);
}

void	draw_background(int x, t_data *data)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		put_pixel(data, x, y, data->color_c);
		y++;
	}
	while (y >= WIN_HEIGHT / 2 && y < WIN_HEIGHT)
	{
		put_pixel(data, x, y, data->color_f);
		y++;
	}
}

void	raycasting(t_data *data)
{
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		draw_background(x, data);
		init_raycast_data(x, data);
		raycast_exec(data);
		draw_wall(x, data);
		x++;
	}
}

int	rendering(t_data *data)
{
	if (data->running == 0)
		ft_exit(data, 0);
	raycasting(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, \
								data->img->mlx_img, 0, 0);
	return (0);
}
