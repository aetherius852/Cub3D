/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/02 02:09:58 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = cub->img.addr + (y * cub->img.line_len + x * (cub->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_ceiling_floor(t_cub *cub, int x, t_ray *ray)
{
	int	color;
	int	y;

	y = 0;
	color = (cub->ceil_rgb[0] << 16) | (cub->ceil_rgb[1] << 8)
		| cub->ceil_rgb[2];
	while (y < ray->draw_start)
		put_pixel(cub, x, y++, color);
	y = ray->draw_end;
	color = (cub->floor_rgb[0] << 16) | (cub->floor_rgb[1] << 8)
		| cub->floor_rgb[2];
	while (y < SCREEN_H)
		put_pixel(cub, x, y++, color);
}

static t_img	*get_texture(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (&cub->tex[3]);
	else if (ray->side == 0)
		return (&cub->tex[2]);
	else if (ray->ray_dir_y > 0)
		return (&cub->tex[1]);
	return (&cub->tex[0]);
}

static t_tex_coords	get_tex_coords(t_cub *cub, t_ray *ray, t_img *tex)
{
	t_tex_coords	tc;
	double			wall_x;

	if (ray->side == 0)
		wall_x = cub->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = cub->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= (int)wall_x;
	tc.tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tc.tex_x = tex->width - tc.tex_x - 1;
	tc.step = (double)tex->height / ray->line_height;
	tc.tex_pos = (ray->draw_start - SCREEN_H / 2
			+ ray->line_height / 2) * tc.step;
	return (tc);
}

void	draw_wall_column(t_cub *cub, int x, t_ray *ray)
{
	t_img			*tex;
	t_tex_coords	tc;
	int				color;
	int				y;

	tex = get_texture(cub, ray);
	tc = get_tex_coords(cub, ray, tex);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		color = *(int *)(tex->addr + ((int)tc.tex_pos & (tex->height - 1))
				* tex->line_len + tc.tex_x * (tex->bpp / 8));
		put_pixel(cub, x, y++, color);
		tc.tex_pos += tc.step;
	}
}
