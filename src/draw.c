#include "../include/cub3D.h"

void draw_line(t_data *data, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;

	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(data->game->mlx, data->game->win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}
/*
static int	apply_fog(int color, double distance, double max_distance)
{
	double	fog_factor;
	int		fog_color;
	int		rgb[3];
	int		fog[3];
	int		new[3];

	fog_color = 0x000000;
	fog_factor = distance / max_distance;
	if (fog_factor > 1.0)
		fog_factor = 1.0;
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	fog[0] = (fog_color >> 16) & 0xFF;
	fog[1] = (fog_color >> 8) & 0xFF;
	fog[2] = fog_color & 0xFF;
	new[0] = (int)(rgb[0] * (1.0 - fog_factor) + fog[0] * fog_factor);
	new[1] = (int)(rgb[1] * (1.0 - fog_factor) + fog[1] * fog_factor);
	new[2] = (int)(rgb[2] * (1.0 - fog_factor) + fog[2] * fog_factor);
	return ((new[0] << 16) | (new[1] << 8) | new[2]);
}
*/

/**
 * @brief Draws a pixel on the floor with fog effect applied
 *
 * Places a pixel at the specified coordinates in the image buffer,
 * applying fog effect to the floor color based on the distance from the viewer.
 * Ensures the pixel coordinates are within the screen boundaries.
 *
 * @param data Main program variables structure containing floor color
 * @param x X-coordinate in the image buffer
 * @param y Y-coordinate in the image buffer
 * @param fogDistance Distance value used to calculate fog intensity
 */
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

/**
 * @brief Draws a pixel on the ceiling with fog effect applied
 *
 * Places a pixel at the specified coordinates in the image buffer,
 * applying fog effect to the ceiling color based on the distance from the viewer.
 * Ensures the pixel coordinates are within the screen boundaries.
 *
 * @param data Main program variables structure containing ceiling color
 * @param x X-coordinate in the image buffer
 * @param y Y-coordinate in the image buffer
 * @param fogDistance Distance value used to calculate fog intensity
 */
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

/**
 * @brief Draws a pixel on a wall with fog effect applied
 *
 * Places a pixel at the specified coordinates in the image buffer,
 * applying fog effect to the wall texture color based on the perpendicular
 * wall distance. Ensures the pixel coordinates are within the screen boundaries.
 *
 * @param img Image buffer to draw to
 * @param x X-coordinate in the image buffer
 * @param rcw Wall rendering information including Y-coordinate, color, and perpendicular distance
 */
void	put_pixel_walls(t_img *img, int x, t_raycast *rcw)
{
    char	*dst;

    if (x >= 0 && x < WIDTH && rcw->y >= 0 && rcw->y < HEIGHT)
    {
        dst = img->addr + (rcw->y * img->line_length + x * (img->bpp / 8));
        *(unsigned int *)dst = rcw->color; /* no fog */
    }
}
