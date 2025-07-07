/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:57:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/07 21:46:09 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// TODO: Split those
void	legal_move(t_cub *cub, double new_x, double	new_y)
{
	int map_x1 = new_x / MAP_SIZE;
	int map_y1 = new_y / MAP_SIZE;

	int map_x2 = (new_x + cub->ply.size - 1) / MAP_SIZE;
	int map_y2 = new_y / MAP_SIZE;

	int map_x3 = new_x / MAP_SIZE;
	int map_y3 = (new_y + cub->ply.size - 1) / MAP_SIZE;

	int map_x4 = (new_x + cub->ply.size - 1) / MAP_SIZE;
	int map_y4 = (new_y + cub->ply.size - 1) / MAP_SIZE;

	if (cub->map[map_y1][map_x1] == 0 &&
		cub->map[map_y2][map_x2] == 0 &&
		cub->map[map_y3][map_x3] == 0 &&
		cub->map[map_y4][map_x4] == 0)
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
	if (cub->ply.rotate_right)
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
	legal_move(cub, new_x, new_y);
}

void	raycast(t_cub *cub)
{
	double	fraction;
	double	start_x;
	int		i;

	fraction = M_PI / 3 / cub->width;
	start_x = cub->ply.angle - M_PI / 6;
	i = 0;
	while (i < cub->width)
	{
		draw_ray(cub, start_x, i);
		start_x += fraction;
		i++;
	}
}

int	ft_loop_hook(t_cub *cub)
{
	if (!cub || !cub->img.img_ptr)
		ft_exit(cub);
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
