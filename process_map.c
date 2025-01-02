/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:02:15 by iatopchu          #+#    #+#             */
/*   Updated: 2024/12/23 13:44:55 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_map_size(char *first_line_in_map, t_data *data)
{
	int		size_h;
	int		max_size_w;
	char	*line;

	size_h = 0;
	max_size_w = 0;
	line = first_line_in_map;
	while (line)
	{
		make_line_null_terminated(line);
		if (ft_strlen(line) > max_size_w)
			max_size_w = ft_strlen(line);
		free(line);
		line = get_next_line(data->fd);
		size_h++;
	}
	data->map_size_h = size_h;
	data->map_size_w = max_size_w;
	if (line)
		free(line);
	close(data->fd);
	if (data->map_size_h < 3 || data->map_size_w < 3)
		return (1);
	return (0);
}

char	*skip_graphical_info(t_data *data, char *line)
{
	line = get_next_line(data->fd);
	while (line)
	{
		make_line_null_terminated(line);
		if (is_map(line))
			break ;
		free(line);
		line = get_next_line(data->fd);
	}
	return (line);
}

int	read_map(char *filename, t_data *data)
{
	int		i;
	char	*line;

	line = NULL;
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
	{
		error("Failed to open file.", 1);
		return (1);
	}
	line = skip_graphical_info(data, line);
	i = 0;
	while (line)
	{
		make_line_null_terminated(line);
		data->map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(data->fd);
		i++;
	}
	data->map[i] = NULL;
	close(data->fd);
	return (0);
}

int	check_for_empty_lines_in_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (map[i][0] == '\0')
		{
			error("Empty line inside map.", 1);
			return (1);
		}
	}
	return (0);
}

int	process_map(char *first_line_in_map, char *filename, t_data *data)
{
	if (calculate_map_size(first_line_in_map, data) == 1)
	{
		error("Map size is not valid (should be at least 3x3).", 1);
		return (1);
	}
	data->map = (char **)malloc(sizeof(char *) * (data->map_size_h + 1));
	if (!data->map)
	{
		error("Failed to allocate memory for map.", 1);
		return (1);
	}
	if (read_map(filename, data) == 1)
		return (1);
	if (check_for_empty_lines_in_map(data->map) == 1)
		return (1);
	return (0);
}
