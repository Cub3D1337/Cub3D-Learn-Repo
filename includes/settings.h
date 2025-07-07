/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:15:00 by abnsila           #+#    #+#             */
/*   Updated: 2025/07/07 12:16:04 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define WIDTH 800
# define HEIGHT 600
# define MOVE_FACTOR 0.2

enum e_events_hooks
{
	ON_MOUSEMOVE = 6,
	ON_DESTROY = 17,
};

enum e_events_masks
{
	PointerMotionMask = 1L << 6,
	DestroyNotify = 0L,
};

enum e_events_inputs
{
	ZOOM_IN = 4,
	ZOOM_OUT = 5,
	INCREASE_BUTTON = 1,
	DECREASE_BUTTON = 3,
	LEFT_KEY = 65361,
	UP_KEY = 65362,
	RIGHT_KEY = 65363,
	DOWN_KEY = 65364,
	ESCAPE_KEY = 65307,
	SHIFT_KEY = 65505,
	SPACE_KEY = 32,
	h_KEY = 104,
};

#endif
