/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:32:32 by inandres          #+#    #+#             */
/*   Updated: 2026/07/01 15:50:11 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static int	rotate_left_right(t_cub *cub, double rotspeed)
{
	double	tmp_x;

	tmp_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(rotspeed) - cub->dir_y * sin(rotspeed);
	cub->dir_y = tmp_x * sin(rotspeed) + cub->dir_y * cos(rotspeed);
	tmp_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(rotspeed) - cub->plane_y * sin(rotspeed);
	cub->plane_y = tmp_x * sin(rotspeed) + cub->plane_y * cos(rotspeed);
	return (1);
}

int	rotate_player(t_cub *cub, double rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROTSPEED * rotdir;
	moved += rotate_left_right(cub, rotspeed);
	return (moved);
}
