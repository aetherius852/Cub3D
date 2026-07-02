/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/02 02:07:40 by efsilva-         ###   ########.fr       */
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

void	load_textures(t_cub *cub)
{
	load_texture(cub, &cub->tex[0], cub->no_texture);
	load_texture(cub, &cub->tex[1], cub->so_texture);
	load_texture(cub, &cub->tex[2], cub->we_texture);
	load_texture(cub, &cub->tex[3], cub->ea_texture);
}
