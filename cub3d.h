/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:34:09 by meroshen          #+#    #+#             */
/*   Updated: 2025/01/02 16:29:56 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define SPEED_MOV 0.125

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# include "./Libft/libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdint.h>

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

/*	map_pos - position of the ray on the map grid (square)
	delta_dist - distance to the next nearist x(delta_dist.x) and y(delta_dist.y)
	wall_dist - distance to the wall
	step - direction of step*/
typedef struct s_ray
{
	t_vector		dir;
	t_int_vector	map_pos;
	t_vector		delta_dist;
	t_vector		side_dist;
	double			wall_dist;
	t_int_vector	step;
	int				is_hit_side_y;
	double			collis_pnt_x;
}	t_ray;

typedef struct s_image
{
	void	*mlx_img;
	char	*img_pixels_ptr;
	int		bpp;
	int		endian;
	int		size_line;
	int		width;
	int		height;
}			t_image;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_data
{
	int			running;
	void		*mlx_ptr;
	void		*mlx_win;
	char		**map;
	int			map_size_h;
	int			map_size_w;
	int			player_pos_flg;
	t_player	*player;
	t_ray		*ray;
	t_image		*img;
	t_image		*textures;
	t_color		color_c;
	t_color		color_f;
	int			fd;
}	t_data;

typedef struct s_line_data
{
	int	x;
	int	line_height;
	int	line_start;
	int	line_end;
}	t_line_data;

typedef struct s_for_norm
{
	double			step;
	double			pos;
	int				y;
	int				x;
	int				y_scr;
	t_int_vector	vect_txtr;
	t_int_vector	vect_scr;

}	t_for_norm;

void			init_data(t_data *data, int fd);
void			init_mlx(t_data *data);
void			init_ray(t_data *data);
int				error(char *str, int code);
int				rendering(t_data *data);
int				event_quit(t_data *data);
int				ft_exit(t_data *data, int code);
t_vector		vector_create(double x, double y);
t_int_vector	vector_int_create(int x, int y);
t_vector		vector_koef(t_vector a, double koef);
t_vector		vector_add(t_vector a, t_vector b);
double			vector_norm(t_vector a);
t_vector		vector_rot(t_vector a, double alpha);
int				rendering(t_data *data);
void			recreate_img(t_data *data);
int				key_handler(int key, t_data *data);
void			load_texture(t_data *data, int tex_num, char *file_path);
void			draw_col_texture(t_data *data, t_line_data *line);
void			put_pixel(t_data *data, int x, int y, t_color color);
int				mouse_move(int x, int y, t_data *data);
void			free_data(t_data *data);
int				is_start_of_map(char *line);
void			make_line_null_terminated(char *line);
void			init_flgs(int *success_flgs, int len);
int				all_fields_processed_successfully(int *success_flgs, int len);
void			init_raycast_data(int x, t_data *data);
void			raycast_exec(t_data *data);
void			copy_pixel(t_image *texture, t_int_vector txtr_point, \
								t_data *data, t_int_vector scr_point);
void			init_statuses(int *statuses, int len);
int				find_path(char **map, int cur_x, int cur_y, int map_size_h);
void			free_map(char **map, int map_size_h);
int				check_map_validity(t_data *data);
int				check_chars_validity(t_data *data);
void			skip_spaces(char *line, int *i);
int				process_map(char *first_line_in_map, char *filename, \
															t_data *data);
int				ft_isspace(char c);
bool			is_map(char *line);
void			check_graphical_errors(t_data *data, char *line, \
														int statuses[6]);
char			*process_graphical_info(t_data *data);
void			make_line_null_terminated(char *line);
int				parse_input_file(t_data *data, char *filename);

#endif