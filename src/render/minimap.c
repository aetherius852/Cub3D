/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/07 12:20:23 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"
#define MM_TILE 6
#define MM_MARGIN 10

static int	tile_color(char c)
{
	if (c == '1')
		return (0xC8C8C8);
	if (c == ' ')
		return (0x000000);
	return (0x323232);
}

static void	draw_tile(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MM_TILE)
	{
		j = 0;
		while (j < MM_TILE)
		{
			put_pixel(cub, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_cub *cub)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = MM_MARGIN + (int)(cub->player_x * MM_TILE);
	py = MM_MARGIN + (int)(cub->player_y * MM_TILE);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(cub, px + j, py + i, 0xFF0000);
			j++;
		}
		i++;
	}
}

static void	draw_direction(t_cub *cub)
{
	double	px;
	double	py;
	int		k;

	px = cub->player_x;
	py = cub->player_y;
	k = 0;
	while (k < 8)
	{
		put_pixel(cub, MM_MARGIN + (int)(px * MM_TILE),
			MM_MARGIN + (int)(py * MM_TILE), 0xFFFF00);
		px += cub->dir_x * 0.3;
		py += cub->dir_y * 0.3;
		k++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			draw_tile(cub, MM_MARGIN + j * MM_TILE,
				MM_MARGIN + i * MM_TILE, tile_color(cub->map[i][j]));
			j++;
		}
		i++;
	}
	draw_player(cub);
	draw_direction(cub);
}
