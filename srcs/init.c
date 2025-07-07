/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:21:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/07 12:22:05 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_cub(t_cub *cub)
{
	srand(time(NULL));
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit(EXIT_FAILURE);
	cub->width = WIDTH;
	cub->height = HEIGHT;
	cub->win = mlx_new_window(cub->mlx, cub->width,
			cub->height, "Cub-3d");
	if (!cub->win)
		ft_exit(cub);
	cub->img.img_ptr = NULL;
}
