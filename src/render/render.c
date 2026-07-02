/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/02 02:09:55 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static void	init_ray_steps(t_cub *cub, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->player_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->player_y)
			* ray->delta_dist_y;
	}
}

static void	calc_ray(t_cub *cub, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_W - 1;
	ray->ray_dir_x = cub->dir_x + cub->plane_x * ray->camera_x;
	ray->ray_dir_y = cub->dir_y + cub->plane_y * ray->camera_x;
	ray->map_x = (int)cub->player_x;
	ray->map_y = (int)cub->player_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	init_ray_steps(cub, ray);
}

static void	calc_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(SCREEN_H / ray->perp_wall_dist);
	ray->draw_start = SCREEN_H / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = SCREEN_H / 2 + ray->line_height / 2;
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
}

static void	dda(t_cub *cub, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	calc_wall_dist(ray);
}

void	render(t_cub *cub)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < SCREEN_W)
	{
		calc_ray(cub, &ray, x);
		dda(cub, &ray);
		draw_ceiling_floor(cub, x, &ray);
		draw_wall_column(cub, x, &ray);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
