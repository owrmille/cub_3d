/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:01:52 by iatopchu          #+#    #+#             */
/*   Updated: 2024/12/21 02:01:53 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

void	make_line_null_terminated(char *line)
{
	int	k;

	k = 0;
	while (line[k] && line[k] != '\n')
		k++;
	line[k] = '\0';
}

int	parse_input_file(t_data *data, char *filename)
{
	char	*first_line_in_map;

	first_line_in_map = process_graphical_info(data);
	if (!first_line_in_map)
		return (1);
	if (process_map(first_line_in_map, filename, data) == 1)
		return (1);
	if (check_map_validity(data) == 1)
		return (1);
	return (0);
}
