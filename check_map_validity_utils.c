/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:02:48 by iatopchu          #+#    #+#             */
/*   Updated: 2024/12/21 02:02:49 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_direction(char map_char)
{
	if (map_char == 'N' || map_char == 'S'
		|| map_char == 'E' || map_char == 'W')
		return (1);
	return (0);
}

void	init_player_view(t_player *player, char direct, t_vector pos)
{
	if (direct == 'N')
	{
		player->pos = vector_create(pos.x, pos.y);
		player->dir = vector_create(0.0, -1.0);
		player->plane = vector_create(0.66, 0);
	}
	else if (direct == 'S')
	{
		player->pos = vector_create(pos.x, pos.y);
		player->dir = vector_create(0.0, 1.0);
		player->plane = vector_create(-0.66, 0);
	}
	else if (direct == 'E')
	{
		player->pos = vector_create(pos.x, pos.y);
		player->dir = vector_create(-1.0, 0.0);
		player->plane = vector_create(0.0, -0.66);
	}
	else
	{
		player->pos = vector_create(pos.x, pos.y);
		player->dir = vector_create(1.0, 0.0);
		player->plane = vector_create(0.0, 0.66);
	}
}

int	check_char_and_add_player(t_data *data, int x, int y, int *player_pos_flg)
{
	char		current_char;
	t_vector	pos;

	current_char = data->map[y][x];
	if (is_valid_direction(current_char))
	{
		*player_pos_flg += 1;
		if (*player_pos_flg == 1)
		{
			pos = vector_create((double)x + 0.5, (double)y + 0.5);
			init_player_view(data->player, current_char, pos);
		}
	}
	else if (current_char != ' ' && current_char != '0' && current_char != '1')
		return (1);
	return (0);
}

int	check_chars_validity(t_data *data)
{
	int		i;
	int		j;
	int		player_pos_flg;

	i = -1;
	j = -1;
	player_pos_flg = 0;
	while (data->map[++i])
	{
		while (++j < ft_strlen(data->map[i]) - 1)
		{
			if (check_char_and_add_player(data, j, i, &player_pos_flg) == 1)
			{
				error("Wrong characters in the map.", 1);
				return (1);
			}
		}
		j = 0;
	}
	if (player_pos_flg != 1)
	{
		error("Map should have only 1 player position and walls around.", 1);
		return (1);
	}
	return (0);
}
