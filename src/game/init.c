/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:03:18 by efsilva-          #+#    #+#             */
/*   Updated: 2026/06/24 13:33:52 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->no_texture = NULL;
	cub->so_texture = NULL;
	cub->we_texture = NULL;
	cub->ea_texture = NULL;
	cub->floor_rgb[0] = -1;
	cub->floor_rgb[1] = -1;
	cub->floor_rgb[2] = -1;
	cub->ceil_rgb[0] = -1;
	cub->ceil_rgb[1] = -1;
	cub->ceil_rgb[2] = -1;
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	cub->player_x = 0;
	cub->player_y = 0;
	cub->player_dir = 0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img.img = NULL;
}
