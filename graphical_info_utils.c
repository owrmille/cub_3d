/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_info_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 02:03:17 by iatopchu          #+#    #+#             */
/*   Updated: 2024/12/21 02:03:18 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\n'
		|| c == '\t'
		|| c == '\r'
		|| c == '\v'
		|| c == '\f');
}

void	init_statuses(int *statuses, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		statuses[i] = 0;
}

bool	is_map(char *line)
{
	int		i;
	bool	has_non_space_char;

	i = 0;
	has_non_space_char = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (false);
		if (!has_non_space_char && (line[i] == '0' || line[i] == '1'
				|| line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W'))
			has_non_space_char = true;
		i++;
	}
	if (!has_non_space_char)
		return (false);
	return (true);
}

bool	were_all_fields_processed_successfully(int *statuses, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (statuses[i] != 1)
			return (false);
	}
	return (true);
}

void	check_graphical_errors(t_data *data, char *line, int statuses[6])
{
	if (!were_all_fields_processed_successfully(statuses, 6))
	{
		if (line)
			free(line);
		ft_exit(data, error("Graphical information is not correct.", 1));
	}
	else if (!line)
		ft_exit(data, error("There is no map in file.", 1));
}
