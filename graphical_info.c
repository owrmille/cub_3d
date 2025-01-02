/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:03:08 by iatopchu          #+#    #+#             */
/*   Updated: 2024/12/21 02:03:09 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_texture(char *line, int *i, int tex_num, t_data *data)
{
	(*i) += 2;
	skip_spaces(line, i);
	load_texture(data, tex_num, line + (*i));
	return (1);
}

int	return_color_number(char *line, int *i)
{
	int	num;

	num = 0;
	while (ft_isdigit(line[*i]))
	{
		num = num * 10 + line[*i] - '0';
		(*i)++;
	}
	while (ft_isspace(line[*i]) || line[*i] == ',')
		(*i)++;
	return (num);
}

int	process_color(char *line, int *i, t_data *data)
{
	if (line[*i] == 'F')
	{
		(*i)++;
		skip_spaces(line, i);
		data->color_f.r = return_color_number(line, i);
		data->color_f.g = return_color_number(line, i);
		data->color_f.b = return_color_number(line, i);
	}
	else if (line[*i] == 'C')
	{
		(*i)++;
		skip_spaces(line, i);
		data->color_c.r = return_color_number(line, i);
		data->color_c.g = return_color_number(line, i);
		data->color_c.b = return_color_number(line, i);
	}
	return (1);
}

void	read_graphical_info(t_data *data, char *line, int *statuses, int *i)
{
	if (line[*i] == 'F')
		statuses[0] += process_color(line, i, data);
	else if (line[*i] == 'C')
		statuses[1] += process_color(line, i, data);
	else if (ft_strncmp(line + *i, "NO ", 3) == 0)
		statuses[2] += process_texture(line, i, NORTH, data);
	else if (ft_strncmp(line + *i, "SO ", 3) == 0)
		statuses[3] += process_texture(line, i, SOUTH, data);
	else if (ft_strncmp(line + *i, "WE ", 3) == 0)
		statuses[4] += process_texture(line, i, WEST, data);
	else if (ft_strncmp(line + *i, "EA ", 3) == 0)
		statuses[5] += process_texture(line, i, EAST, data);
}

char	*process_graphical_info(t_data *data)
{
	char	*line;
	int		i;
	int		statuses[6];

	init_statuses(statuses, 6);
	line = get_next_line(data->fd);
	while (line)
	{
		make_line_null_terminated(line);
		if (is_map(line))
			break ;
		i = 0;
		skip_spaces(line, &i);
		read_graphical_info(data, line, statuses, &i);
		if (line)
			free(line);
		line = get_next_line(data->fd);
	}
	check_graphical_errors(data, line, statuses);
	return (line);
}
