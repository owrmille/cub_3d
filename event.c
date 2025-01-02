/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:08:42 by meroshen          #+#    #+#             */
/*   Updated: 2025/01/02 16:35:07 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_left_and_up_wall(t_data *data)
{
	int	res;

	res = 1;
	if ((data->player->pos.y - (int)(data->player->pos.y) < 0.120) &&
		data->map[(int)data->player->pos.y - 1][(int)data->player->pos.x] \
																	== '1')
		res = 0;
	if ((data->player->pos.x - (int)(data->player->pos.x) < 0.120) &&
		data->map[(int)data->player->pos.y][(int)data->player->pos.x - 1] \
																	== '1')
		res = 0;
	return (res);
}

static int	check_pos(t_data *data)
{
	if (data->player->pos.x > 1 && data->player->pos.y > 1
		&& data->player->pos.x < (double)(data->map_size_w -1)
		&& data->player->pos.y < (double)(data->map_size_h -1)
		&& data->map[(int)data->player->pos.y][(int)data->player->pos.x] \
																		!= '1'
		&& check_left_and_up_wall(data))
		return (0);
	else
		return (1);
}

static void	rotation(int key, t_data *data)
{
	if (key == XK_Left)
	{
		data->player->dir = vector_rot(data->player->dir, M_PI / 50.0);
		data->player->plane = vector_rot(data->player->plane, M_PI / 50.0);
	}
	else if (key == XK_Right)
	{
		data->player->dir = vector_rot(data->player->dir, -M_PI / 50.0);
		data->player->plane = vector_rot(data->player->plane, -M_PI / 50.0);
	}
}

int	key_handler(int key, t_data *data)
{
	t_vector	old_pos;

	old_pos = data->player->pos;
	if (key == XK_Escape)
		data->running = 0;
	else if (key == XK_a)
		data->player->pos = vector_add(data->player->pos, \
			vector_koef(vector_rot(data->player->dir, M_PI_2), SPEED_MOV));
	else if (key == XK_d)
		data->player->pos = vector_add(data->player->pos, \
				vector_koef(vector_rot(data->player->dir, -M_PI_2), SPEED_MOV));
	else if (key == XK_w)
		data->player->pos = vector_add(data->player->pos,
				vector_koef(data->player->dir, SPEED_MOV));
	else if (key == XK_s)
		data->player->pos = vector_add(data->player->pos,
				vector_koef(data->player->dir, -SPEED_MOV));
	else if (key == XK_Left || key == XK_Right)
		rotation(key, data);
	if (check_pos(data) == 1)
		data->player->pos = old_pos;
	else
		recreate_img(data);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	prev_pos = WIN_WIDTH / 2;

	(void)y;
	if (x == prev_pos)
		return (0);
	else if (x > prev_pos)
	{
		data->player->dir = vector_rot(data->player->dir, -M_PI / 50.0);
		data->player->plane = vector_rot(data->player->plane, -M_PI / 50.0);
	}
	else if (x < prev_pos)
	{
		data->player->dir = vector_rot(data->player->dir, M_PI / 50.0);
		data->player->plane = vector_rot(data->player->plane, M_PI / 50.0);
	}
	prev_pos = x;
	recreate_img(data);
	return (0);
}
