/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoniof <antoniof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 20:47:05 by antoniof          #+#    #+#             */
/*   Updated: 2025/12/18 20:54:45 by antoniof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../dependencies/libft/libft.h"
# include "../dependencies/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1080
# define HEIGHT 1020

typedef struct s_raycast
{
	double		camera_x;
	double		ray_dirx;
	double		ray_diry;
	int			map_x;
	int			map_y;
	double		side_distx;
	double		side_disty;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perpwall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		wall_x;
	int			tex_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_y;
	int			color;
	int			y;
	int			d;
}				t_raycast;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_texture
{
	char		*path;
}				t_texture;

typedef struct s_map
{
	char		**matrix;
	t_color		*floor_color;
	t_color		*ceiling_color;
	t_texture	*north_text;
	t_texture	*south_text;
	t_texture	*east_text;
	t_texture	*west_text;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			map_width;
	int			map_height;
	t_img		img;
	t_img		textures[4];
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	double		move_speed;
	double		rotate_speed;
	int			**world_map;
	int			c_hex;
	int			f_hex;
}				t_game;

typedef struct s_data
{
	int			map_fd;
	t_map		*map;
	t_game		*game;
}				t_data;

// file_check.c
int				valid_extension(char *av[]);
int				parse_map(t_data *data);
void			check_texture_file(char *path);

// play.c
void			mainloop(t_data *data);

// keys.c
void			update_movement(t_data *data, int **worldMap);
int				key_press(int key, t_data *data);
int				key_release(int key, t_data *data);
int				can_move(t_data *data, double xy[], int **worldMap,
					double radius);
void			move_for(t_data *data, double next[], int **worldMap,
					double variables[]);
void			move_back(t_data *data, double next[], int **worldMap,
					double variables[]);
void			move(t_data *data, int **worldMap, double variables[]);

// move.c
void			move_forward(int poscheckX, int poscheckY, t_game *game);
void			move_backwards(int poscheckX, int poscheckY, t_game *game);
void			rotate_right(t_game *game);
void			rotate_left(t_game *game);

// raycasting.c
void			draw_view(t_data *data);
void			raycast_init(t_data *data, t_raycast *ray, int x);
void			raycast_dist(t_data *data, t_raycast *ray);
void			dda(t_data *data, t_raycast *ray);
void			wall_calc(t_raycast *ray);

// draw.c
void			put_pixel_walls(t_img *img, int x, t_raycast *rcw);
void			put_pixel_ceiling(t_data *data, int x, int y);
void			put_pixel_floor(t_data *data, int x, int y);

// load_text.c
void			load_textures(t_data *data);

// parser.c
void			parse_cub_file(t_data *data);

// parser_utils.c
void			add_map_line(char ***map, char *line);
int				map_height(char **map);
int				map_width(char **map);
int				is_empty_line(char *line);
int				is_map_line(char *line);

// parser_config.c
void			parse_config_line(t_map *map, char *line);

// parser_map.c
char			get_map_char(t_map *map, int y, int x);
void			validate_map_chars(t_map *map);
void			validate_closed_map(t_map *map);

// error.c
void			error_exit(char *msg);

// gnl.c
char			*get_next_line(int fd);

// utils.c
void			trim_newline(char *s);
char			*trim_spaces(char *s);
int				is_unsigned_number(char *s);
int				split_len(char **split);
void			free_split(char **split);

// frees.c
int				close_window(t_data *data);
void			early_free(t_data *data);
// init.c
void			init_game(t_data *data);
#endif
