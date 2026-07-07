/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/07 12:06:37 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static void	load_texture(t_cub *cub, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		ft_error(cub, ERR_TEXTURE);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		ft_error(cub, ERR_TEXTURE);
}

t_img	*get_texture(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&cub->tex[3]);
	else if (ray->side == 0)
		return (&cub->tex[2]);
	else if (ray->ray_dir_y > 0)
		return (&cub->tex[1]);
	return (&cub->tex[0]);
}

void	load_textures(t_cub *cub)
{
	load_texture(cub, &cub->tex[0], cub->no_texture);
	load_texture(cub, &cub->tex[1], cub->so_texture);
	load_texture(cub, &cub->tex[2], cub->we_texture);
	load_texture(cub, &cub->tex[3], cub->ea_texture);
	if (cub->floor_texture)
		load_texture(cub, &cub->tex[4], cub->floor_texture);
	if (cub->ceil_texture)
		load_texture(cub, &cub->tex[5], cub->ceil_texture);
}
