/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 11:50:12 by inandres          #+#    #+#             */
/*   Updated: 2026/07/02 01:00:14 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static int	key_press_handler(int key, t_cub *cub)
{
	if (key == XK_Escape)
		quit_cub3d(cub);
	if (key == XK_Left)
		cub->rotate -= 1;
	if (key == XK_Right)
		cub->rotate += 1;
	if (key == XK_w)
		cub->move_y = 1;
	if (key == XK_a)
		cub->move_x = -1;
	if (key == XK_s)
		cub->move_y = -1;
	if (key == XK_d)
		cub->move_x = 1;
	return (0);
}

static int	key_release_handler(int key, t_cub *cub)
{
	if (key == XK_Escape)
		quit_cub3d(cub);
	if (key == XK_w && cub->move_y == 1)
		cub->move_y = 0;
	if (key == XK_s && cub->move_y == -1)
		cub->move_y = 0;
	if (key == XK_a && cub->move_x == -1)
		cub->move_x += 1;
	if (key == XK_d && cub->move_x == 1)
		cub->move_x -= 1;
	if (key == XK_Left && cub->rotate <= 1)
		cub->rotate = 0;
	if (key == XK_Right && cub->rotate >= -1)
		cub->rotate = 0;
	return (0);
}

static void	wrap_mouse_position(t_cub *cub, int x, int y)
{
	if (x > SCREEN_W - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(cub->mlx, cub->win, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = SCREEN_W - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(cub->mlx, cub->win, x, y);
	}
}

static int	mouse_motion_handler(int x, int y, t_cub *cub)
{
	static int	old_x = SCREEN_W / 2;

	wrap_mouse_position(cub, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		cub->has_moved += rotate_player(cub, -1);
	else if (x > old_x)
		cub->has_moved += rotate_player(cub, 1);
	old_x = x;
	return (0);
}

void	listen_for_input(t_cub *cub)
{
	mlx_hook(cub->win, 17, 0, quit_cub3d, cub);
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_press_handler, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, key_release_handler, cub);
	if (BONUS)
		mlx_hook(cub->win, MotionNotify, PointerMotionMask,
			mouse_motion_handler, cub);
}
