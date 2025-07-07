/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:53:45 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/07 20:25:38 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "includes.h"
# include "settings.h"
# include "typedef.h"

// Init
void	init_cub(t_cub *cub);
void	init_image_buffer(t_cub *cub);

// Draw
void	put_pixel(t_cub *cub, int x, int y, int color);
void	draw_square(t_cub *cub, int x, int y, int size, int color);
void	draw_player(t_cub *cub);
void	draw_map(t_cub *cub);
// Raycasting Draw
t_bool	touch(t_cub *cub, double x, double y);
void	draw_ray(t_cub *cub, double start_x, int i);
void	raycast(t_cub *cub);
void	draw(t_cub *cub);

// Events
void	init_events(t_cub *cub);

// Cleanup
void	destroy_cub(t_cub *cub);
int		ft_exit(t_cub *cub);

#endif
