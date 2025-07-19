/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:57:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/19 13:10:01 by abnsila          ###   ########.fr       */
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

// TODO: 2.5D raycasting
void	raycast(t_cub *cub, t_bool build)
{
	//? Use double instead of float for higher precision in ray calculations,
	//? since we're not highly memory-constrained and need accurate distances
	double	fov;
	double	fraction;
	double	ray_angle;
	int		i;

	// Set the Field of View (FOV) — here it's 60 degrees (PI / 3 radians)
	// This defines the total angle of the player's vision cone.
	fov = M_PI / 3;

	// Compute the angle increment between rays
	// Divide the FOV by the screen width so each pixel column gets a unique ray
	fraction = fov / cub->width;

	// Set the starting ray angle at the left edge of the FOV
	// Player's angle minus half of FOV centers the FOV around the player direction
	ray_angle = cub->ply.angle - fov / 2;

	i = 0;
	// Loop through each vertical column of the screen
	while (i < cub->width)
	{
		// Debug info: show index, angle increment, and current ray angle in degrees/radians
		printf("i: %d      frac: %.4f      r_a: %.4f radians   (%.4f degrees)\n",
			i, fraction, ray_angle, ray_angle * 180 / M_PI);

		// Cast a ray for this angle and draw a vertical line based on wall hit distance
		draw_ray(cub, ray_angle, i, build);

		// Increment the angle by one ray step (fraction) for next screen column
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
