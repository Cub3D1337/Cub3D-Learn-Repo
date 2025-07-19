/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:06:22 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/19 11:58:10 by abnsila          ###   ########.fr       */
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

void draw_ray(t_cub *cub, double ray_angle, int x, t_bool build)
{
	t_pointF	ply_pos;
	t_pointF	ray_dir;
	t_pointF	hit_point;
	double		perp_dist;

	ply_pos.x = cub->ply.x + cub->ply.size / 2.0;
	ply_pos.y = cub->ply.y + cub->ply.size / 2.0;

	ray_dir.x = cos(ray_angle);
	ray_dir.y = sin(ray_angle);

	hit_point = dda_algo(cub, ply_pos, ray_dir, &perp_dist);
	(void)hit_point; // TODO: Understand the fish-eye effect

	// Remove fish-eye effect
	// double corrected_dist = perp_dist * cos(ray_angle - cub->ply.angle);

	// double line_height = (MAP_SIZE / corrected_dist) * (cub->width / 2);
	double line_height = (MAP_SIZE / perp_dist) * (cub->width / 2);
	if (line_height > cub->height)
    	line_height = cub->height;
	int draw_start = (cub->height - line_height) / 2;
	int draw_end = draw_start + line_height;

	if (build)
	{
		for (int y = draw_start; y < draw_end; y++)
			put_pixel(cub, x, y, 0x0000ff);
	}
}

void	draw_square(t_cub *cub, int x, int y, int size, int color)
{
	t_pointI	incr_pos;

	incr_pos.y = 0;
	while (incr_pos.y < size)
	{
		incr_pos.x = 0;
		while (incr_pos.x < size)
		{
			put_pixel(cub, (x + incr_pos.x), (y + incr_pos.y), color);
			incr_pos.x++;
		}
		incr_pos.y++;
	}
}
