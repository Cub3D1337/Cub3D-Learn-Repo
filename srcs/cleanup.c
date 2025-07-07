/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:22:33 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/07 12:34:09 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	destroy_cub(t_cub *cub)
{
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
}

int	ft_exit(t_cub *cub)
{
	destroy_cub(cub);
	ft_printf("Programme exit successfuly\n");
	exit(EXIT_SUCCESS);
}
