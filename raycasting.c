/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:52:45 by meroshen          #+#    #+#             */
/*   Updated: 2024/12/20 23:09:48 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	find_ray_step_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - player->pos.x) * \
							ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->map_pos.y) * \
							ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - player->pos.y) * \
							ray->delta_dist.y;
	}
}

/*Initialization:
	koef for normalize x to [-1, 1]
	dir - direction vector of the ray
	map_pos - position of the ray on the map grid (square)
	delta_dist - distance to the next nearist x or y.
	wall_dist - distance to the wall*/
void	init_raycast_data(int x, t_data *data)
{
	double	koef;
	t_ray	*ray;

	init_ray(data);
	koef = 2.0 * x / (double) WIN_WIDTH - 1.0;
	ray = data->ray;
	ray->dir = vector_add(data->player->dir, \
							vector_koef(data->player->plane, koef));
	ray->map_pos = vector_int_create((int)(data->player->pos.x), \
									(int)(data->player->pos.y));
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	find_ray_step_side_dist(ray, data->player);
}

static void	find_wall_dist(t_data *data)
{
	if (data->ray->is_hit_side_y == 0)
		data->ray->wall_dist = (data->ray->map_pos.x - data->player->pos.x + \
						(1 - data->ray->step.x) / 2) / data->ray->dir.x;
	else
		data->ray->wall_dist = (data->ray->map_pos.y - data->player->pos.y + \
						(1 - data->ray->step.y) / 2) / data->ray->dir.y;
	if (fabs(data->ray->wall_dist) == 0)
		data->ray->wall_dist = fmax(data->ray->wall_dist, 0.0003);
}

static void	ray_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_pos.x += ray->step.x;
		ray->is_hit_side_y = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_pos.y += ray->step.y;
		ray->is_hit_side_y = 1;
	}
}

/* Raycasting execution. While there is no collision with any wall, 
	we move along X or Y depending on which side_dist is smaller*/
void	raycast_exec(t_data *data)
{
	int	is_hit;

	is_hit = 0;
	while (is_hit == 0)
	{
		ray_step(data->ray);
		if (data->ray->map_pos.y < 0.15
			|| data->ray->map_pos.y > data->map_size_h - 0.15
			|| data->ray->map_pos.x < 0.15
			|| data->ray->map_pos.x > data->map_size_w - 0.15)
			break ;
		if (data->map[data->ray->map_pos.y][data->ray->map_pos.x] == '1')
			is_hit = 1;
	}
	find_wall_dist(data);
}
