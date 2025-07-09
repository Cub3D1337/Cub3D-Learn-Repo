/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:46:22 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/09 18:18:12 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_pointF dda(t_cub *cub, t_pointF start, double rayDirX, double rayDirY, double *out_dist)
{
	t_pointI map;
	t_pointF sideDist;
	t_pointF deltaDist;
	t_pointI step;
	t_bool hit = false;
	int side; // 0 = x side, 1 = y side

	map.x = (int)(start.x / MAP_SIZE);
	map.y = (int)(start.y / MAP_SIZE);

	deltaDist.x = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	deltaDist.y = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

	if (rayDirX < 0)
	{
		step.x = -1;
		sideDist.x = (start.x / MAP_SIZE - map.x) * deltaDist.x;
	}
	else
	{
		step.x = 1;
		sideDist.x = (map.x + 1.0 - start.x / MAP_SIZE) * deltaDist.x;
	}
	if (rayDirY < 0)
	{
		step.y = -1;
		sideDist.y = (start.y / MAP_SIZE - map.y) * deltaDist.y;
	}
	else
	{
		step.y = 1;
		sideDist.y = (map.y + 1.0 - start.y / MAP_SIZE) * deltaDist.y;
	}

	while (!hit)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			map.y += step.y;
			side = 1;
		}

		if (map.x < 0 || map.x >= MAP_WIDTH || map.y < 0 || map.y >= MAP_HEIGHT)
			break;

		if (cub->map[map.y][map.x] == 1)
			hit = true;
	}

	double dist;
	if (side == 0)
		dist = (map.x - start.x / MAP_SIZE + (1 - step.x) / 2) / rayDirX;
	else
		dist = (map.y - start.y / MAP_SIZE + (1 - step.y) / 2) / rayDirY;

	*out_dist = dist * MAP_SIZE; // Convert from map units to pixels

	t_pointF hit_point;
	hit_point.x = start.x + rayDirX * (*out_dist);
	hit_point.y = start.y + rayDirY * (*out_dist);
	return hit_point;
}

