/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:17:57 by meroshen          #+#    #+#             */
/*   Updated: 2024/11/24 04:46:14 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_player(t_data *data)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (1);
	data->player = player;
	return (0);
}

void	init_mlx(t_data *data)
{
	int	i;

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_exit(data, error("mlx", 1));
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, \
																"Cub3D");
	if (!data->mlx_win)
		ft_exit(data, error("mlx", 1));
	data->img = (t_image *)malloc(sizeof(t_image));
	if (!data->img)
		ft_exit(data, error("mlx", 1));
	data->img->mlx_img = NULL;
	data->textures = (t_image *)malloc(4 * sizeof(t_image));
	if (!data->textures)
		ft_exit(data, error("mlx", 1));
	i = 0;
	while (i < 4)
	{
		(data->textures[i]).mlx_img = NULL;
		i++;
	}
	recreate_img(data);
	return ;
}

void	init_ray(t_data *data)
{
	if (data->ray)
	{
		free(data->ray);
		data->ray = NULL;
	}
	data->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!data->ray)
		ft_exit(data, 1);
	data->ray->dir = vector_create(0.0, 0.0);
	data->ray->map_pos = vector_int_create(0, 0);
	data->ray->delta_dist = vector_create(0.0, 0.0);
	data->ray->wall_dist = 0.0;
	data->ray->side_dist = vector_create(0.0, 0.0);
	data->ray->step = vector_int_create(0, 0);
	data->ray->is_hit_side_y = 0;
}

void	init_data(t_data *data, int fd)
{
	data->running = 1;
	data->fd = fd;
	data->mlx_ptr = NULL;
	data->mlx_win = NULL;
	data->img = NULL;
	data->map = NULL;
	data->player = NULL;
	data->ray = NULL;
	data->color_f.r = -1;
	data->color_f.g = -1;
	data->color_f.b = -1;
	data->color_c.r = -1;
	data->color_c.g = -1;
	data->color_c.b = -1;
	init_player(data);
	init_ray(data);
}
