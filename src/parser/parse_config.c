/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:33:27 by efsilva-          #+#    #+#             */
/*   Updated: 2026/06/22 10:45:40 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	parse_texture(t_cub *cub, char **dst, char *line)
{
	char	*path;

	if (*dst)
		ft_error(cub, ERR_TEXTURE);
	path = skip_spaces(line);
	if (!*path)
		ft_error(cub, ERR_TEXTURE);
	*dst = ft_strdup(path);
	if (!*dst)
		ft_error(cub, ERR_MALLOC);
}

static void	parse_color(t_cub *cub, int *rgb, char *line)
{
	char	*ptr;
	int		i;

	ptr = skip_spaces(line);
	i = 0;
	while (i < 3)
	{
		if (!ptr || !*ptr)
			ft_error(cub, ERR_COLOR);
		rgb[i] = ft_atoi(ptr);
		if (rgb[i] < 0 || rgb[i] > 255)
			ft_error(cub, ERR_COLOR);
		ptr = ft_strchr(ptr, ',');
		if (ptr)
			ptr++;
		i++;
	}
}

static int	parse_line(t_cub *cub, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		parse_texture(cub, &cub->no_texture, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		parse_texture(cub, &cub->so_texture, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		parse_texture(cub, &cub->we_texture, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		parse_texture(cub, &cub->ea_texture, line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		parse_texture(cub, &cub->floor_rgb, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		parse_texture(cub, &cub->ceil_rgb, line + 2);
	else if (line[0] == 'i' || line[0] == '0')
		return (0);
	else if (ft_strlen(line) > 0)
		ft_error(cub, ERR_MAP);
	return (1);
}

static void	check_config(t_cub *cub)
{
	if (!cub->no_texture || !cub->so_texture
		|| !cub->we_texture || !cub->ea_texture)
		ft_error(cub, ERR_TEXTURE);
	if (cub->floor_rgb[0] == -1 || cub->ceil_rgb[0] == -1)
		ft_error(cub, ERR_COLOR);
}

void	parse_config(t_cub *cub, int fd)
{
	char	*line;

	line = read_line(fd);
	while (line)
	{
		if (!parse_line(cub, skip_spaces(line)))
		{
			free(line);
			break ;
		}
		free(line);
		line = read_line(fd);
	}
	check_config(cub);
	parse_map(cub, fd);
}
