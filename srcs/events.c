/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:57:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/07 12:46:45 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//TODO: Draw Loop
int	ft_loop_hook(t_cub *cub)
{
	if (!cub)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_mouse_move_hook(int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	(void)cub;
	return (EXIT_SUCCESS);
}

int	ft_mouse_hook(int button, t_cub *cub)
{
	(void)button;
	(void)cub;
	return (EXIT_SUCCESS);
}

// TODO: Key event flow
// else if (keycode == LEFT_KEY)
// 	ft_move_plan(cub, -MOVE_FACTOR / cub->zoom, 0);
// else if (keycode == RIGHT_KEY)
// 	ft_move_plan(cub, MOVE_FACTOR / cub->zoom, 0);
// else if (keycode == UP_KEY)
// 	ft_move_plan(cub, 0, MOVE_FACTOR / cub->zoom);
// else if (keycode == DOWN_KEY)
// 	ft_move_plan(cub, 0, -MOVE_FACTOR / cub->zoom);
// else if (keycode == SPACE_KEY)
// 	cub->trick_mouse = !cub->trick_mouse;
// else if (keycode == h_KEY)
// 	cub->toggle_menu = !cub->toggle_menu;
int	ft_key_hook(int keycode, t_cub *cub)
{
	(void)cub;
	if (keycode == ESCAPE_KEY)
		ft_exit(cub);
	return (EXIT_SUCCESS);
}

void	init_events(t_cub *cub)
{
	mlx_mouse_hook(cub->win, ft_mouse_hook, cub);
	mlx_key_hook(cub->win, ft_key_hook, cub);
	mlx_hook(cub->win, ON_MOUSEMOVE, PointerMotionMask,
		ft_mouse_move_hook, cub);
	mlx_hook(cub->win, ON_DESTROY, DestroyNotify, ft_exit, cub);
	mlx_loop_hook(cub->mlx, ft_loop_hook, cub);
}
