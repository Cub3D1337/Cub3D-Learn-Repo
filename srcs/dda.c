/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:46:22 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/16 13:24:59 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	setup_step(t_dda *dda, t_pointF ray_dir)
{
	if (ray_dir.x < 0)
		dda->step.x = -1;
	else
		dda->step.x = 1;
	if (ray_dir.y < 0)
		dda->step.y = -1;
	else
		dda->step.y = 1;
}

static void	setup_dda(t_dda *dda, t_pointF ply_pos, t_pointF ray_dir)
{
	dda->map.x = (int)(ply_pos.x / MAP_SIZE);
	dda->map.y = (int)(ply_pos.y / MAP_SIZE);
	dda->unit.x = fabs(1 / ray_dir.x);
	dda->unit.y = fabs(1 / ray_dir.y);
	dda->hit = false;
	dda->max_steps = fmax(MAP_WIDTH, MAP_HEIGHT) * 2;
	setup_step(dda, ray_dir);
	if (ray_dir.x < 0)
		dda->hypotenuse_dist.x = ((ply_pos.x / MAP_SIZE) - dda->map.x)
			* dda->unit.x;
	else
		dda->hypotenuse_dist.x = (dda->map.x + 1.0 - (ply_pos.x / MAP_SIZE))
			* dda->unit.x;
	if (ray_dir.y < 0)
		dda->hypotenuse_dist.y = ((ply_pos.y / MAP_SIZE) - dda->map.y)
			* dda->unit.y;
	else
		dda->hypotenuse_dist.y = (dda->map.y + 1 - (ply_pos.y / MAP_SIZE))
			* dda->unit.y;
}

static void	compute_ray_length(t_dda *dda, t_pointF ply_pos
		, t_pointF ray_dir, double *out_dist)
{
	double	dist;

	if (dda->side == 0)
		dist = (dda->map.x - ply_pos.x / MAP_SIZE
				+ (1 - dda->step.x) / 2) / ray_dir.x;
	else
		dist = (dda->map.y - ply_pos.y / MAP_SIZE
				+ (1 - dda->step.y) / 2) / ray_dir.y;
	*out_dist = dist * MAP_SIZE;
	dda->hit_point.x = ply_pos.x + ray_dir.x * (*out_dist);
	dda->hit_point.y = ply_pos.y + ray_dir.y * (*out_dist);
}

t_pointF	dda_algo(t_cub *cub, t_pointF ply_pos
			, t_pointF ray_dir, double *out_dist)
{
	t_dda	dda;

	setup_dda(&dda, ply_pos, ray_dir);
	while (!dda.hit && dda.max_steps-- > 0)
	{
		if (dda.hypotenuse_dist.x < dda.hypotenuse_dist.y)
		{
			dda.hypotenuse_dist.x += dda.unit.x;
			dda.map.x += dda.step.x;
			dda.side = 0;
		}
		else
		{
			dda.hypotenuse_dist.y += dda.unit.y;
			dda.map.y += dda.step.y;
			dda.side = 1;
		}
		if (dda.map.x < 0 || dda.map.x >= MAP_WIDTH
			|| dda.map.y < 0 || dda.map.y >= MAP_HEIGHT)
			break ;
		if (cub->map[dda.map.y][dda.map.x] == 1)
			dda.hit = true;
	}
	compute_ray_length(&dda, ply_pos, ray_dir, out_dist);
	return (dda.hit_point);
}
