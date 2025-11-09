#ifndef CUB3D

# include "../dependencies/libft/libft.h"
# include "../dependencies/mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include <math.h>

# define WIDTH 640
# define HEIGHT 480

typedef struct s_raycast
{
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit;
    int side;
    double wallX;
    int tex_x;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int tex_y;
    int color;
    int y;
    int d;
}   t_raycast;

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
    int red;
    int green;
    int blue;
} t_color;

typedef struct s_texture
{
    char *path;
} t_texture;

typedef struct s_map
{
    char **matrix;
    t_color *floor_color;
    t_color *ceiling_color;
    t_texture *north_text;
    t_texture *south_text;
    t_texture *east_text;
    t_texture *west_text;
} t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			map_width;
	int			map_height;
    t_img   img;
    t_img textures[4];
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double time;
    double oldTime;
    int key_a;
    int key_w;
    int key_s;
    int key_d;
    double moveSpeed;
    double rotateSpeed;
    int **world_map;
    int c_hex;
    int f_hex;
}				t_game;

typedef struct s_data
{
    int map_fd;
    t_map *map;
    t_game *game;
} t_data;

//file_check.c
int	valid_extension(char *av[]);
int map_exists(char *av[], t_data *data);
int parse_map(t_data *data);

//play.c
void mainloop(t_data *data);

//keys.c
int close_window(t_data *data);
void	update_movement(t_data *data, int **worldMap);
int	key_press(int key, t_data *data);
int	key_release(int key, t_data *data);

//move.c
void move_forward(int poscheckX, int poscheckY, t_game *game);
void move_backwards(int poscheckX, int poscheckY, t_game *game);
void rotate_right(t_game *game);
void rotate_left(t_game *game);

//raycasting.c
void draw_view(t_data *data);

//draw.c
void	put_pixel_walls(t_img *img, int x, t_raycast *rcw);
void put_pixel_ceiling(t_data *data, int x, int y);
void put_pixel_floor(t_data *data, int x, int y);

//load_text.c
int	load_textures(t_data *data);
#endif
