/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 11:51:49 by inandres          #+#    #+#             */
/*   Updated: 2026/07/01 15:50:11 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static int	move_player_forward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_x + cub->dir_x * MOVESPEED;
	new_y = cub->player_y + cub->dir_y * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	move_player_backward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_x - cub->dir_x * MOVESPEED;
	new_y = cub->player_y - cub->dir_y * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	move_player_left(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_x + cub->dir_y * MOVESPEED;
	new_y = cub->player_y - cub->dir_x * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	move_player_right(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player_x - cub->dir_y * MOVESPEED;
	new_y = cub->player_y + cub->dir_x * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

int	move_player(t_cub *cub)
{
	int	moved;

	moved = 0;
	if (cub->move_y == 1)
		moved += move_player_forward(cub);
	if (cub->move_y == -1)
		moved += move_player_backward(cub);
	if (cub->move_x == -1)
		moved += move_player_left(cub);
	if (cub->move_x == 1)
		moved += move_player_right(cub);
	if (cub->rotate != 0)
		moved += rotate_player(cub, cub->rotate);
	return (moved);
}
