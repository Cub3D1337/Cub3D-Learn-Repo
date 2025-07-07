/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:06:22 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/07 20:53:59 by abnsila          ###   ########.fr       */
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

void	draw_ray(t_cub *cub, double start_x, int i)
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
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!touch(cub, ray_x, ray_y))
	{
		put_pixel(cub, ray_x, ray_y, 0x00ff00);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
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
