/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/07 12:19:48 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

/* ── SCREEN ── */
# define SCREEN_W	1280
# define SCREEN_H	800

/* ── GAMEPLAY ── */
# define MOVESPEED           0.1
# define ROTSPEED            0.08
# define DIST_EDGE_MOUSE_WRAP 10
# define MOUSE_SENS			 0.0624
# define BONUS               1
# define ACCEL_STEP			 0.015
# define MAX_ACCEL 		  	 2.5

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
# define ERR_MLX     "MLX initialization failed\n"

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

typedef struct s_floor
{
	double	floor_x;
	double	floor_y;
	double	step_x;
	double	step_y;
}	t_floor;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_cub
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*floor_texture;
	char	*ceil_texture;
	t_img	tex[6];
	int		floor_rgb[3];
	int		ceil_rgb[3];
	char	**map;
	int		map_height;
	int		map_width;
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	player_dir;
	char	*current_line;
	int		move_x;
	int		move_y;
	int		accel;
	int		rotate_left;
	int		rotate_right;
	int		has_moved;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_cub;

typedef struct s_tex_coords
{
    int     tex_x;
    double  step;
    double  tex_pos;
}   t_tex_coords;

/* ************************************************************************** */
/*                            PARSER FUNCTIONS                                */
/* ************************************************************************** */

/* parser/parse_file.c */
void	parse_file(t_cub *cub, const char *path);

/* parser/parse_config.c */
void	check_config(t_cub *cub);
void	parse_config(t_cub *cub, int fd);

/* parser/parse_map.c */
void	parse_map(t_cub *cub, int fd, char *first_line);

/* parser/valid_map.c */
void	valid_map(t_cub *cub);

/* ************************************************************************** */
/*                             UTILS FUNCTIONS                                */
/* ************************************************************************** */

/* parser/utils_parser.c */
char	*read_line(int fd);
void	ft_error(t_cub *cub, char *msg);
void	free_cub(t_cub *cub);
void	free_map(t_cub *cub);

/* parser/utils_map.c */
int		is_valid_char(char c);
int		is_player(char c);
char	*skip_spaces(char *line);

/* ************************************************************************** */
/*                              INIT FUNCTIONS                                */
/* ************************************************************************** */

/* game/init.c */
void	init_cub(t_cub *cub);
void	init_player_dir(t_cub *cub);
void	init_mlx(t_cub *cub);

/* ************************************************************************** */
/*                             EVENTS FUNCTIONS                               */
/* ************************************************************************** */

/* game/events.c */
int		handle_keypress(int key, t_cub *cub);
int		handle_close(t_cub *cub);

/* game/input_reader.c */
void	listen_for_input(t_cub *cub);

/* game/exit.c */
int		exit_clean(t_cub *cub, int code);
int		quit_cub3d(t_cub *cub);

/* game/player_movement.c */
int		move_player(t_cub *cub);

/* game/player_position.c */
int		validate_move(t_cub *cub, double new_x, double new_y);

/* game/player_rotate.c */
int		rotate_player(t_cub *cub, double rotdir);

/* ************************************************************************** */
/*                             RENDER FUNCTIONS                               */
/* ************************************************************************** */

/* render/render.c */
void	render(t_cub *cub);

/* minimap.c */
void	draw_minimap(t_cub *cub);

/* render/render_utils.c */
void	put_pixel(t_cub *cub, int x, int y, int color);
void	draw_ceiling_floor(t_cub *cub, int x, t_ray *ray);
void	draw_wall_column(t_cub *cub, int x, t_ray *ray);
void	draw_floor_ceiling(t_cub *cub);

/* render/textures.c */
void	load_textures(t_cub *cub);
int		is_wall(t_cub *cub, int x, int y);
t_img	*get_texture(t_cub *cub, t_ray *ray);

/* ************************************************************************** */
/*                             MOVEMENT FUNCTIONS                             */
/* ************************************************************************** */

int		check_point(t_cub *cub, double x, double y);
void	update_accel(t_cub *cub);
bool	is_walkable(char c);

#endif