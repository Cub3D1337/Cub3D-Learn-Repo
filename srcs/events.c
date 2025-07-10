/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:57:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/10 19:23:18 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_edges(t_cub *cub, double new_x, double	new_y)
{
	int	ply_corners[4][2];
	
	ply_corners[0][0] = new_x / MAP_SIZE;
	ply_corners[0][1] = new_y / MAP_SIZE;
	ply_corners[1][0] = (new_x + cub->ply.size - 1) / MAP_SIZE;
	ply_corners[1][1] = new_y / MAP_SIZE;
	ply_corners[2][0] = new_x / MAP_SIZE;
	ply_corners[2][1] = (new_y + cub->ply.size - 1) / MAP_SIZE;
	ply_corners[3][0] = (new_x + cub->ply.size - 1) / MAP_SIZE;
	ply_corners[3][1] = (new_y + cub->ply.size - 1) / MAP_SIZE;
	if (cub->map[ply_corners[0][1]][ply_corners[0][0]] == 0 &&
		cub->map[ply_corners[1][1]][ply_corners[1][0]] == 0 &&
		cub->map[ply_corners[2][1]][ply_corners[2][0]] == 0 &&
		cub->map[ply_corners[3][1]][ply_corners[3][0]] == 0)
	{
		cub->ply.x = new_x;
		cub->ply.y = new_y;
	}
}

void	move(t_cub *cub)
{
	double	new_x;
	double	new_y;

	// Update the rotation angle A, D
	if (cub->ply.rotate_left)
		cub->ply.angle -= ROT_SPEED;
	else if (cub->ply.rotate_right)
		cub->ply.angle += ROT_SPEED;
	//TODO: You need to understand the Normalize angle to 0 ~ 2π
	if (cub->ply.angle < 0)
		cub->ply.angle += 2 * M_PI;
	if (cub->ply.angle >= 2 * M_PI)
		cub->ply.angle -= 2 * M_PI;
	// Future position variables
	new_x = cub->ply.x;
	new_y = cub->ply.y;
	// Move forward
	if (cub->ply.move_up)
	{
		new_x += cos(cub->ply.angle) * SPEED;
		new_y += sin(cub->ply.angle) * SPEED;
	}
	// Move backward
	if (cub->ply.move_down)
	{
		new_x -= cos(cub->ply.angle) * SPEED;
		new_y -= sin(cub->ply.angle) * SPEED;
	}
	check_edges(cub, new_x, new_y);
}

void	raycast(t_cub *cub, t_bool build)
{
	double	fraction;
	double	ray_angle;
	int		i;

	// Only draw on right side
	fraction = M_PI / 3 / cub->width;
	ray_angle = cub->ply.angle - M_PI / 6;
	i = 0;
	while (i < cub->width)
	{
		draw_ray(cub, ray_angle, i, build);
		ray_angle += fraction;
		i++;
	}
}

int ft_loop_hook(t_cub *cub)
{
	double	current;

	if (!cub || !cub->img.img_ptr)
		ft_exit(cub);
	// Increment frame
	cub->frames++;
	current = get_time_ms();
	
	if (current - cub->last_time >= 1000.0)
	{
		cub->fps = cub->frames;     // Store the counted frames before resetting
		cub->frames = 0;
		cub->last_time = current;
	}
	move(cub);
	draw(cub);
	return (EXIT_SUCCESS);
}


int	ft_key_press(int keycode, t_cub *cub)
{
	if (keycode == ESCAPE_KEY)
		ft_exit(cub);
	else if (keycode == W_KEY)
		cub->ply.move_up = true;
	else if (keycode == S_KEY)
		cub->ply.move_down = true;
	else if (keycode == A_KEY)
		cub->ply.rotate_left = true;
	else if (keycode == D_KEY)
	cub->ply.rotate_right = true;

	return (EXIT_SUCCESS);
}

int	ft_key_release(int keycode, t_cub *cub)
{
	if (keycode == W_KEY)
		cub->ply.move_up = false;
	else if (keycode == S_KEY)
		cub->ply.move_down = false;
	else if (keycode == A_KEY)
		cub->ply.rotate_left = false;
	else if (keycode == D_KEY)
		cub->ply.rotate_right = false;
	return (EXIT_SUCCESS);
}

void	init_events(t_cub *cub)
{
	mlx_hook(cub->win, ON_KEYDOWN, KeyPressMask, ft_key_press, cub);
	mlx_hook(cub->win, ON_KEYUP, KeyReleaseMask, ft_key_release, cub);
	mlx_hook(cub->win, ON_DESTROY, DestroyNotifyMask, ft_exit, cub);
	mlx_loop_hook(cub->mlx, ft_loop_hook, cub);
}
