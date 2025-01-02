/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:31:05 by meroshen          #+#    #+#             */
/*   Updated: 2024/12/21 23:31:05 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map, int map_size_h)
{
	int	i;

	if (map)
	{
		i = 0;
		while (i < map_size_h)
		{
			if (map[i])
				free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_data(t_data *data)
{
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	free_map(data->map, data->map_size_h);
	if (data->fd > 2)
		close (data->fd);
}

void	ft_free_mlx(t_data *data)
{
	if (!data->mlx_ptr)
		return ;
	if (data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	mlx_destroy_display(data->mlx_ptr);
	mlx_loop_end(data->mlx_ptr);
	free(data->mlx_ptr);
	data->mlx_ptr = NULL;
}

void	ft_free_textures(t_data *data)
{
	int	i;

	if (!data->textures)
		return ;
	i = 0;
	while (i < 4)
	{
		if ((data->textures[i]).mlx_img)
			mlx_destroy_image(data->mlx_ptr, (data->textures[i]).mlx_img);
		i++;
	}
	free(data->textures);
	data->textures = NULL;
}

int	ft_exit(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->img)
	{
		if (data->img->mlx_img)
			mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
		free(data->img);
		data->img = NULL;
	}
	ft_free_textures(data);
	ft_free_mlx(data);
	free_data(data);
	exit(code);
}
