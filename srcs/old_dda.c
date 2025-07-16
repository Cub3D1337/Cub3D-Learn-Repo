/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:59:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/16 09:47:58 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// 	Given ply_pos (px, py), ray_dir (cos(O), sin(O)) for angle O
t_pointF	dda(t_cub *cub, t_pointF ply_pos, t_pointF ray_dir, double *out_dist)
{
	t_pointI	map;
	t_pointF	unit;
	t_pointF	hypotenuse_dist;
	t_pointI	step;
	t_bool		hit;
	int			side;
	double		dist;

	// → Take the int ply pos
	map.x = (int) (ply_pos.x / MAP_SIZE);
	map.y = (int) (ply_pos.y / MAP_SIZE);

	// → Compute horizontal increments (distance between two vertical lines along ray direction)
	unit.x = fabs(1 / ray_dir.x);
	// → Compute vertical increments (distance between two horizontal lines along ray direction)
	unit.y = fabs(1 / ray_dir.y);

	// → Compute first horizontal intersection point
	if (ray_dir.x < 0)
	{
		// → Left step
		step.x = -1;
		// → ((int x ply pos) + (double x ply pos)) * scale unit Hori grid
		hypotenuse_dist.x = ((ply_pos.x / MAP_SIZE) - map.x) * unit.x;
	}
	else
	{
		// → Right step
		step.x = 1;
		// → ((int x ply pos) + 1 unit to next Hori grid - (double x ply pos)) * scale unit Hori grid
		hypotenuse_dist.x = (map.x + 1.0 - (ply_pos.x / MAP_SIZE)) * unit.x;
	}
		// → Compute first vertical intersection point

	if (ray_dir.y < 0)
	{
		// → Up step
		step.y = -1;
		// → ((int y ply pos) + (double y ply pos)) * scale unit Ver grid
		hypotenuse_dist.y = ((ply_pos.y / MAP_SIZE) - map.y) * unit.y;
	}
	else
	{
		// → Down step
		step.y = 1;
		// → ((int y ply pos) + 1 unit to neyt Hori grid - (double y ply pos)) * scale unit Ver grid
		hypotenuse_dist.y = (map.y + 1 - (ply_pos.y / MAP_SIZE)) * unit.y;
	}

	hit = false;
	// Loop:
	while (!hit)
	{
		// if next horizontal c < next vertical c:
		if (hypotenuse_dist.x < hypotenuse_dist.y)
		{
			// advance horizontal point by horizontal step
			hypotenuse_dist.x += unit.x;
			map.x += step.x;
			side = 0; // x-side hit
		}
		// else:
		else
		{
			// advance vertical point by vertical step
			hypotenuse_dist.y += unit.y;
			map.y += step.y;
			side = 1; // y-side hit
		}
		// check map cell
		// if wall hit: break
		if (cub->map[map.y][map.x] == 1)
			hit = true;
	}

	// → Use final intersection point to compute final ray length c
	if (side == 0)
		dist = (map.x - ply_pos.x / MAP_SIZE + (1 - step.x) / 2) / ray_dir.x;
	else
		dist = (map.y - ply_pos.y / MAP_SIZE + (1 - step.y) / 2) / ray_dir.y;

	*out_dist = dist * MAP_SIZE; // Convert map units to pixels

	t_pointF hit_point;
	hit_point.x = ply_pos.x + ray_dir.x * (*out_dist);
	hit_point.y = ply_pos.y + ray_dir.y * (*out_dist);
	return (hit_point);
}


// We have a 2D plan (x, y) and a Player (px, py) and (1 x_unit == 1 y_unit)
// for each ray, they have an angle, called ray-angle (O)


// [ Horizontal intersections ]
//TODO: We want to calculate the x and y and c of the right-angle triangle of this Horizontal intersection
// x = Opposite    y = Adjacent    c = Hypotenuse

// [1] For the first intersection
//? So the y = 1 unit - py, now we know the Adjacent lenght (because the start position may be in the middle of the unit square)
// sin(O) = Adjacent / Hypotenuse , sin(O) = (1 - py) / c
// c = (1 - py) / sin(O)
// cos(O) = Opposite / Hypotenuse, cos(O) = x / c
// x = c * cos(O)
// x = ((1 - py) / sin(O)) * cos(O), x = ((1 - py) * cos(O)) / sin(O), x = (1 - py) / tan(O)
//! Finally x = (1 - py) / tan(O) , y = (1 - py) , c = (1 - py) / sin(O)

// [2] For the rest intersection
// All start position is perfectly in horizontal line
//? So the y = 1
// sin(O) = 1 / c
// c = 1 / sin(O)
// cos(O) = x / c, x = c * cos(O)
// x = (1 / sin(O)) * cos(O), x = cos(O) / sin(O), x = 1 / tan(O)
//! Finally x = 1 / tan(O), y = 1, c = 1 / sin(O)


// [ Vertical intersections ]
//TODO: We want to calculate the x and y and c of the right-angle triangle of this Vertical intersection
// x = Opposite    y = Adjacent    c = Hypotenuse

// [1] For the first intersection
//? So the x = 1 unit - px, now we know the Opposite lenght (because the start position may be in the middle of the unit square)
// cos(O) = (1 - px) / c
// c = (1 - px) / cos(O)
// sin(O) = y / c
// y = c * sin(O), y = ((1 - px) / cos(O)) * sin(O), y = ((1 - px) * sin(O)) / cos(O), y = ((1 - px)) * tan(O)
//! Finally x = (1 - px), y = (1 - px) * tan(O), c = (1 - px) / cos(O)

// [2] For the rest intersection
// All start position is perfectly in vertical line
//? So the x = 1
// cos(O) = 1 / c
// c = 1 / cos(O)
// sin(O) = y / c
// y = c * sin(O), y = (1 / cos(O)) * sin(O), y = sin(O) / cos(O), y = tan(O)
//! Finally x = 1, y = tan(O), c = 1 / cos(O)

