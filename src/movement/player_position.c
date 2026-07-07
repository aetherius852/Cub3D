/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 10:50:21 by inandres          #+#    #+#             */
/*   Updated: 2026/07/07 12:05:24 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	is_valid_pos_wall_collision(t_cub *cub, double x, double y)
{
	double	margin;

	margin = 0.2;
	if (!check_point(cub, x - margin, y - margin))
		return (false);
	if (!check_point(cub, x + margin, y - margin))
		return (false);
	if (!check_point(cub, x - margin, y + margin))
		return (false);
	if (!check_point(cub, x + margin, y + margin))
		return (false);
	return (true);
}

static bool	is_valid_pos_in_map(t_cub *cub, double x, double y)
{
	if (x < 0.25 || x >= cub->map_width - 0.25)
		return (false);
	if (y < 0.25 || y >= cub->map_height - 0.25)
		return (false);
	return (true);
}

static bool	is_valid_pos(t_cub *cub, double x, double y)
{
	if (!BONUS && is_valid_pos_in_map(cub, x, y))
		return (true);
	if (BONUS && is_valid_pos_wall_collision(cub, x, y))
		return (true);
	return (false);
}

int	validate_move(t_cub *cub, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(cub, new_x, cub->player_y))
	{
		cub->player_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(cub, cub->player_x, new_y))
	{
		cub->player_y = new_y;
		moved = 1;
	}
	return (moved);
}
