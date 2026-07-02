/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 02:07:03 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/02 02:19:50 by efsilva-         ###   ########.fr       */
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
	i = 0;
	while (i < 4)
		cub->tex[i++].img = NULL;
}

void	init_cub(t_cub *cub)
{
	init_cub_data(cub);
	cub->player_x = 0;
	cub->player_y = 0;
	cub->dir_x = 0;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0;
	cub->player_dir = 0;
	cub->move_x = 0;
	cub->move_y = 0;
	cub->rotate = 0;
	cub->has_moved = 0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img.img = NULL;
	cub->img.addr = NULL;
	cub->img.bpp = 0;
	cub->img.line_len = 0;
	cub->img.endian = 0;
}

static void	set_ew_dir(t_cub *cub)
{
	if (cub->player_dir == 'E')
	{
		cub->dir_x = 1;
		cub->dir_y = 0;
		cub->plane_x = 0;
		cub->plane_y = 0.66;
	}
	else
	{
		cub->dir_x = -1;
		cub->dir_y = 0;
		cub->plane_x = 0;
		cub->plane_y = -0.66;
	}
}

void	init_player_dir(t_cub *cub)
{
	if (cub->player_dir == 'N')
	{
		cub->dir_x = 0;
		cub->dir_y = -1;
		cub->plane_x = 0.66;
		cub->plane_y = 0;
	}
	else if (cub->player_dir == 'S')
	{
		cub->dir_x = 0;
		cub->dir_y = 1;
		cub->plane_x = -0.66;
		cub->plane_y = 0;
	}
	else
		set_ew_dir(cub);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_error(cub, ERR_MLX);
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!cub->win)
		ft_error(cub, ERR_MLX);
	cub->img.img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	if (!cub->img.img)
		ft_error(cub, ERR_MLX);
	cub->img.addr = mlx_get_data_addr(cub->img.img,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	if (!cub->img.addr)
		ft_error(cub, ERR_MLX);
	cub->player_x = 0;
	cub->player_y = 0;
	cub->player_dir = 0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img.img = NULL;
}
