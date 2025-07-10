/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:21:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/10 17:23:33 by abnsila          ###   ########.fr       */
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
	cub->ply.x = (MAP_WIDTH * MAP_SIZE) / 2 + (MAP_SIZE / 2);
	cub->ply.y = (MAP_HEIGHT * MAP_SIZE) / 2 - (MAP_SIZE / 2);
	cub->ply.size = 5;
	cub->ply.move_up = false;
	cub->ply.move_down = false;
	cub->ply.rotate_left = false;
	cub->ply.rotate_right = false;
	cub->ply.angle = (3 * M_PI) / 2;
	// Utils
	cub->last_time = 0.0;
	cub->frames = 0;
	cub->last_frame_time = 0.0;
}

void	init_image_buffer(t_cub *cub)
{
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	cub->img.img_ptr = mlx_new_image(cub->mlx,
			cub->width, cub->height);
	cub->img.img_pixels_ptr = mlx_get_data_addr(cub->img.img_ptr,
			&cub->img.bits_per_pixel, &cub->img.line_length,
			&cub->img.endian);
}

