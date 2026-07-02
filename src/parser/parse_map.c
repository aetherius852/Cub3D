/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:31:31 by efsilva-          #+#    #+#             */
/*   Updated: 2026/07/01 13:43:31 by efsilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

static char	**grow_map(t_cub *cub, char **map, int count)
{
	char	**new_map;
	int		i;

	new_map = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_map)
	{
		free_map(cub);
		ft_error(cub, ERR_MALLOC);
	}
	i = 0;
	while (i < count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

static void	add_line(t_cub *cub, char *line, int i)
{
	int	len;

	len = ft_strlen(line);
	if (len > cub->map_width)
		cub->map_width = len;
	cub->map[i] = ft_strdup(line);
	if (!cub->map[i])
		ft_error(cub, ERR_MALLOC);
}

static int	process_line(t_cub *cub, char *line, int i)
{
	if (ft_strlen(line) > 0)
	{
		cub->map = grow_map(cub, cub->map, i);
		add_line(cub, line, i);
		return (1);
	}
	return (0);
}

void	parse_map(t_cub *cub, int fd, char *first_line)
{
	char	*line;
	int		i;

	cub->map = (char **)malloc(sizeof(char *) * 2);
	if (!cub->map)
		ft_error(cub, ERR_MALLOC);
	cub->map[0] = NULL;
	i = 0;
	if (first_line)
		i += process_line(cub, first_line, i);
	line = read_line(fd);
	while (line)
	{
		i += process_line(cub, line, i);
		free(line);
		line = read_line(fd);
	}
	if (i == 0)
		ft_error(cub, ERR_MAP);
	cub->map[i] = NULL;
	cub->map_height = i;
}
