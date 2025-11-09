#include "../include/cub3D.h"

static void raycast_init(t_data *data, t_raycast *ray, int x)
{
  //calculate ray position and direction
      ray->cameraX = 2.0 * (double)x / (double)WIDTH - 1.0; //x-coordinate in camera space
      ray->rayDirX = data->game->dirX + data->game->planeX *  ray->cameraX;
      ray->rayDirY = data->game->dirY + data->game->planeY *  ray->cameraX;
      //which box of the map we're in
      ray->mapX = (int)data->game->posX;
      ray->mapY = (int)data->game->posY;

      //length of ray from current position to next x or y-side

       //length of ray from one x or y-side to next x or y-side
      ray->deltaDistX = ( ray->rayDirX == 0) ? 1e30 : fabs(1 /  ray->rayDirX);
      ray->deltaDistY = ( ray->rayDirY == 0) ? 1e30 : fabs(1 /  ray->rayDirY);

      ray->hit = 0; //was there a wall hit?
}

static void raycast_dist(t_data *data, t_raycast *ray)
{
  if ( ray->rayDirX < 0)
      {
        ray->stepX = -1;
         ray->sideDistX = (data->game->posX -  ray->mapX) *  ray->deltaDistX;
      }
      else
      {
        ray->stepX = 1;
         ray->sideDistX = (ray->mapX + 1.0 - data->game->posX) *  ray->deltaDistX;
      }
      if ( ray->rayDirY < 0)
      {
        ray->stepY = -1;
         ray->sideDistY = (data->game->posY - ray->mapY) *  ray->deltaDistY;
      }
      else
      {
        ray->stepY = 1;
         ray->sideDistY = (ray->mapY + 1.0 - data->game->posY) *  ray->deltaDistY;
      }
}

static void DDA(t_data *data, t_raycast *ray)
{
	 while (ray->hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if ( ray->sideDistX <  ray->sideDistY)
        {
           ray->sideDistX +=  ray->deltaDistX;
          ray->mapX += ray->stepX;
          ray->side = 0;
        }
        else
        {
           ray->sideDistY +=  ray->deltaDistY;
          ray->mapY += ray->stepY;
          ray->side = 1;
        }
        //Check if ray has hit a wall
        if(ray->mapX >= 0 && ray->mapX < data->game->map_height && ray->mapY >= 0 && ray->mapY < data->game->map_width)
        {
          if (data->game->world_map[ray->mapX][ray->mapY] > 0) ray->hit = 1;
        }
        else
        {
          ray->hit = 1; // Prevents out-of-bounds access
        }
      }
}

static void wall_calc(t_raycast *ray)
{
   if(ray->side == 0)  ray->perpWallDist = ( ray->sideDistX -  ray->deltaDistX);
      else           ray->perpWallDist = ( ray->sideDistY -  ray->deltaDistY);

  if (ray->perpWallDist <= 0.0001)
  {
      ray->perpWallDist = 0.0001;
  }

      //Calculate height of line to draw on screen
      ray->lineHeight = (int)(HEIGHT /  ray->perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
      if(ray->drawStart < 0)ray->drawStart = 0;
      ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
      if(ray->drawEnd >= HEIGHT)ray->drawEnd = HEIGHT - 1;

	  //int texNum = data->game->world_map[ray->mapX][ray->mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //draw_line(data, x, drawStart, x, drawEnd, color);
}

static void sel_texture(t_data *data, t_img *texture, t_raycast ray)
{
if (ray.side == 1)
	{
		if (ray.rayDirY < 0)
			*texture = data->game->textures[0];
		else
			*texture = data->game->textures[2];
	}
	else
	{
		if (ray.rayDirX < 0)
			*texture = data->game->textures[3];
		else
			*texture = data->game->textures[1];
	}
}

static void	texture_calc(t_data *data, t_raycast *ray, t_img *texture)
{
	if (ray->side == 0)
		ray->wallX = data->game->posY + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = data->game->posX + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor(ray->wallX);
	ray->tex_x = (int)(ray->wallX * (double)(texture->width));
	if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1
			&& ray->rayDirY < 0))
		ray->tex_x = texture->width - ray->tex_x - 1;
}

static void draw_wall_column(t_data *data, t_raycast *ray, t_img *texture, int x)
{
	ray->y = ray->drawStart;
	while (ray->y < ray->drawEnd)
	{
		ray->d = ray->y * 256 - HEIGHT * 128 + ray->lineHeight * 128;
		ray->tex_y = ((ray->d * texture->height) / ray->lineHeight) / 256;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		else if (ray->tex_y >= texture->height)
			ray->tex_y = texture->height - 1;
		ray->color = *(unsigned int *)(texture->addr + (ray->tex_y
					* texture->line_length + ray->tex_x * (texture->bpp / 8)));
		put_pixel_walls(&data->game->img, x, ray);
		ray->y++;
	}
}

static void draw_ceiling_and_floor(t_raycast *ray, t_data *data, int x)
{

	ray->y = 0;
	while (ray->y < ray->drawStart)
	{
		put_pixel_ceiling(data, x, ray->y);
		ray->y++;
	}
	ray->y = ray->drawEnd;
	while (ray->y < HEIGHT)
	{
		put_pixel_floor(data, x, ray->y);
		ray->y++;
	}
}

void draw_view(t_data *data)
{
	t_raycast ray;
  t_img texture;
	int x;

	x = 0;
	while(x < WIDTH)
    {
      raycast_init(data, &ray, x);
      raycast_dist(data, &ray);
	    DDA(data, &ray);
      wall_calc(&ray);
      sel_texture(data, &texture, ray);
      texture_calc(data, &ray, &texture);
      draw_wall_column(data, &ray, &texture, x);
      draw_ceiling_and_floor(&ray, data, x);
	  x++;
    }
}


