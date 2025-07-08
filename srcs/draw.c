/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:06:22 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/08 14:55:21 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	if (x < 0 || x >= cub->width || y < 0 || y >= cub->height)
		return ;
	*(unsigned int *)(cub->img.img_pixels_ptr
		+ (y * cub->img.line_length + x * (cub->img.bits_per_pixel / 8)))
		= color;
}

t_bool	touch(t_cub *cub, double x, double y)
{
	int	px;
	int	py;

	px = x / MAP_SIZE;
	py = y / MAP_SIZE;
	if (cub->map[py][px] == 1)
		return (true);
	return (false);
}

double	fixed_dist(t_cub *cub, double x1, double y1, double x2, double y2)
{
	double	delta_x;
	double	delta_y;
	double	angle;
	double	fixed_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - cub->ply.angle;
	fixed_dist = sqrt(pow(delta_x, 2) + pow(delta_y, 2)) * cos(angle);
	return (fixed_dist);
}

void	draw_line(t_cub *cub, double ray_x, double ray_y, int i)
{
	// Draw lines
	double	dist;
	double	height;
	int		start_y;
	int		end;
	int		screen_x;

	dist = fixed_dist(cub, cub->ply.x ,cub->ply.y ,ray_x, ray_y);
	height = (MAP_SIZE / dist) * (cub->width / 2);
	start_y = (cub->height - height) / 2;
	end = start_y + height;

	// 👇 Move 3D column to the right side of window
	// screen_x = MAP_VIEW_WIDTH + i;
	screen_x = i;
	while (start_y < end)
	{
		put_pixel(cub, screen_x, start_y, 0x0000ff);
		start_y++;
	}
}

void	draw_ray(t_cub *cub, double ray_angle, int i, t_bool build)
{
	(void)i;
	double	ray_x;
	double	ray_y;
	double	cos_angle;
	double	sin_angle;

	// The ray start from the player center
	ray_x = cub->ply.x + cub->ply.size / 2.0;
	ray_y = cub->ply.y + cub->ply.size / 2.0;
	// Get current angle cos and sin
	cos_angle = cos(ray_angle);
	sin_angle = sin(ray_angle);
	while (!touch(cub, ray_x, ray_y))
	{
		put_pixel(cub, ray_x, ray_y, 0x00ff00);
		ray_x += cos_angle * 0.1;
		ray_y += sin_angle * 0.1;
	}
	if (build)
		draw_line(cub, ray_x, ray_y, i);
}

void	draw_square(t_cub *cub, int x, int y, int size, int color)
{
	int	_x;
	int	_y;

	_y = 0;
	while (_y < size)
	{
		_x = 0;
		while (_x < size)
		{
			put_pixel(cub, (x + _x), (y + _y), color);
			_x++;
		}
		_y++;
	}
}
