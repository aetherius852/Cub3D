/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 11:53:03 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/07 12:05:37 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	check_point(t_cub *cub, double x, double y)
{
	if (x < 0 || y < 0 || x >= cub->map_width || y >= cub->map_height)
		return (0);
	if (!cub->map[(int)y] || (int)x >= (int)ft_strlen(cub->map[(int)y]))
		return (0);
	return (is_walkable(cub->map[(int)y][(int)x]));
}

void	update_accel(t_cub *cub)
{
	if (cub->move_x != 0 || cub->move_y != 0)
	{
		cub->accel += ACCEL_STEP;
		if (cub->accel > MAX_ACCEL)
			cub->accel = MAX_ACCEL;
	}
	else
		cub->accel = 1.0;
}
