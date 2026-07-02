/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 02:03:57 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/02 02:35:21 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static char	*clean_newline(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	return (str);
}

static void	parse_texture(t_cub *cub, char **dst, char *line)
{
	char	*path;

	if (*dst)
		ft_error(cub, ERR_TEXTURE);
	path = skip_spaces(line);
	if (!*path)
		ft_error(cub, ERR_TEXTURE);
	path = clean_newline(path);
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
		else if (i < 2)
			ft_error(cub, ERR_COLOR);
		i++;
	}
}

static int	parse_line(t_cub *cub, char *line)
{
	char	*cleaned;

	cleaned = skip_spaces(line);
	if (!ft_strncmp(cleaned, "NO ", 3))
		parse_texture(cub, &cub->no_texture, cleaned + 3);
	else if (!ft_strncmp(cleaned, "SO ", 3))
		parse_texture(cub, &cub->so_texture, cleaned + 3);
	else if (!ft_strncmp(cleaned, "WE ", 3))
		parse_texture(cub, &cub->we_texture, cleaned + 3);
	else if (!ft_strncmp(cleaned, "EA ", 3))
		parse_texture(cub, &cub->ea_texture, cleaned + 3);
	else if (!ft_strncmp(cleaned, "F ", 2))
		parse_color(cub, cub->floor_rgb, cleaned + 2);
	else if (!ft_strncmp(cleaned, "C ", 2))
		parse_color(cub, cub->ceil_rgb, cleaned + 2);
	else if (cleaned[0] == '1' || cleaned[0] == '0')
		return (0);
	else if (ft_strlen(cleaned) > 0 && cleaned[0] != '\n')
		ft_error(cub, ERR_MAP);
	return (1);
}

void	parse_config(t_cub *cub, int fd)
{
	char	*line;
	char	*first;

	first = NULL;
	line = read_line(fd);
	cub->current_line = line;
	while (line)
	{
		if (!parse_line(cub, line))
		{
			first = line;
			break ;
		}
		free(line);
		cub->current_line = NULL;
		line = read_line(fd);
		cub->current_line = line;
	}
	check_config(cub);
	parse_map(cub, fd, first);
	cub->current_line = NULL;
	if (first)
		free(first);
}
