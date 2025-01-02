/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:02:35 by iatopchu          #+#    #+#             */
/*   Updated: 2024/12/21 02:26:20 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_directions(char **map, int cur_x, int cur_y, int map_size_h)
{
	if (find_path(map, cur_x + 1, cur_y, map_size_h))
		return (1);
	if (find_path(map, cur_x - 1, cur_y, map_size_h))
		return (1);
	if (find_path(map, cur_x, cur_y + 1, map_size_h))
		return (1);
	if (find_path(map, cur_x, cur_y - 1, map_size_h))
		return (1);
	if (find_path(map, cur_x + 1, cur_y + 1, map_size_h))
		return (1);
	if (find_path(map, cur_x - 1, cur_y - 1, map_size_h))
		return (1);
	if (find_path(map, cur_x + 1, cur_y - 1, map_size_h))
		return (1);
	if (find_path(map, cur_x - 1, cur_y + 1, map_size_h))
		return (1);
	return (0);
}

int	find_path(char **map, int cur_x, int cur_y, int map_size_h)
{
	int	x;
	int	y;

	x = cur_x;
	y = cur_y;
	if (y < 0 || y >= map_size_h
		|| x < 0 || x >= ft_strlen(map[y])
		|| (map[y][x] && (map[y][x] == ' ' || map[y][x] == '\0')))
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	if (find_directions(map, x, y, map_size_h))
		return (1);
	return (0);
}

char	**create_map_copy(t_data *data)
{
	char		**map_copy;
	int			i;

	map_copy = malloc(sizeof(char *) * (data->map_size_h + 1));
	if (!map_copy)
	{
		error("Memory allocation error.", 1);
		return (NULL);
	}
	i = -1;
	while (++i < data->map_size_h)
		map_copy[i] = ft_strdup(data->map[i]);
	map_copy[i] = NULL;
	return (map_copy);
}

int	check_map_validity(t_data *data)
{
	char		**map_copy;

	if (check_chars_validity(data) == 1)
		return (1);
	map_copy = create_map_copy(data);
	if (!map_copy)
		return (1);
	if (find_path(map_copy,
			data->player->pos.x, data->player->pos.y, data->map_size_h) == 1)
	{
		error("Map is not enclosed or does not have player position.", 1);
		free_map(map_copy, data->map_size_h);
		return (1);
	}
	free_map(map_copy, data->map_size_h);
	return (0);
}
