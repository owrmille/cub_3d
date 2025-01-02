/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:14:45 by meroshen          #+#    #+#             */
/*   Updated: 2024/12/23 15:02:19 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_input(char *str, int *fd)
{
	int		len;
	char	*file_name;

	len = ft_strlen(str);
	file_name = str;
	if (len < 5)
		return (1);
	if (ft_strncmp(str + len - 4, ".cub", 4) == 0)
	{
		*fd = open(file_name, O_RDONLY);
		if (*fd == -1)
		{
			exit(error("Failed to open file", 1));
		}
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2 || check_input(argv[1], &fd) == 1)
		return (error("Incorrect input", 1));
	init_data(&data, fd);
	init_mlx(&data);
	if (parse_input_file(&data, argv[1]) == 1)
		ft_exit(&data, 1);
	mlx_loop_hook(data.mlx_ptr, rendering, &data);
	mlx_hook(data.mlx_win, DestroyNotify, NoEventMask, event_quit, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_handler, &data);
	mlx_hook(data.mlx_win, MotionNotify, PointerMotionMask, mouse_move, &data);
	mlx_loop(data.mlx_ptr);
	ft_exit(&data, 0);
}
