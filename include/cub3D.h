#ifndef CUB3D

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

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
    t_color floor_color;
    t_color ceiling_color;
    t_texture north_text;
    t_texture south_text;
    t_texture east_text;
    t_texture west_text;
} t_map;

typedef struct s_data
{
    int map_fd;
    char **map;
} t_data;

//file_check.c
int	valid_extension(char *av[]);
int map_exists(char *av[], t_data *data);
int parse_map(t_data *data);
#endif