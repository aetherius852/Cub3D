/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/07 12:10:16 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static t_floor	init_floor_row(t_cub *cub, int y)
{
	t_floor	f;
	double	row_dist;

	row_dist = (double)SCREEN_H / (2.0 * y - SCREEN_H);
	f.step_x = row_dist * (cub->plane_x * 2) / SCREEN_W;
	f.step_y = row_dist * (cub->plane_y * 2) / SCREEN_W;
	f.floor_x = cub->player_x + row_dist * (cub->dir_x - cub->plane_x);
	f.floor_y = cub->player_y + row_dist * (cub->dir_y - cub->plane_y);
	return (f);
}

static int	get_floor_color(t_cub *cub, double floor_x, double floor_y)
{
	t_img	*tex;
	int		tx;
	int		ty;

	if (!cub->tex[4].addr)
		return ((cub->floor_rgb[0] << 16) | (cub->floor_rgb[1] << 8)
			| cub->floor_rgb[2]);
	tex = &cub->tex[4];
	tx = (int)(floor_x * tex->width) & (tex->width - 1);
	ty = (int)(floor_y * tex->height) & (tex->height - 1);
	return (*(int *)(tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8))));
}

static int	get_ceil_color(t_cub *cub, double floor_x, double floor_y)
{
	t_img	*tex;
	int		tx;
	int		ty;

	if (!cub->tex[5].addr)
		return ((cub->ceil_rgb[0] << 16) | (cub->ceil_rgb[1] << 8)
			| cub->ceil_rgb[2]);
	tex = &cub->tex[5];
	tx = (int)(floor_x * tex->width) & (tex->width - 1);
	ty = (int)(floor_y * tex->height) & (tex->height - 1);
	return (*(int *)(tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8))));
}

void	draw_floor_ceiling(t_cub *cub)
{
	t_floor	f;
	int		y;
	int		x;

	y = SCREEN_H / 2 + 1;
	while (y < SCREEN_H)
	{
		f = init_floor_row(cub, y);
		x = 0;
		while (x < SCREEN_W)
		{
			put_pixel(cub, x, y, get_floor_color(cub, f.floor_x, f.floor_y));
			put_pixel(cub, x, SCREEN_H - y - 1,
				get_ceil_color(cub, f.floor_x, f.floor_y));
			f.floor_x += f.step_x;
			f.floor_y += f.step_y;
			x++;
		}
		y++;
	}
}
