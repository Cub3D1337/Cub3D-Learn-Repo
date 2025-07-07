/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:09:37 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/07 18:22:24 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "includes.h"

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	double	x;
	double	y;
	int		size;
	t_bool	move_up;
	t_bool	move_down;
	t_bool	rotate_left;
	t_bool	rotate_right;
	double	angle;
}				t_player;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_img		img;
	t_player	ply;
	int			map[MAP_HEIGHT][MAP_WIDTH];
}				t_cub;

#endif
