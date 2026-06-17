/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:01:48 by efsilva-          #+#    #+#             */
/*   Updated: 2026/06/15 13:31:13 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
 
#include "libft.h"
#include "../mlx/minilibx-linux/mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
 
/* ── ERRORS ── */
# define ERR_ARGS    "Usage: ./cub3D <map.cub>\n"
# define ERR_EXT     "Map must have .cub extension\n"
# define ERR_OPEN    "Could not open file\n"
# define ERR_MALLOC  "Memory allocation failed\n"
# define ERR_TEXTURE "Invalid or missing texture path\n"
# define ERR_COLOR   "Invalid color format\n"
# define ERR_MAP     "Invalid map\n"
# define ERR_PLAYER  "Map must have exactly one player\n"
# define ERR_CLOSE   "Map is not closed by walls\n"
# define ERR_CHAR    "Invalid character in map\n"
 
/* ── STRUCTS ── */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;
 
typedef struct s_cub
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_rgb[3];
	int		ceil_rgb[3];
	char	**map;
	int		map_height;
	int		map_width;
	double	player_x;
	double	player_y;
	char	player_dir;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_cub;
 
/* ── PARSER ── */
void	parse_file(t_cub *cub, const char *path);
void	parse_config(t_cub *cub, int fd);
void	parse_map(t_cub *cub, int fd);
void	valid_map(t_cub *cub);
void	valid_close(t_cub *cub);
 
/* ── UTILS ── */
char	*read_line(int fd);
void	ft_error(t_cub *cub, char *msg);
void	free_cub(t_cub *cub);
void	free_map(t_cub *cub);
 
/* ── INIT ── */
void	init_cub(t_cub *cub);
 
#endif