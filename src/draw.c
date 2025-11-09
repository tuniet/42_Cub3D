#include "../include/cub3D.h"

void	put_pixel_floor(t_data *data, int x, int y)
{
    t_img	*img;
    char	*dst;

    img = &data->game->img;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
        *(unsigned int *)dst = data->game->f_hex; /* no fog */
    }
}

void	put_pixel_ceiling(t_data *data, int x, int y)
{
    t_img	*img;
    char	*dst;

    img = &data->game->img;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
        *(unsigned int *)dst = data->game->c_hex; /* no fog */
    }
}

void	put_pixel_walls(t_img *img, int x, t_raycast *rcw)
{
    char	*dst;

    if (x >= 0 && x < WIDTH && rcw->y >= 0 && rcw->y < HEIGHT)
    {
        dst = img->addr + (rcw->y * img->line_length + x * (img->bpp / 8));
        *(unsigned int *)dst = rcw->color; /* no fog */
    }
}
